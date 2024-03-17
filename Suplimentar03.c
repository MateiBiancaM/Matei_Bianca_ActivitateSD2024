#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Calatorie {
	char* destinatie;
	int nrZile;
	float pret;
};

struct Calatorie* adaugaCalatorie(struct Calatorie* vector, struct Calatorie calatorie, int* nrCalatorii) {
	struct Calatorie* calatoriiCopy = (struct Calatorie*)malloc(sizeof(struct Calatorie) * ((*nrCalatorii) + 1));
	calatoriiCopy[(*nrCalatorii)] = calatorie;
	for (int i = 0; i < (*nrCalatorii); i++) {
		calatoriiCopy[i] = vector[i];
	}
	if (vector) {
		free(vector);
	}
	(*nrCalatorii)++;
	return calatoriiCopy;

}void afisareCalatorie(struct Calatorie calatorie) {
	printf("\nDestinatie:%s ; Nr zile:%d ; Pret:%.2f ", calatorie.destinatie, calatorie.nrZile, calatorie.pret);
}

void afisareCalatorii(struct Calatorie* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		afisareCalatorie(vector[i]);
	}
}

struct Calatorie* citireFisier(const char* numeFisier, int* nrCalatorii) {
	struct Calatorie* calatorii;
	calatorii = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		(*nrCalatorii) = 0;
		char buffer[50];
		while (fgets(buffer, 49, f) != NULL) {
			struct Calatorie calatorie;
			char delimitator[] = " \n";
			char* token = strtok(buffer, delimitator);
			calatorie.destinatie = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(calatorie.destinatie, token);
			token = strtok(NULL, delimitator);
			calatorie.nrZile = atoi(token);
			token = strtok(NULL, delimitator);
			calatorie.pret = atof(token);
			calatorii = adaugaCalatorie(calatorii, calatorie, nrCalatorii);
		}
		fclose(f);
	}
	else {
		printf("Eroare la deschiderea fisierului!");
	}
	return calatorii;
}

//cautare calatorie dupa o destinatie data
struct Calatorie cautaDestinatie(const struct Calatorie* vector, int dimensiune, const char* destinatie) {
	for (int i = 0; i < dimensiune; i++) {
		if (strcmp(vector[i].destinatie, destinatie) == 0) {
			return vector[i];
		}
	}
	struct Calatorie calatorie;
	calatorie.destinatie = malloc(strlen("N/A") + 1);
	strcpy(calatorie.destinatie, "N/A");
	calatorie.nrZile = 0;
	calatorie.pret = 0;
	return calatorie;
}

void adaugaInFisier(const char* nume_fisier, const struct Calatorie* calatorie) {
	FILE* f = fopen(nume_fisier, "a");
	if (f != NULL) {
		fprintf(f, "%s %d %.2f\n", calatorie->destinatie, calatorie->nrZile, calatorie->pret);
		fclose(f);
		printf("\nCalatoria pentru destinatia %s a fost adaugata cu succes in fisierul %s!", calatorie->destinatie, nume_fisier);
	}
	else {
		printf("Eroare la deschiderea fisierului!\n");
	}
}

void scrieVectorInFisier(const char* nume_fisier, struct Calatorie* vector, int dimensiune) {
	FILE* f = fopen(nume_fisier, "w");
	if (f != NULL) {
		for (int i = 0; i < dimensiune; i++) {
			fprintf(f, "%s %d %.2f\n", vector[i].destinatie, vector[i].nrZile, vector[i].pret);
		}
		fclose(f);
		printf("\nVectorul de calatorii a fost scris cu succes in fisierul %s!\n", nume_fisier);
	}
	else {
		printf("Eroare la deschiderea fisierului!\n");
	}
}

void dezalocareVector(struct Calatorie** calatorii, int* dimensiune) {
	for (int i = 0; i < (*dimensiune); i++)
		free((*calatorii)[i].destinatie);
	free(*calatorii);
	(*calatorii) = NULL;
	(*dimensiune) = 0;
}

void main() {
	int nrCalatorii = 0;
	struct Calatorie* calatorii = NULL;
	printf("\nCalatoriile cititie din fisier:\n");
	calatorii = citireFisier("Calatorii.txt", &nrCalatorii);
	afisareCalatorii(calatorii, nrCalatorii);

	struct Calatorie calatorieCautata;
	calatorieCautata = cautaDestinatie(calatorii, nrCalatorii, "Paris");
	printf("\n\nCalatoria cautata:");
	afisareCalatorie(calatorieCautata);
	printf("\n");
	struct Calatorie calatorieCautata2;
	calatorieCautata2 = cautaDestinatie(calatorii, nrCalatorii, "Londra");
	printf("\n\nCalatoria cautata:");
	afisareCalatorie(calatorieCautata2);
	printf("\n");

	struct Calatorie adaugCalatorie = { "Romania",2,435 };
	adaugaInFisier("Calatorii.txt", &adaugCalatorie);
	struct Calatorie adaugCalatorie2 = { "Madrid",2,768 };
	adaugaInFisier("Calatorii.txt", &adaugCalatorie2);

	printf("\nCalatoriile cititie din fisier:\n");
	calatorii = citireFisier("Calatorii.txt", &nrCalatorii);
	afisareCalatorii(calatorii, nrCalatorii);

	scrieVectorInFisier("VectorCalatorii.txt", calatorii, nrCalatorii);
	int nr = 0;
	struct Calatorie* vector = NULL;
	printf("\nCalatoriile cititie din fisierul creat:\n");
	vector = citireFisier("VectorCalatorii.txt", &nr);
	afisareCalatorii(vector, nr);

	dezalocareVector(&calatorii, &nrCalatorii);

}
