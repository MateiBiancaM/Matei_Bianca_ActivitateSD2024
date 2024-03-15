#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Carte {
	char* titlu;
	float pret;
	int nrPagini;
};

struct Carte initializareCarte(const char* titlu, float pret, int nrPagini) {
	struct Carte carte;
	if (titlu != NULL) {
		carte.titlu = malloc(strlen(titlu) + 1);
		strcpy(carte.titlu, titlu);
	}
	else {
		carte.titlu = malloc(strlen("N\A") + 1);
		strcpy(carte.titlu, "N\A");
	}
	carte.nrPagini = nrPagini;
	carte.pret = pret;
	return carte;
}

void afisareCarte(const struct Carte carte) {
	if (carte.titlu != NULL) {
		printf("Titlu: %s | ", carte.titlu);
	}
	printf("Nr pagini: %d | Pret: %.2f\n", carte.nrPagini, carte.pret);

}

void afisareVector(const struct Carte* carti, int dim) {

	if (dim > 0 && carti != NULL) {
		for (int i = 0; i < dim; i++) {
			afisareCarte(carti[i]);
		}
	}
}

struct Carte* copiazaNcarti(const struct Carte* carti, int nCpy) {
	struct Carte* copy = (struct Carte*)malloc(sizeof(struct Carte) * nCpy);
	for (int i = 0; i < nCpy; i++) {
		copy[i] = carti[i];
		copy[i].titlu = (char*)malloc(sizeof(char) * (strlen(carti[i].titlu) + 1));
		strcpy(copy[i].titlu, carti[i].titlu);
	}
	return copy;
}

struct Carte primaCarte(const struct Carte* carti, int dim, float pret) {
	struct Carte carte;
	for (int i = 0; i < dim; i++) {
		if (carti[i].pret == pret) {
			carte = initializareCarte(carti[i].titlu, carti[i].pret, carti[i].nrPagini);
			return carte;
		}
	}
	carte = initializareCarte("N/A", 0, 0);
	return carte;
}

struct Carte* cartiNrMinimPagini(const struct Carte* cartiInitiale, int dim, int* nrCartiConditie, int min) {
	(*nrCartiConditie) = 0;
	for (int i = 0; i < dim; i++) {
		if (cartiInitiale[i].nrPagini > min) {
			(*nrCartiConditie)++;
		}
	}
	struct Carte* cartiConditie = (struct Carte*)malloc(sizeof(struct Carte) * (*nrCartiConditie));
	int index = 0;
	for (int i = 0; i < dim; i++) {
		if (cartiInitiale[i].nrPagini > min) {
			cartiConditie[index++] = initializareCarte(cartiInitiale[i].titlu, cartiInitiale[i].pret, cartiInitiale[i].nrPagini);
		}
	}
	return cartiConditie;
}

struct Carte* mutaCarti(struct Carte** vectInitial, int* dimInitial, int* dimNou, float pret) {
	(*dimNou) = 0;
	for (int i = 0; i < *dimInitial; i++) {
		if ((*vectInitial)[i].pret > pret) {
			(*dimNou)++;
		}
	}
	struct Carte* vectorNou = (struct Carte*)malloc((*dimNou) * sizeof(struct Carte));
	struct Carte* tempVect = (struct Carte*)malloc(*dimInitial * sizeof(struct Carte));
	int j = 0, k = 0;
	for (int i = 0; i < (*dimInitial); i++) {
		if ((*vectInitial)[i].pret > pret) {
			vectorNou[k++] = initializareCarte((*vectInitial)[i].titlu, (*vectInitial)[i].pret, (*vectInitial)[i].nrPagini);
		}
		else {
			tempVect[j++] = initializareCarte((*vectInitial)[i].titlu, (*vectInitial)[i].pret, (*vectInitial)[i].nrPagini);
		}
	}
	free(*vectInitial);
	*vectInitial = (struct Carte*)malloc(j * sizeof(struct Carte));
	for (int i = 0; i < j; i++) {
		(*vectInitial)[i] = tempVect[i];
	}
	*dimInitial = j;
	free(tempVect);
	return vectorNou;
}


void dezalocareCarte(struct Carte* carte) {
	free(carte->titlu);
	carte->titlu = NULL;
}

void dezalocareMemorie(struct Carte** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		dezalocareCarte(&((*vector)[i]));
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

struct Carte* concateneazaVectori(struct Carte* vector1, int dim1, struct Carte* vector2, int dim2, int* dimRez) {
	*dimRez = dim1 + dim2;
	struct Carte* rezultat = (struct Carte*)malloc(sizeof(struct Carte) * (*dimRez));
	int i, j;
	for (i = 0; i < dim1; i++) {
		rezultat[i] = vector1[i];
		rezultat[i].titlu = (char*)malloc(sizeof(char) * (strlen(vector1[i].titlu) + 1));
		strcpy(rezultat[i].titlu, vector1[i].titlu);
	}
	for (j = 0; j < dim2; j++) {
		rezultat[i + j] = vector2[j];
		rezultat[i + j].titlu = (char*)malloc(sizeof(char) * (strlen(vector2[j].titlu) + 1));
		strcpy(rezultat[i + j].titlu, vector2[j].titlu);
	}
	return rezultat;
}


void main() {
	int nrCarti = 5;
	struct Carte* carti = (struct Carte*)malloc(sizeof(struct Carte) * nrCarti);
	for (int i = 0; i < nrCarti; i++) {
		carti[i] = initializareCarte("Titlu", 10 * i + 15, 100 * i + 50.5);
	}
	printf("\n\tVectorul de carti initial:\n");
	afisareVector(carti, nrCarti);

	int nrCopiate = 2;
	printf("\n\tVectorul cu primele %d carti:\n", nrCopiate);
	struct Carte* vector = copiazaNcarti(carti, nrCopiate);
	afisareVector(vector, nrCopiate);

	int minPag = 260;
	int nrCartiCond;
	printf("\n\tVectorul cu minim %d pagini\n", minPag);
	struct Carte* CartiMinPag = cartiNrMinimPagini(carti, nrCarti, &nrCartiCond, minPag);
	afisareVector(CartiMinPag, nrCartiCond);

	printf("\n\tCartea cu pretul cautat\n", minPag);
	float pret = 45;
	struct Carte carteCautata = primaCarte(carti, nrCarti, pret);
	afisareCarte(carteCautata);


	printf("\n\tConcatenarea a doi vectori\n");
	int dimNoua = 0;
	struct Carte* concat = concateneazaVectori(vector, nrCopiate, CartiMinPag, nrCartiCond, &dimNoua);
	afisareVector(concat, dimNoua);

	int nrMutate = 0;
	struct Carte* cartiMutate = mutaCarti(&carti, &nrCarti, &nrMutate, 17);

	printf("\n\tDupa mutare avem\n");
	printf("\n\tVectorul de carti initial a devenit:\n");
	afisareVector(carti, nrCarti);
	printf("\n\tVectorul de carti in care s-a mutat:\n");
	afisareVector(cartiMutate, nrMutate);


	dezalocareMemorie(&cartiMutate, &nrMutate);
	dezalocareMemorie(&concat, &dimNoua);
	dezalocareCarte(&carteCautata);
	dezalocareMemorie(&CartiMinPag, &nrCartiCond);
	dezalocareMemorie(&vector, &nrCopiate);
	dezalocareMemorie(&carti, &nrCarti);
}
