#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Elev Elev;
struct Elev {
	int id;
	int nrMedii;
	float* medii;
};
typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* st;
	Nod* dr;
};

Nod* rotireDreapta(Nod* radacina) {
	Nod* nod;
	nod = radacina->st;
	radacina->st = nod->dr;
	nod->dr = radacina;
	//radacina = nod; 
	return nod;
}


Nod* rotireStanga(Nod* radacina) {
	Nod* nod;
	//metoda paharelor
	nod = radacina->dr;
	radacina->dr = nod->st;
	nod->st = radacina;
	return nod;
}
void inserareArbore(Nod** radacina, Elev elev) {
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > elev.id) {
			inserareArbore(&((*radacina)->st), elev);
		}
		else {
			inserareArbore(&((*radacina)->dr), elev);
		}
		int grad = gradEchilibru(*radacina);
		if (grad == 2) {//dezechilibru stanga stanga
			//rotire stanga
			if (gradEchilibru((*radacina)->st) == 1) {//dezechilibru simplu
				(*radacina) = rotireDreapta(*radacina);
			}
			else {
				(*radacina)->st = rotireStanga((*radacina)->st);
				//rotire dreapta
				(*radacina) = rotireDreapta(*radacina);
			}
		}
		else if (grad == -2) {
			//if (gradEchilibru(*radacina->dr) == 1)//situatia complexa:dez. dr=>rotire dr
			//{
			//	(*radacina)->dr = rotireDreapta((*radacina)->dr); 
			//	(*radacina) = rotireStanga(*radacina); 
			//}
			//else {
			//	(*radacina) = rotireStanga(*radacina);
			//}
			if (gradEchilibru((*radacina)->dr) == 1) {
				(*radacina)->dr = rotireDreapta((*radacina)->dr);

			}
			(*radacina) = rotireStanga(*radacina);

		}
	}
	else {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = elev;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
	}
}

Elev citireElev(FILE* f) {
	Elev e;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);
	e.medii = malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(f, "%f", &(e.medii[i]));
	}
	return e;
}

Nod* citireFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	if (!numeFisier) {
		return NULL;
	}
	else {
		FILE* f = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(f, "%d", &nrElevi);
		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(f);
			inserareArbore(&arbore, e);
		}
		fclose(f);
	}
	return arbore;

}
void afisareElev(Elev e) {
	printf("Id: %d  Nr note: %d cu mediile:", e.id, e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("%3.2f ", e.medii[i]);
	}
	printf("\n");
}


void afisareInOrder(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);
	}
}

float calculeazaMedieElev(Elev e) {
	if (e.nrMedii != 0) {
		float suma = 0;
		for (int i = 0; i < e.nrMedii; i++) {
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	else {
		return 0;
	}

}

float calculeazaSumaNote(Nod* arbore, int* nrNote) {
	if (arbore != NULL) {
		float suma = 0;
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];
		}
		(*nrNote) += arbore->info.nrMedii;
		float sumastg = calculeazaSumaNote(arbore->st, nrNote);
		float sumadr = calculeazaSumaNote(arbore->dr, nrNote);
		return suma + sumadr + sumastg;
	}
	else {
		return 0;
	}
}
float calculeazaMediaGenerala(Nod* arbore) {
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	printf("\n %d \n", nrNote);
	if (nrNote > 0) {
		return suma / nrNote;
	}
	else {
		return 0;
	}

}


int inaltime(Nod* radacina) {
	if (radacina == NULL)
		return 0;
	else {
		int inaltimeSt = inaltime(radacina->st);
		int inaltimeDr = inaltime(radacina->dr);
		/*if (inaltimeSt > inaltimeDr) {
			return 1 + inaltimeSt;
		}
		else {
			return 1 + inaltimeDr;
		}*/
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
}

int gradEchilibru(Nod* radacina) {
	int inaltimeSt = inaltime(radacina->st);
	int inaltimeDr = inaltime(radacina->dr);
	return inaltimeSt - inaltimeDr;
}

afisarePreordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareElev(radacina->info);
		afisarePreordine(radacina->st);
		afisarePreordine(radacina->dr);
	}
}


void dezalocareArbore(Nod** radacina) {
	if (*radacina) {
		//parcurgere postordine
		dezalocareArbore(&((*radacina)->st));
		dezalocareArbore(&((*radacina)->dr));
		free((*radacina)->info.nrMedii);
		free(*radacina);
		(*radacina) = NULL;
	}
}


void main() {
	Nod* arbore = NULL;
	arbore = citireFisier("elevi.txt");
	afisareInOrder(arbore);
	printf("Media este %5.2f \n", calculeazaMediaGenerala(arbore));
	afisarePreordine(arbore);
	dezalocareArbore(&arbore);
	afisareInOrder(arbore);
}