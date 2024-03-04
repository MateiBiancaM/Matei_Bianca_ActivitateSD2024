#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>


struct Marmelada {
	int nrBorcane;
	char* sortiment;
	float pret;
};

struct Marmelada citesteMarmelada() {
	struct Marmelada marmelada;
	printf("Introduceti sortimentul: ");
	marmelada.sortiment = (char*)malloc(50 * sizeof(char));
	scanf("%s", marmelada.sortiment);
	printf("Introduceti numarul de borcane: ");
	scanf("%d", &marmelada.nrBorcane);
	printf("Introduceti pretul: ");
	scanf("%f", &marmelada.pret);
	return marmelada;
}

void afisareMarmelada(struct Marmelada m) {
	if (m.sortiment != NULL) {
		printf("Sortiment: %s\n", m.sortiment);
	}
	printf("Pret: %5.2f\n", m.pret);
	printf("Nr. Borcane: %d\n\n", m.nrBorcane);
}

void afiseazaVector(struct Marmelada* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		afisareMarmelada(vector[i]);
	}
}

void dezalocareMarmelada(struct Marmelada* m) {
	free(m->sortiment);
	m->sortiment = NULL;
}

struct Marmelada initializareMarmelada(const char* sortiment, int nrBorcane, float pret) {
	struct Marmelada m;
	m.nrBorcane = nrBorcane;
	m.pret = pret;
	if (sortiment != NULL) {
		m.sortiment = malloc(strlen(sortiment) + 1);
		strcpy(m.sortiment, sortiment);
	}
	else {
		m.sortiment = malloc(strlen("N/A") + 1);
		strcpy(m.sortiment, "N/A");
	}
	return m;
}

struct Marmelada* copiazaObiectePretMinim(struct Marmelada* vectorInitial, int dimensiune, int* dimensiuneNoua, float pretMinim) {
	*dimensiuneNoua = 0;
	struct Marmelada* vectorNou = (struct Marmelada*)malloc(dimensiune * sizeof(struct Marmelada));
	for (int i = 0; i < dimensiune; i++) {
		if (vectorInitial[i].pret >= pretMinim) {
			vectorNou[*dimensiuneNoua] = vectorInitial[i];
			(*dimensiuneNoua)++;
		}
	}
	return vectorNou;
}

struct Marmelada* copiazaObiecteNrMaximBorcane(struct Marmelada* vectorInitial, int dimensiune, int* dimensiuneNoua, int nrMaximBorcane) {
	*dimensiuneNoua = 0;
	struct Marmelada* vectorNou = (struct Marmelada*)malloc(dimensiune * sizeof(struct Marmelada));
	for (int i = 0; i < dimensiune; i++) {
		if (vectorInitial[i].nrBorcane <= nrMaximBorcane) {
			vectorNou[*dimensiuneNoua] = vectorInitial[i];
			(*dimensiuneNoua)++;
		}
	}
	return vectorNou;
}
struct Marmelada* concateneazaVectori(struct Marmelada* vector1, int dimensiune1, struct Marmelada* vector2, int dimensiune2, int* dimensiuneNoua) {
	*dimensiuneNoua = 0;
	struct Marmelada* vectorConcatenat = (struct Marmelada*)malloc((dimensiune1 + dimensiune2) * sizeof(struct Marmelada));
	for (int i = 0; i < dimensiune1; i++) {
		vectorConcatenat[*dimensiuneNoua] = vector1[i];
		(*dimensiuneNoua)++;
	}
	for (int i = 0; i < dimensiune2; i++) {
		vectorConcatenat[*dimensiuneNoua] = vector2[i];
		(*dimensiuneNoua)++;
	}
	return vectorConcatenat;
}


void dezalocaVector(struct Marmelada* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		dezalocareMarmelada(&vector[i]);
	}
	free(vector);
}

void creare(char* fisier_txt) {
	FILE* f = fopen(fisier_txt, "w");
	if (f) {
		for (int i = 0; i < 10; i++) {
			struct Marmelada marmelada;
			marmelada.nrBorcane = i + 1;
			marmelada.pret = (i + 1) * 10;
			marmelada.sortiment = (char*)malloc(50 * sizeof(char));
			sprintf(marmelada.sortiment, "Sortiment%d", i + 1);
			fprintf(f, "%d %s %.2f\n", marmelada.nrBorcane, marmelada.sortiment, marmelada.pret);

			free(marmelada.sortiment);
		}
		fclose(f);
	}
	else
		printf("\nEroare la  deschiderea fisierului!\n");

}

