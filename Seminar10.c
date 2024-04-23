#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
//Arbori Binari De Cautare
//arbore=graf conex aciclic
//binar=arbore cu maxim 2 descendenti
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

void inserareArbore(Nod** radacina, Elev elev) {
	//verif e facuta in toate fct care lucreaza cu arbori,inserarea e mereu intr-un nod frunza
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > elev.id) {
			inserareArbore(&((*radacina)->st), elev);
		}
		else {
			inserareArbore(&((*radacina)->dr), elev);
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
//funct care citeste acesti elevi dintr-un fisier
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

//afisare
//in ordine->St,rad,dr
//pre ordine->rad,st,dr
//post ordine->st,dr,rad
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
		//radacina
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];
		}
		(*nrNote) += arbore->info.nrMedii;
		//stanga
		float sumastg = calculeazaSumaNote(arbore->st, nrNote);
		//dreapta
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
void main() {
	//Declareare arbore->il identificam prin adresa primului nod
	Nod* arbore = NULL;
	arbore = citireFisier("elevi.txt");
	afisareInOrder(arbore);
	printf("Media este %5.2f \n", calculeazaMediaGenerala(arbore));

}