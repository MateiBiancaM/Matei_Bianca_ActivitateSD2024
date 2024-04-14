#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
typedef struct Restaurant Restaurant;
typedef struct Nod Nod;

struct Restaurant {
	char* nume;
	int nrLocuri;
	float suprafata;
};

struct Nod {
	Restaurant info;
	Nod* next;
};


Restaurant initializare(const char* nume, int nrLocuri, float suprafata) {
	Restaurant r;
	r.nume = malloc(strlen(nume) + 1);
	strcpy(r.nume, nume);
	r.nrLocuri = nrLocuri;
	r.suprafata = suprafata;
	return r;
}
Nod* inserareInceput(Nod* cap, Restaurant r) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = r;
	nod->next = cap;
	return nod;
}
void inserareSfarsit(Nod** cap, Restaurant r) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = r;
	nod->next = NULL;
	if (*cap) {
		Nod* aux = (*cap);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		(*cap) = nod;
	}
}
char* getNumeRestaurant(Nod* cap, int nrLocuri) {
	while (cap) {
		if (cap->info.nrLocuri == nrLocuri) {
			char* nume = (char*)malloc(strlen(cap->info.nume) + 1);
			strcpy(nume, cap->info.nume);
			return nume;
		}
		cap = cap->next;
	}
	return 0;
}
Nod* inserareSfar(Nod* cap, Restaurant r) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = r;
	nod->next = NULL;
	if (cap) {
		Nod* aux = cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		cap = nod;
	}
	return cap;
}
void inserareIncep(Nod** cap, Restaurant r) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = r;
	nod->next = (*cap);
	(*cap) = nod;
}
Nod* getRestaurant(Nod* cap, const char* nume) {
	while (cap) {
		if (strcmp(cap->info.nume, nume) == 0) {
			return cap;
		}
		cap = cap->next;
	}
	return 0;
}
void inserareRestaurant(Nod** cap, Restaurant r, int nrLoc) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = r;
	nod->next = NULL;
	if (*cap) {
		Nod* aux = *cap;
		while (aux && (aux->info.nrLocuri != nrLoc)) {
			aux = aux->next;
		}
		if (aux->info.nrLocuri == nrLoc) {
			nod->next = aux->next;
		}
		aux->next = nod;
	}
	else {
		*cap = nod;
	}
}
void afisareLista(Nod* cap) {
	while (cap) {
		printf("%s, %d, %.2f\n", cap->info.nume, cap->info.nrLocuri, cap->info.suprafata);
		cap = cap->next;
	}
}
void stergeNodPozitie(Nod** cap, int pozitie) {
	if (*cap) {
		Nod* aux = (*cap);
		if (pozitie == 0) {
			*cap = aux->next;
			free(aux->info.nume);
			free(aux);
		}
		else {
			int index = 0;
			while (aux && index < pozitie - 1) {
				aux = aux->next;
				index++;
			}
			if (aux && aux->next) {
				Nod* nodDeSters = aux->next;
				aux->next = nodDeSters->next;
				free(nodDeSters->info.nume);
				free(nodDeSters);
			}
			else {
				printf("Nu exista nod la acea pozitie");
			}
		}
	}
	else {
		printf("Lista este goala.\n");
	}
}
void stergeLista(Nod** cap) {
	while ((*cap)) {
		free((*cap)->info.nume);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void main() {
	Nod* cap = NULL;
	Restaurant r1 = initializare("Bristo", 57, 80);
	Restaurant r2 = initializare("GerdenPub", 60, 80.7);
	Restaurant r3 = initializare("Proper", 5, 30.5);
	cap = inserareInceput(cap, r1);
	cap = inserareInceput(cap, r2);
	cap = inserareInceput(cap, r3);
	afisareLista(cap);
	Restaurant r4 = initializare("ThePlace", 35, 55.6);
	Restaurant r5 = initializare("Sky", 25, 48.7);
	inserareSfarsit(&cap, r4);
	inserareSfarsit(&cap, r5);
	printf("\n");
	afisareLista(cap);
	char* nume = getNumeRestaurant(cap, 5);
	if (nume) {
		printf("\nRestaurantul cautat este:%s\n", nume);
	}
	else {
		printf("\nNu exista un restaurant cu numarul de locuri specificat\n");
	}
	Nod* cautat = getRestaurant(cap, "Sky");
	if (cautat) {
		printf("\nNume:%s, Nr Locuri:%d, Suprafata:%.2f\n", cautat->info.nume, cautat->info.nrLocuri, cautat->info.suprafata);
	}
	else {
		printf("\nNu exista restaurantul specificat\n");
	}
	Restaurant r6 = initializare("SushiTerra", 34, 90.8);
	inserareRestaurant(&cap, r6, 35);
	printf("\n");
	afisareLista(cap);
	stergeLista(&cap);

}