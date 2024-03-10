#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


struct Marmelada {
	int nrBorcane;
	char* sortiment;
	float pret;
};


void afisareMarmelada(struct Marmelada* m) {
	if (m->sortiment != NULL) {
		printf("Nr. Borcane: %d,Sortiment: %s,Pret: %5.2f\n", m->nrBorcane, m->sortiment, m->pret);
	}
}

void afiseazaVector(struct Marmelada* vector, int dimensiune) {
	printf("\nAfisare vector\n");
	for (int i = 0; i < dimensiune; i++) {
		afisareMarmelada(&vector[i]);
	}
}


void dezalocaVector(struct Marmelada** vector, int* dimensiune) {
	for (int i = 0; i < (*dimensiune); i++) {
		free((*vector)[i].sortiment);
	}
	free(*vector);
	(*vector) = NULL;
	(*dimensiune) = 0;
}

struct Marmelada* adaugaMarmelada(struct Marmelada* vector, struct Marmelada marmelada, int* dim) {
	struct Marmelada* copy = (struct Marmelada*)malloc(sizeof(struct Marmelada) * ((*dim) + 1));
	copy[(*dim)] = marmelada;
	for (int i = 0; i < (*dim); i++) {
		copy[i] = vector[i];
	}
	if (vector)
		free(vector);
	(*dim)++;
	return copy;
}

//functia care citeste din fisier si obiectele din fisier si sa le salveze intr-un vector
struct Marmelada* citireFisier(const char* numeFisier, int* nrSortimene) {
	struct Marmelada* vectorMarmelada;
	vectorMarmelada = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		(*nrSortimene) = 0;
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL) {
			struct Marmelada marmelada;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			marmelada.nrBorcane = atoi(token);
			token = strtok(NULL, delimitator);
			marmelada.sortiment = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(marmelada.sortiment, token);
			token = strtok(NULL, delimitator);
			marmelada.pret = atof(token);
			vectorMarmelada = adaugaMarmelada(vectorMarmelada, marmelada, nrSortimene);
		}
		fclose(f);
	}
	return vectorMarmelada;
}
//deep copy
struct Marmelada* copiazaMarmelada(const struct Marmelada* marmelada) {
	// Alocare memorie pentru obiectul copie
	struct Marmelada* copie = (struct Marmelada*)malloc(sizeof(struct Marmelada));
	copie->nrBorcane = marmelada->nrBorcane;
	copie->pret = marmelada->pret;
	copie->sortiment = (char*)malloc(strlen(marmelada->sortiment) + 1);
	strcpy(copie->sortiment, marmelada->sortiment);
	return copie;
}

//criteriu aplicat unui atribut->pret
void sortareInserare(struct Marmelada* vector, int dimensiune) {

	for (int i = 0; i < dimensiune; i++) {
		struct Marmelada cpy = vector[i];
		int j = i - 1;
		while (j >= 0 && vector[j].pret > cpy.pret) {
			vector[j + 1] = vector[j];
			j--;
		}
		vector[j + 1] = cpy;
	}
}
//functie care sa copieze elementele din vector intr-o matrice alocata dinamic
struct Marmelada** copiazaInMatrice(struct Marmelada* vector, int dimensiune) {
	struct Marmelada** matrice = (struct Marmelada**)malloc(dimensiune * sizeof(struct Marmelada*));
	sortareInserare(vector, dimensiune);
	//copiem obiectele din vector in matrice
	for (int i = 0; i < dimensiune; i++) {
		matrice[i] = copiazaMarmelada(&vector[i]);
	}

	return matrice;
}
void afisareMatrice(struct Marmelada** matrice, int dimensiune) {
	printf("\nAfisare matrice\n");
	for (int i = 0; i < dimensiune; ++i) {
		printf("Nr. Borcane: %-5d  Sortiment: %-15s  Pret: %-5.2f\n", matrice[i]->nrBorcane, matrice[i]->sortiment, matrice[i]->pret);
	}
}

void elibereazaMatrice(struct Marmelada** matrice, int dimensiune) {
	for (int i = 0; i < dimensiune; ++i) {
		free(matrice[i]->sortiment);
		free(matrice[i]);
	}
	free(matrice);
}
//functie care sorteaza liniile matricei in functie de numarul de borcane
void sortareLiniiMatrice(struct Marmelada** matrice, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		for (int j = i + 1; j < dimensiune; j++) {
			if (matrice[i]->nrBorcane > matrice[j]->nrBorcane) {
				struct Marmelada* temp = matrice[i];
				matrice[i] = matrice[j];
				matrice[j] = temp;
			}
		}
	}
}

void main() {
	int dimensiune = 3;
	struct Marmelada* sortimente = NULL;
	sortimente = citireFisier("marmelade.txt", &dimensiune);

	printf("\nVectorul citit din fisier:\n");
	afiseazaVector(sortimente, dimensiune);

	struct Marmelada** matrice = copiazaInMatrice(sortimente, dimensiune);
	printf("\nMatricea rezultata in urma copierii:\n");
	afisareMatrice(matrice, dimensiune);

	sortareLiniiMatrice(matrice, dimensiune);
	printf("\nMatricea rezultata dupa sortare:\n");
	afisareMatrice(matrice, dimensiune);

	dezalocaVector(&sortimente, &dimensiune);
	elibereazaMatrice(matrice, dimensiune);
}