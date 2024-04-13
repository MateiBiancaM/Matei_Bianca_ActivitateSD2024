#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Caiet Caiet;
struct Caiet {
	char* tip;
	int nrPagini;
	float pret;
};

Caiet initializareCaiet(const char* tip, int nrPagini, float pret) {
	Caiet c;
	if (tip != NULL) {
		c.tip = malloc(strlen(tip) + 1);
		strcpy(c.tip, tip);
	}
	c.pret = pret;
	c.nrPagini = nrPagini;
	return c;
}

Caiet citireCaiet() {
	Caiet c;
	printf("Tip:");
	char buffer[30];
	scanf("%s", buffer);
	c.tip = malloc(strlen(buffer) + 1);
	strcpy(c.tip, buffer);
	printf("Numar pagini:");
	scanf("%d", &c.nrPagini);
	printf("Pret:");
	scanf("%f", &c.pret);
	return c;
}

void afisareCaiet(Caiet c) {
	printf("Tip:%s Nr pagini:%d Pret:%.2f\n", c.tip, c.nrPagini, c.pret);
}

void afisareVector(const Caiet* c, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareCaiet(c[i]);
	}
}

Caiet* copiazaNelemnte(Caiet* vector, int n) {
	Caiet* cpy = (Caiet*)malloc(sizeof(Caiet) * n);
	for (int i = 0; i < n; i++) {
		cpy[i] = initializareCaiet(vector[i].tip, vector[i].nrPagini, vector[i].pret);
	}
	return cpy;
}

Caiet* conditie(Caiet* vector, int dim, int min, int* dimNou) {
	*dimNou = 0;
	for (int i = 0; i < dim; i++) {
		if (vector[i].nrPagini > min)
			(*dimNou)++;
	}
	Caiet* vectConditie = (Caiet*)malloc(sizeof(Caiet) * (*dimNou));
	int k = 0;
	for (int i = 0; i < dim; i++) {
		if (vector[i].nrPagini > min) {
			vectConditie[k++] = initializareCaiet(vector[i].tip, vector[i].nrPagini, vector[i].pret);
		}
	}
	return vectConditie;
}

Caiet primulConditionat(Caiet* vector, int dim, float pret) {
	Caiet c;
	int i = 0;
	int ok = 0;
	while (i < dim && ok == 0) {
		if (vector[i].pret == pret) {
			c = initializareCaiet(vector[i].tip, vector[i].nrPagini, vector[i].pret);
			ok = 1;
		}
		i++;
	}
	if (ok == 0) {
		c = initializareCaiet("N/A", 0, 0);
	}
	return c;
}

Caiet* mutaElemente(Caiet** vector, int* dim, int* dimNou, int cond) {
	*dimNou = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].nrPagini < cond) {
			(*dimNou)++;
		}
	}
	Caiet* vectMutat = (Caiet*)malloc(sizeof(Caiet) * (*dimNou));
	Caiet* vectTemp = (Caiet*)malloc(sizeof(Caiet) * (*dim));
	int j = 0, k = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].nrPagini < cond) {
			vectMutat[j++] = initializareCaiet((*vector)[i].tip, (*vector)[i].nrPagini, (*vector)[i].pret);
		}
		else {
			vectTemp[k++] = initializareCaiet((*vector)[i].tip, (*vector)[i].nrPagini, (*vector)[i].pret);
		}
	}
	free(*vector);
	*vector = (Caiet*)malloc(sizeof(Caiet) * j);
	*dim = j;
	for (int i = 0; i < j; i++) {
		(*vector)[i] = vectTemp[i];
	}
	free(vectTemp);
	return vectMutat;
}

Caiet* concateneazaVectori(Caiet* v1, Caiet* v2, int dim1, int dim2, int* dimNou) {
	*dimNou = dim1 + dim2;
	Caiet* vectNou = (Caiet*)malloc(sizeof(Caiet) * (*dimNou));
	int i, j;
	for (i = 0; i < dim1; i++) {
		vectNou[i] = initializareCaiet(v1[i].tip, v1[i].nrPagini, v1[i].pret);
	}
	for (j = 0; j < dim2; j++) {
		vectNou[i + j] = initializareCaiet(v2[j].tip, v2[j].nrPagini, v2[j].pret);
	}
	return vectNou;
}

Caiet* adaugElement(Caiet* vect, int dim, Caiet c, int* dimNou) {
	(*dimNou) = dim + 1;
	Caiet* temp = (Caiet*)malloc(sizeof(Caiet) * (*dimNou));
	for (int i = 0; i < dim; i++) {
		temp[i] = initializareCaiet(vect[i].tip, vect[i].nrPagini, vect[i].pret);
	}
	temp[dim] = initializareCaiet(c.tip, c.nrPagini, c.pret);
	return temp;
}

