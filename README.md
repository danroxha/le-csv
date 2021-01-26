![License](https://img.shields.io/github/license/dannrocha/le-csv)
![Repo size](https://img.shields.io/github/repo-size/dannrocha/le-csv)
![Last commit](https://img.shields.io/github/last-commit/dannRocha/le-csv)
![Dev](https://img.shields.io/badge/daniel%20rocha-dev-green)


## Atividade de AED

### compilação
```sh
gcc main.c -o main && ./main dados.csv TITULO_COLUNA
```

* Exemplo
```sh
gcc main.c -o main && ./main dados_eleicao_2020.csv SG_PARTIDO
```
* Saída
```
|      INDEX     | Nº CANDIDATOS |    SG_PARTIDO 
|	1 	 |  	 1839 	 | 	PDT
|	2 	 |  	 1831 	 | 	PL
|	3 	 |  	 1620 	 | 	PC do B
|	4 	 |  	 1483 	 | 	REPUBLICANOS
|	5 	 |  	 1236 	 | 	PT
|	6 	 |  	 992 	 | 	PP
|	7 	 |  	 980 	 | 	MDB
|	8 	 |  	 974 	 | 	PSC
|	9 	 |  	 951 	 | 	PTB
|	10 	 |  	 948 	 | 	DEM
|	11 	 |  	 925 	 | 	PSDB
|	12 	 |  	 798 	 | 	PSD
|	13 	 |  	 717 	 | 	PSB
|	14 	 |  	 690 	 | 	PSL
|	15 	 |  	 627 	 | 	AVANTE
|	16 	 |  	 583 	 | 	PATRIOTA
|	17 	 |  	 539 	 | 	SOLIDARIEDADE
|	18 	 |  	 444 	 | 	PODE
|	19 	 |  	 435 	 | 	CIDADANIA
|	20 	 |  	 430 	 | 	PROS
|	21 	 |  	 379 	 | 	PV
|	22 	 |  	 305 	 | 	PTC
|	23 	 |  	 228 	 | 	PMN
|	24 	 |  	 205 	 | 	PRTB
|	25 	 |  	 205 	 | 	PSOL
|	26 	 |  	 140 	 | 	DC
|	27 	 |  	 140 	 | 	REDE
|	28 	 |  	 125 	 | 	PMB
|	29 	 |  	 11 	 | 	PSTU
|	30 	 |  	 9 	 | 	NOVO
|	31 	 |  	 5 	 | 	PCB
-----------------------------------------------------
| 	-	 |    TOTAL      | 	 -
|	   	 |    20794	 |

```
