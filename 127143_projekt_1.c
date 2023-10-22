#include<stdio.h>
#include<string.h>
#include<stdlib.h>


FILE* fc_v(FILE* file, int* sn,char ****pole,int *pz) {
	int jeotvoreny = 0;

	if (file == NULL) {
		printf("subor nebol este otvoreny - pokusam sa ho otvorit\n");
		file = fopen("dataloger.txt", "r");
		if (file == NULL)
			jeotvoreny = 0;
		else
			jeotvoreny = 1;
	}
	else
		jeotvoreny = 1;
	if (jeotvoreny == 0) {
		printf("Neotvoreny subor");
	}
	if(pole !=NULL) {
		int a, b, c;
		for (a = 0; a < *pz; a++) {
			for (b = 0; b < 7; b++) {
				for (c = 0; c < 1; c++) {
					printf("%s\n", pole[a][b][c]);
				}
			}
		}
	}
	else {
		int r = 1;
		char riadok[256];
		while (fgets(riadok, sizeof(riadok), file)) {
			if ((r % 7) == 1) {
				printf("ID. mer. modulu: ");
			}
			if ((r % 7) == 2) {
				printf("Pozicia modulu: ");
			}
			if ((r % 7) == 3) {
					printf("Typ mer. veliciny: ");
			}
			if ((r % 7) == 4) {
				printf("Hodnota: ");
			}
			if ((r % 7) == 5) {
				printf("Cas merania: ");
			}
			if ((r % 7) == 6) {
				printf("Datum merania: ");
			}
			printf("%s", riadok);
			r++;	
		}	
	}
	return file;
}

char**** fc_n(char**** pole, FILE* file, int* sv,int* ppz) {
	int c, i, j, x, y, z;
	if (*sv == 0) {
		printf("Neotvoreny subor\n");
	}
	else if (*sv > 0) {
		int poc_ria = 1, prec_c;
		char pred_c = ' ';
		fseek(file, 0, SEEK_SET);
		while ((prec_c = fgetc(file)) != EOF) { //zistenie poctu riadkov
			if (prec_c == '\n' && pred_c != '\r') {
				poc_ria++;
			}
			pred_c = prec_c;
		}
		*ppz = poc_ria / 7;
		printf("Pocet zaznamov = %d\n", *ppz);

		if (pole != NULL) {
			for (x = 0; x < *ppz; x++) {
				for (y = 0; y < 7; y++) {
					for (z = 0; z < 1; z++) {
						free(pole[x][y][z]);
					}
					free(pole[x][y]);
				}
				free(pole[x]);
			}
			pole = (char****)malloc(*ppz * sizeof(char***)); // vyhradenie miesta na 3D pole
			for (x = 0; x < *ppz; x++) {
				pole[x] = (char***)malloc(7 * sizeof(char**));
				for (y = 0; y < 7; y++) {
					pole[x][y] = (char**)malloc(1 * sizeof(char*));
				}
			}
			//priradenie hodnôt daným prvkom 3D po¾a
			for (x = 0; x < *ppz; x++) {
				for (y = 0; y < 7; y++) {
					for (z = 0; z < 1; z++) {
						char buff[20]; // predpokladám že riadok nie je dlhší ako 20 charakterov
						fseek(file, 0, SEEK_SET);
						while (fgets(buff, 20, file) != NULL) {
							buff[strlen(buff) - 1] = '\0';
							pole[x][y][z] = (char*)malloc(strlen(buff) + 1);
							strcpy(pole[x][y][z], buff);

						}
					}
				}
			}
		}
	}
	return pole;
	}



int main(void) {
	char p;
	char**** pole = NULL;
	int s_n = 0, s_v = 0, pz=0;
	FILE* f =NULL;
	do {
		scanf("%c", &p);
		if (p == 'v') {
			f = fc_v(f, &s_n,pole,&pz);
			s_v+= 1;
		}
		else if (p == 'n') {
			pole = fc_n(pole,f,&s_v,&pz);
			s_n += 1;
		}
			 /*
		else if (p == 'c')
			fc_c();
		else if (p == 's')
			fc_s();
		else if (p == 'h')
			fc_h();
		else if (p == 'z')
			fc_z();
		else if (p == 'k') {
			//dealokácia dynamických polí a zavretie súboru
		}*/
		//else
			//continue;
	} while (1);
	return 0;
}