void dezalocareElement(Caiet c) {
	free(c.tip);
	c.tip = NULL;
}

void dezalocareVector(Caiet** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		dezalocareElement((*vector)[i]);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

Caiet* adaugaCaiet(Caiet* vector, Caiet c, int* nrCaiete) {
	Caiet* copie = (Caiet*)malloc(sizeof(Caiet) * ((*nrCaiete) + 1));
	copie[(*nrCaiete)] = c;
	for (int i = 0; i < (*nrCaiete); i++) {
		copie[i] = vector[i];
	}
	if (vector) {
		free(vector);
	}
	(*nrCaiete)++;
	return copie;
}

Caiet* citireFiser(const char* fisier, int* nrCaiete) {
	Caiet* caiete = NULL;
	FILE* f = fopen(fisier, "r");
	if (f != NULL) {
		(*nrCaiete) = 0;
		char buffer[50];
		while (fgets(buffer, 49, f) != NULL) {
			Caiet c;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			c.tip = malloc(sizeof(char) * strlen(token) + 1);
			strcpy(c.tip, token);
			token = strtok(NULL, delimitator);
			c.nrPagini = atoi(token);
			token = strtok(NULL, delimitator);
			c.pret = atof(token);
			caiete = adaugaCaiet(caiete, c, nrCaiete);
		}
		fclose(f);
	}
	else {
		printf("Eroare la deschiderea fisierului!");
	}
	return caiete;
}

void adaugaInFisier(const char* fisier, const Caiet c) {
	FILE* f = fopen(fisier, "a");
	if (f != NULL) {
		fprintf(f, "\n%s,%d,%.2f", c.tip, c.nrPagini, c.pret);
		fclose(f);
		printf("\nCaietul a fost adaugat cu succes in fisier!\n");
	}
	else {
		printf("\nEroare la deschiderea fisierului!\n");
	}
}

void scrieVectorInFisier(const char* fisier, Caiet* vector, int dim) {
	FILE* f = fopen(fisier, "w");
	if (f != NULL) {
		for (int i = 0; i < dim; i++) {
			fprintf(f, "%s,%d,%.2f\n", vector[i].tip, vector[i].nrPagini, vector[i].pret);
		}
		fclose(f);
		printf("\nVectorul a fost adaugat cu succes in fisier!\n");
	}
	else {
		printf("\nEroare la deschiderea fisierului!\n");
	}
}

void citireMatrice(const char* nume, Caiet** matrice, int* nrCaieteLinie, int nrClustere) {
	FILE* f = fopen(nume, "r");
	if (f != NULL) {
		char buffer[50];
		while (fgets(buffer, 49, f)) {
			Caiet c;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			c.tip = malloc(strlen(token) + 1);
			strcpy(c.tip, token);
			token = strtok(NULL, delimitator);
			c.nrPagini = atoi(token);
			token = strtok(NULL, delimitator);
			c.pret = atof(token);
			int poz;
			if (c.nrPagini < 30) {
				poz = 0;
			}
			else if (c.nrPagini > 70) {
				poz = 2;
			}
			else {
				poz = 1;
			}
			matrice[poz] = adaugaCaiet(matrice[poz], c, &(nrCaieteLinie[poz]));
		}
		fclose(f);
	}
	else {
		printf("\nEroare deschidere fisier!\n");
	}
}

void afisareElem(Caiet c) {
	printf("Tip:%s Nr pagini:%d Pret:%.2f\t", c.tip, c.nrPagini, c.pret);
}

void afisareMatrice(Caiet** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareElem(matrice[i][j]);
		}
		printf("\n");
	}
}

Caiet CaietPretMin(Caiet** matrice, int nrLinii, int* nrCol) {
	float min = matrice[0][0].pret;
	printf("\nVal minima initiala:%.2f\n", min);
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			if (min > matrice[i][j].pret)
				min = matrice[i][j].pret;
		}
	}
	printf("Val minima finala : % .2f\n", min);
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			if (min == matrice[i][j].pret)
				return matrice[i][j];
		}
	}
}

float mediePagini(Caiet** matrice, int* nrColoane, int cluster) {
	float suma = 0;
	for (int i = 0; i < nrColoane[cluster]; i++) {
		suma += matrice[cluster][i].nrPagini;
	}
	if (suma) {
		return suma / nrColoane[cluster];
	}
	else {
		return 0;
	}
}

