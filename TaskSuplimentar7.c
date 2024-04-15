#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cladire Cladire;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Cladire {
	int id;
	int anConstruire;
	char* zona;
};
struct Nod {
	Cladire info;
	Nod* next;
};
struct HashTable {
	Nod** vector;
	int dim;
};

Cladire initializareCladire(int id, int anConstructie, const char* zona) {
	Cladire c;
	c.id = id;
	c.anConstruire = anConstructie;
	c.zona = (char*)malloc(strlen(zona) + 1);
	strcpy(c.zona, zona);
	return c;
}
HashTable initializareTabela(int dimensiune) {
	HashTable tabela;
	tabela.dim = dimensiune;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		tabela.vector[i] = NULL;
	}
	return tabela;
}

int calculHash(int an, int dim) {
	if (dim > 0) {
		return an % dim;
	}
	return -1;
}

void inserareSfarsit(Nod** cap, Cladire c) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = c;
	nod->next = NULL;
	if (*cap) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		*cap = nod;
	}
}

void inserareCladireInTabela(HashTable tabela, Cladire c) {
	if (tabela.dim > 0) {
		int poz = calculHash(c.anConstruire, tabela.dim);
		if (tabela.vector[poz]) {
			inserareSfarsit(&(tabela.vector[poz]), c);
		}
		else {
			inserareSfarsit(&(tabela.vector[poz]), c);
		}
	}
}

void afisareCladire(Cladire c) {
	printf("	Id:%d An:%d Zona:%s\n", c.id, c.anConstruire, c.zona);
}
void afisareLista(Nod* cap) {
	while (cap) {
		afisareCladire(cap->info);
		cap = cap->next;
	}
}

void afisareTabelaHash(HashTable tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		if (tabela.vector[i]) {
			printf("\nCluster %d\n", i + 1);
			afisareLista(tabela.vector[i]);
		}
	}
}

void afisareCladiriAnDat(HashTable tabela, int an) {
	int poz = calculHash(an, tabela.dim);
	if (poz >= 0 && poz < tabela.dim) {
		Nod* aux = tabela.vector[poz];
		printf("\nCladirile corespunzatoare anului %d:\n", an);
		while (aux) {
			if (aux->info.anConstruire == an) {
				afisareCladire(aux->info);
			}
			aux = aux->next;
		}
	}
	else {
		printf("Clusterul pentru anul %d nu exista.\n", an);
	}
}

void stergereIdSiAn(HashTable tabela, int id, int an) {
	int poz = calculHash(an, tabela.dim);
	if (poz >= 0 && poz < tabela.dim) {
		Nod* prev = NULL;
		Nod* nod = tabela.vector[poz];
		while (nod && nod->info.id != id && nod->info.anConstruire != an) {
			prev = nod;
			nod = nod->next;
		}
		if (nod) {
			if (prev == NULL) {
				tabela.vector[poz] = nod->next;
			}
			else {
				prev->next = nod->next;
			}
			free(nod->info.zona);
			free(nod);
			printf("\nSters");
		}
	}
}

void stergereDupaId(HashTable tabela, int id) {
	for (int i = 0; i < tabela.dim; i++) {
		Nod* prev = NULL;
		Nod* nod = tabela.vector[i];
		while (nod && nod->info.id != id) {
			prev = nod;
			nod = nod->next;
		}
		if (nod) {
			if (prev == NULL) {
				tabela.vector[i] = nod->next;
			}
			else {
				prev->next = nod->next;
			}
			free(nod->info.zona);
			free(nod);
			printf("\nSters");
		}
	}
}


Cladire* vectorCladiriAnDat(HashTable tabela, int an, int* nrCladiri) {
	*nrCladiri = 0;
	for (int i = 0; i < tabela.dim; i++) {
		Nod* nod = tabela.vector[i];
		while (nod) {
			if (nod->info.anConstruire == an) {
				(*nrCladiri)++;
			}
			nod = nod->next;
		}
	}
	Cladire* vector = (Cladire*)malloc(sizeof(Cladire) * (*nrCladiri));
	int k = 0;

	for (int i = 0; i < tabela.dim; i++) {
		Nod* nod = tabela.vector[i];
		while (nod) {
			if (nod->info.anConstruire == an) {
				vector[k] = initializareCladire(nod->info.id, nod->info.anConstruire, nod->info.zona);
				k++;

			}
			nod = nod->next;
		}
	}
	return vector;
}





void dezalocareLista(Nod** cap) {
	while (*cap) {
		free((*cap)->info.zona);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void dezalocareTabela(HashTable* tabela) {
	for (int i = 0; i < tabela->dim; i++) {
		if (tabela->vector[i]) {
			dezalocareLista(&(tabela->vector[i]));
			tabela->vector[i] = NULL;
		}
	}
	free(tabela->vector);
	tabela->vector = NULL;
	tabela->dim = 0;
}

void main() {
	HashTable tabela = initializareTabela(5);
	Cladire c1 = initializareCladire(1, 2000, "Piata Romana");
	Cladire c2 = initializareCladire(2, 2019, "Militari");
	Cladire c3 = initializareCladire(3, 1998, "Obor");
	Cladire c4 = initializareCladire(4, 2000, "Piata Sudului");
	Cladire c5 = initializareCladire(5, 1998, "Berceni");
	Cladire c6 = initializareCladire(6, 2000, "Aviatorilor");

	inserareCladireInTabela(tabela, c1);
	inserareCladireInTabela(tabela, c2);
	inserareCladireInTabela(tabela, c3);
	inserareCladireInTabela(tabela, c4);
	inserareCladireInTabela(tabela, c5);
	inserareCladireInTabela(tabela, c6);
	printf("\n\tTabela:\n");
	afisareTabelaHash(tabela);
	afisareCladiriAnDat(tabela, 1998);
	stergereIdSiAn(tabela, 5, 1998);
	stergereDupaId(tabela, 1);
	printf("\n\tTabela dupa stergeri:\n");
	afisareTabelaHash(tabela);
	int nr = 0;
	Cladire* vector = vectorCladiriAnDat(tabela, 2000, &nr);
	printf("\nVECTORUL\n");
	for (int i = 0; i < nr; i++) {
		printf("%d %d %s\n", vector[i].id, vector[i].anConstruire, vector[i].zona);
	}
	for (int i = 0; i < nr; i++) {
		free(vector[i].zona);
	}
	free(vector);
	dezalocareTabela(&tabela);
}