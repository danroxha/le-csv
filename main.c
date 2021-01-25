#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

struct map {
	char* key;
	int value;
};

struct stack {
	struct map* map;
	int len;
};

struct cabecalho {
	char** colunas;
	int capacidade;
};

void nextLine(FILE* file) {
	while(fgetc(file) != '\n');
}

char* trim(char* s){
	char* n = (char*)malloc(0);
	size_t l = 0;
	for(size_t i = 0; i < strlen(s); i++) {
		if(s[i] != ' ') {
			l++;
			n = (char*)realloc(n, sizeof(char) * l);
			n[l - 1] = s[i];
		}
	}

	return n;
}

char* removeChar(char*s, char c) {
	char*n = (char*) malloc(0);
	int len = 0;
	for(size_t i = 0; i < strlen(s); i++) {
		if(s[i] != c) {
			len++;
			n = realloc(n, sizeof(char) * len);
			n[len - 1] = s[i];
		}
	}

	return n;
}

int compare(const void* a, const void* b)  {
	struct map _a = (*(struct map *) a);
	struct map _b = (*(struct map *) b);
	if( _a.value < _b.value) return 1;
	if( _a.value > _b.value) return -1;
	return 1;
} 

void sort(struct map *s, int n){  
  qsort(s, n, sizeof(struct map), compare);
}

struct cabecalho  extrairCabecalho(FILE *file){

	struct cabecalho cabecalho = {.capacidade=0, .colunas=NULL};
	char*  text = (char*)malloc(0);
	char letra;
	int len = 0;
	int start = 0;
	fpos_t pos;

	fgetpos(file, &pos);
	fseek(file, 0, SEEK_SET);

	
	
	while(letra != '\n') {
		
		letra = fgetc(file);
		if((letra == ';' && !start) || ftell(file) == 1) {
			start = 1;
			len = 0;
		}
		if(letra == ';' && start) {

			start = 0;
			len = 0;

			cabecalho.capacidade += 1;
			cabecalho.colunas = (char**) realloc(cabecalho.colunas, sizeof(char**) * cabecalho.capacidade);
			cabecalho.colunas[cabecalho.capacidade - 1] = (char*)malloc(sizeof(char) * strlen(text));
			strcpy(cabecalho.colunas[cabecalho.capacidade - 1], text);
	        			
			text = (char*) realloc(text, len);
			continue;
		}
		
		if(letra == '"') continue;
				
		len++;
				
		text = (char*) realloc(text, sizeof(char) * len);
		text[len - 1] = letra;
	}

	fsetpos(file, &pos);

	
	return cabecalho;
}


int main(int argc, char**argv){
	
	FILE *file = NULL;
	if(argc > 1)
		file = fopen(argv[1], "r");
	else {
		fprintf(stderr, "Passe um arquivo csv como parametro: OBS: delimitador ponto e virgula(;)");
		exit(1);
	}

	
	int dot = 0;
	int COLUNA = 28;

	char* text = (char*)malloc(0);
	int len = 0;

	struct stack candidadosPorPartido = {.len = 0};
	struct cabecalho cabecalho = extrairCabecalho(file);

	if(argc == 3) {
		for(int i = 0; i < cabecalho.capacidade; i++) {
			if(!strcmp(cabecalho.colunas[i], argv[2])) {
				COLUNA = i;
				break;			
			}
		}
	}

	do {
		char letra = fgetc(file);
		if(letra == ';') dot++;
		
	
		if(dot >= COLUNA && letra != ';') {
			len++;
			text = (char*) realloc(text, sizeof(char) * len);
			text[len - 1] = letra;
		}
		if(dot > COLUNA && letra == ';') {
	
			text = removeChar(text, '"');

			if(candidadosPorPartido.len == 0) {
				candidadosPorPartido.len = 1;
				candidadosPorPartido.map = (struct map*)realloc(candidadosPorPartido.map, sizeof(struct map) * candidadosPorPartido.len);
				struct map partido = {.value=1};
				partido.key = (char*)calloc(strlen(text), sizeof(char));
				strcpy(partido.key, text);
				candidadosPorPartido.map[candidadosPorPartido.len - 1] = partido;

			} else {
			
				bool existePartido = false;
				
				for(int i = 0; i < candidadosPorPartido.len; i++) {
					if(!strcmp(candidadosPorPartido.map[i].key, text)) {
						candidadosPorPartido.map[i].value += 1;
						existePartido = true;
						break;
					}
				}

				if(!existePartido) {
				
					candidadosPorPartido.len += 1;
					candidadosPorPartido.map = (struct map*)realloc(candidadosPorPartido.map, sizeof(struct map) * candidadosPorPartido.len);
		
					candidadosPorPartido.map[candidadosPorPartido.len - 1].key = (char*)calloc(strlen(text), sizeof(char));
					candidadosPorPartido.map[candidadosPorPartido.len - 1].value = 1;
					strcpy(candidadosPorPartido.map[candidadosPorPartido.len - 1].key, text);	

				}

			}


			len = 0;
			dot = 0;
			text = (char*) realloc(text, 0);
				
			nextLine(file);
		}
	}
	while(!feof(file));
		
	fclose(file);


	sort(candidadosPorPartido.map, candidadosPorPartido.len);
	
	printf("|     INDEX \t | Nº CANDIDATOS |    %s \n", argv[2]);
	for(int i = 0; i < candidadosPorPartido.len; i++) {
		printf("|\t%d \t | \t %d \t | \t%s\n", i + 1, candidadosPorPartido.map[i].value, candidadosPorPartido.map[i].key);
	}
	printf("---------------------------------------------------------\n");
	printf("| \t-\t |\tTOTAL\t | \t -\n");

	int totalCandidatos = 0;

	for(int i = 0; i < candidadosPorPartido.len; i++)
		totalCandidatos += candidadosPorPartido.map[i].value;
	printf("|\t   \t |\t%d\t |\n",totalCandidatos);

	return 0;
}