void dezalocareMatrice(Caiet*** matrice, int* nrLinii, int** nrColoane) {
	for (int i = 0; i < (*nrLinii); i++) {
		for (int j = 0; j < (*nrColoane)[i]; j++) {
			dezalocareVector(&((*matrice)[i]), &((*nrColoane)[i]));
		}
		free(*matrice);
		*matrice = NULL;
		free(*nrColoane);
		(*nrColoane) = NULL;
		(*nrLinii) = 0;
	}
}

void main() {
	/*Caiet c1 = initializareCaiet("Dictando", 30, 2.7);
	afisareCaiet(c1);
	Caiet c2 = citireCaiet();
	afisareCaiet(c2);*/

	printf("Vector initial\n");
	int dim = 10;
	Caiet* vector = (Caiet*)malloc(sizeof(Caiet) * dim);
	for (int i = 0; i < dim; i++) {
		vector[i] = initializareCaiet("Tip", 10 + 5 * i, 0.5 + 1.5 * i);
	}
	vector[2] = initializareCaiet("Tip", 50, 5.55);
	vector[5] = initializareCaiet("Tip", 60, 8.44);
	vector[8] = initializareCaiet("Tip", 50, 6.55);
	afisareVector(vector, dim);

	printf("\nVector cu n elemnte coipiate\n");
	int dimCopiate = 5;
	Caiet* vectCopy = copiazaNelemnte(vector, dimCopiate);
	afisareVector(vectCopy, dimCopiate);

	printf("\nVector conditie\n");
	int dimCond = 0;
	Caiet* vectCond = conditie(vector, dim, 49, &dimCond);
	afisareVector(vectCond, dimCond);

	printf("\nPrimul caiet\n");
	Caiet caiet = primulConditionat(vector, dim, 8.44);
	afisareCaiet(caiet);

	int dimMutat = 0;
	Caiet* vectMutat = mutaElemente(&vector, &dim, &dimMutat, 40);
	printf("\nVector initial:\n");
	afisareVector(vector, dim);
	printf("\nVector mutat:\n");
	afisareVector(vectMutat, dimMutat);

	printf("\nVector concat:\n");
	int dimConcat = 0;
	Caiet* vectConcat = concateneazaVectori(vectCond, vectMutat, dimCond, dimMutat, &dimConcat);
	afisareVector(vectConcat, dimConcat);

	printf("\nVector nou:\n");
	int dimNou = 0;
	Caiet* vectNou = adaugElement(vector, dim, caiet, &dimNou);
	afisareVector(vectNou, dimNou);

	/////////////////////////
	printf("\n\n--------CITIRE DIN FISIER--VECTOR----------\n\n");
	int nrCaiete = 0;
	Caiet* vectorFisier = citireFiser("caiete.txt", &nrCaiete);
	afisareVector(vectorFisier, nrCaiete);

	/*adaugaInFisier("caiete.txt", caiet);
	vectorFisier = citireFiser("caiete.txt", &nrCaiete);
	afisareVector(vectorFisier, nrCaiete);*/

	int nrCaiete2 = dimConcat;
	scrieVectorInFisier("caiete2.txt", vectConcat, nrCaiete2);
	Caiet* vectorFisier2 = citireFiser("caiete2.txt", &nrCaiete2);
	afisareVector(vectorFisier2, nrCaiete2);

	dezalocareVector(&vectorFisier2, &nrCaiete2);
	dezalocareVector(&vectorFisier, &nrCaiete);
	/////////////////////////

	printf("\n\n--------CITIRE DIN FISIER--MATRICE----------\n\n");
	struct Caiet** matrice;
	int nrLinii = 3;
	int* nrCol = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (Caiet**)malloc(sizeof(Caiet*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrCol[i] = 0;
		matrice[i] = NULL;
	}
	citireMatrice("caiete.txt", matrice, nrCol, nrLinii);
	afisareMatrice(matrice, nrLinii, nrCol);
	Caiet caietPret = CaietPretMin(matrice, nrLinii, nrCol);
	afisareCaiet(caietPret);

	int cluster = 2;
	float nrMediu = mediePagini(matrice, nrCol, cluster);
	printf("\nNr mediu de pagini pentru clsuterul %d este:%.2f\n", cluster, nrMediu);
	dezalocareMatrice(&matrice, &nrLinii, &nrCol);

	////////////////////////
	dezalocareVector(&vectNou, &dimNou);
	dezalocareVector(&vectConcat, &dimConcat);
	dezalocareVector(&vectMutat, &dimMutat);
	dezalocareElement(caiet);
	dezalocareVector(&vectCond, &dimCond);
	dezalocareVector(&vectCopy, &dimCopiate);
	dezalocareVector(&vector, &dim);

}