void preluare(struct Marmelada* vector, int* nrObiecte, char* fis_txt) {
	FILE* f = fopen(fis_txt, "r");
	if (f) {
		*nrObiecte = 0;
		while (fscanf(f, "%d", &vector[*nrObiecte].nrBorcane) == 1) {
			vector[*nrObiecte].sortiment = (char*)malloc(50 * sizeof(char));
			if (vector[*nrObiecte].sortiment == NULL) {
				printf("Eroare la alocarea memoriei!");
				fclose(f);
				return;
			}
			fscanf(f, "%s %f", vector[*nrObiecte].sortiment, &vector[*nrObiecte].pret);
			(*nrObiecte)++;
		}
		fclose(f);
	}
	else
		printf("\nEroare la  deschiderea fisierului!\n");
}

void salvareObiect(struct Marmelada obiect, char* fisier_txt) {
	FILE* f = fopen(fisier_txt, "a"); //a => adaugare (append)
	if (f) {
		fprintf(f, "%d %s %.2f\n", obiect.nrBorcane, obiect.sortiment, obiect.pret);
		fclose(f);
		printf("\nObiectul a fost salvat in fisierul %s cu succes!\n", fisier_txt);
	}
	else {
		printf("\nEroare la deschiderea fisierului!\n");
	}
}

void salvareVector(struct Marmelada* vector, int nrObiecte, char* fisier_txt) {
	FILE* f = fopen(fisier_txt, "w");
	if (f) {
		for (int i = 0; i < nrObiecte; i++) {
			fprintf(f, "%d %s %.2f\n", vector[i].nrBorcane, vector[i].sortiment, vector[i].pret);
		}
		fclose(f);
		printf("\n\nVectorul de obiecte a fost salvat in fisierul %s cu succes!\n", fisier_txt);
	}
	else {
		printf("\nEroare la deschiderea fisierului!\n");
	}
}

void main() {
	creare("marmelade.txt");

	char fisier_txt[30];
	printf("Denumirea fisierului existent: ");
	scanf("%s", fisier_txt);

	struct Marmelada vectM[15];
	int nr;
	preluare(vectM, &nr, fisier_txt);

	printf("\n\nObiectele citite din fisier:\n");
	for (int i = 0; i < nr; i++) {
		printf("Obiect %d: Nr. Borcane: %d, Sortiment: %s, Pret: %.2f\n", i + 1,
			vectM[i].nrBorcane, vectM[i].sortiment, vectM[i].pret);
	}

	struct Marmelada m1;
	m1.nrBorcane = 11;
	m1.sortiment = "Sortiment11";
	m1.pret = 110;
	salvareObiect(m1, "marmelade.txt");

	preluare(vectM, &nr, fisier_txt);
	printf("\n\nObiectele citite din fisier:\n");
	for (int i = 0; i < nr; i++) {
		printf("Obiect %d: Nr. Borcane: %d, Sortiment: %s, Pret: %.2f\n", i + 1,
			vectM[i].nrBorcane, vectM[i].sortiment, vectM[i].pret);
	}
	salvareVector(vectM, 11, "mar.txt");


	//Apel task precedent
	/*int nr;
	printf("Intorduceti numarul de obiecte:"); scanf("%d", &nr);
	struct Marmelada* vectorMarmelade = (struct Marmelada*)malloc(nr * sizeof(struct Marmelada));
	for (int i = 0; i < nr; i++) {
		vectorMarmelade[i] = citesteMarmelada();
	}
	printf("\nAfisare obiecte din vector:\n");
	for (int i = 0; i < nr; i++) {
		afisareMarmelada(vectorMarmelade[i]);
	}

	int dimensiuneNoua1;
	struct Marmelada* vectorNou1 = copiazaObiectePretMinim(vectorMarmelade, nr, &dimensiuneNoua1, 20.0);
	printf("\n\nNoul vector cu preturi mai mari de 20\n");
	afiseazaVector(vectorNou1, dimensiuneNoua1);
	int dimensiuneNoua2;
	struct Marmelada* vectorNou2 = copiazaObiecteNrMaximBorcane(vectorMarmelade, nr, &dimensiuneNoua2, 5);
	printf("\n\nNoul vector cu un nr maxim de borcane 5\n");
	afiseazaVector(vectorNou2, dimensiuneNoua2);
	int dimensiuneNoua3;
	printf("\n\nConcatenarea celor doi vectori\n");
	struct Marmelada* vectorNou3 = concateneazaVectori(vectorNou1, dimensiuneNoua1, vectorNou2, dimensiuneNoua2, &dimensiuneNoua3);
	afiseazaVector(vectorNou3, dimensiuneNoua3);

	dezalocaVector(vectorMarmelade, nr);
	free(vectorNou1);
	free(vectorNou2);
	free(vectorNou3);*/

}