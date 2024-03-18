#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Haina {
	int marime;
	char* categorie;
	float pret;
};

void afisareHaina(const struct Haina* haina) {
	if (haina != NULL) {
		printf("%s %d cu pretul %.2f.\t", haina->categorie, haina->marime, haina->pret);
	}
	else {
		printf("\nNu exista aceasta haina!\n");
	}
}

void afisareVector(const struct Haina* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareHaina(&vector[i]);
	}
}

void afisareMatrice(struct Haina** haine, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareHaina(&haine[i][j]);
		}
		printf("\n");
	}
}

struct Haina* adaugaElementVector(struct Haina* haine, int* dimensiune, struct Haina haina) {
	struct Haina* vector = (struct Haina*)malloc(sizeof(struct Haina) * ((*dimensiune) + 1));
	vector[(*dimensiune)] = haina;
	for (int i = 0; i < (*dimensiune); i++) {
		vector[i] = haine[i];
	}
	if (haine)
		free(haine);
	(*dimensiune)++;
	return vector;
}

void citireVectorFisier(const char* numeFisier, struct Haina** vecHaine, int* dimensiune) {
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		(*dimensiune) = 0;
		char buffer[50];
		char delimitator[] = ",\n";
		while (fgets(buffer, 49, f) != NULL) {
			struct Haina haina;
			char* token = strtok(buffer, delimitator);
			haina.marime = atoi(token);
			token = strtok(NULL, delimitator);
			haina.categorie = malloc(strlen(token) + 1);
			strcpy(haina.categorie, token);
			token = strtok(NULL, delimitator);
			haina.pret = atof(token);
			*vecHaine = adaugaElementVector(*vecHaine, dimensiune, haina);
		}
		fclose(f);
	}
	else {
		printf("Eroare la deschiderea fisierului");
	}
}

void citireMatriceFisier(const char* numeFisier, struct Haina** haine, int nrLinii, int* nrColoane) {
	FILE* f = fopen(numeFisier, "r");
	char buffer[50];
	if (f != NULL) {
		while (fgets(buffer, 49, f)) {
			struct Haina haina;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			haina.marime = atoi(token);
			token = strtok(NULL, delimitator);
			haina.categorie = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(haina.categorie, token);
			token = strtok(NULL, delimitator);
			haina.pret = atof(token);
			int poz;
			if (haina.pret < 50) {
				poz = 0;
			}
			else if (haina.pret > 100) {
				poz = 2;
			}
			else {
				poz = 1;
			}
			haine[poz] = adaugaElementVector(haine[poz], &(nrColoane[poz]), haina);
		}
		fclose(f);
	}
	else {
		printf("\nEroare la deschiderea fisierului!\n");
	}
}

float pretMediu(const struct Haina** matrice, int* nrElementeLinie, int cluster) {
	float suma = 0;
	for (int i = 0; i < nrElementeLinie[cluster]; i++) {
		suma += matrice[cluster][i].pret;
	}
	if (nrElementeLinie[cluster]) {
		return suma / nrElementeLinie[cluster];
	}
	else {
		return 0;
	}
}

struct Haina* cautareAricolMarime(const struct Haina** matrice, int nrLinii, int* nrColoane, int marime) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			if (matrice[i][j].marime == marime) {
				return &(matrice[i][j]);
			}
		}
	}
	return NULL;
}

void copyVectorMatrice(const struct Haina* vecHaine, struct Haine** matHaine, int nrLinii, int* nrColoane, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		int poz;
		if (vecHaine[i].marime < 35) {
			poz = 0;
		}
		else if (vecHaine[i].marime > 40) {
			poz = 2;
		}
		else {
			poz = 1;
		}
		struct Haina* hainaNoua = (struct Haina*)malloc(sizeof(struct Haina));
		hainaNoua->marime = vecHaine[i].marime;
		hainaNoua->pret = vecHaine[i].pret;
		hainaNoua->categorie = malloc(sizeof(char) * (strlen(vecHaine[i].categorie) + 1));
		strcpy(hainaNoua->categorie, vecHaine[i].categorie);

		matHaine[poz] = adaugaElementVector(matHaine[poz], &nrColoane[poz], *hainaNoua);
	}

}

void sortareMarime(struct Haina** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		//pentru fiecare linie aplicam algoritmul de sortare
		for (int j = 0; j < nrColoane[i] - 1; j++) {
			for (int k = 0; k < nrColoane[i] - j - 1; k++) {
				if (matrice[i][k].marime > matrice[i][k + 1].marime) {
					struct Haina temp = matrice[i][k];
					matrice[i][k] = matrice[i][k + 1];
					matrice[i][k + 1] = temp;
				}
			}
		}
	}
}

void sortarePret(struct Haina** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i] - 1; j++) {
			for (int k = 0; k < nrColoane[i] - j - 1; k++) {
				if (matrice[i][k].pret > matrice[i][k + 1].pret) {
					struct Haina temp = matrice[i][k];
					matrice[i][k] = matrice[i][k + 1];
					matrice[i][k + 1] = temp;
				}
			}
		}
	}
}

int main() {
	struct Haina** haine;
	int nrLinii = 3;
	int* nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	haine = (struct Haine**)malloc(sizeof(struct Haina*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrColoane[i] = 0;
		haine[i] = NULL;
	}
	citireMatriceFisier("haine.txt", haine, nrLinii, nrColoane);
	printf("\n\tMatricea\n");
	afisareMatrice(haine, nrLinii, nrColoane);
	printf("\nPretul mediu pentru primul cluster este: %.2f\n", pretMediu(haine, nrColoane, 0));
	printf("Pretul mediu pentru al doilea cluster este: %.2f\n", pretMediu(haine, nrColoane, 1));
	printf("Pretul mediu pentru ultimul cluster este: %.2f\n", pretMediu(haine, nrColoane, 2));
	printf("\n\tCautare articol dupa marime:\n");
	afisareHaina(cautareAricolMarime(haine, nrLinii, nrColoane, 34));
	struct Haina* vectHaine = NULL;
	int dim = 0;
	printf("\n\nCitire vector din fisier txt\n");
	citireVectorFisier("haine.txt", &vectHaine, &dim);
	afisareVector(vectHaine, dim);
	struct Haina** matHaine;
	int clustere = 3;
	int* nrCol = (int*)malloc(sizeof(int) * clustere);
	matHaine = (struct Haine**)malloc(sizeof(struct Haina*) * clustere);
	for (int i = 0; i < nrLinii; i++) {
		nrCol[i] = 0;
		matHaine[i] = NULL;
	}
	printf("\n\nAfisarea metricei din vector:\n");
	copyVectorMatrice(vectHaine, matHaine, clustere, nrCol, dim);
	afisareMatrice(matHaine, clustere, nrCol);

	printf("\nSortarea primei matrice dupa marimi:\n");
	sortareMarime(haine, nrLinii, nrColoane);
	afisareMatrice(haine, nrLinii, nrColoane);

	printf("\nSortarea pentru a 2 a matrice dupa pret:\n");
	sortarePret(matHaine, clustere, nrCol);
	afisareMatrice(matHaine, clustere, nrCol);
}