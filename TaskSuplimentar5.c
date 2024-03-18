#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Angajat {
	int id;
	char* nume;
	float salariu;
};

struct Nod {
	struct Angajat angajat;
	struct Nod* next;
};

void adaugaNod(struct Nod** cap, struct Angajat angajat) {
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->angajat = angajat;
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		struct Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void afiseazaLista(struct Nod* cap) {
	struct Nod* temp = cap;
	while (temp != NULL) {
		printf("ID: %d, Nume: %s, Salariu: %.2f\n", temp->angajat.id, temp->angajat.nume, temp->angajat.salariu);
		temp = temp->next;
	}
}

struct Nod* stergereElement(struct Nod* inceput, int pozitie) {
	if (inceput == NULL) {
		printf("Lista este goala.\n");
		return NULL;
	}
	if (pozitie == 0) {
		struct Nod* temp = inceput;
		inceput = inceput->next;
		free(temp->angajat.nume);
		free(temp);
		return inceput;
	}
	struct Nod* temp = inceput;
	int index = 0;
	while (temp != NULL && index < pozitie - 1) { // Parcurgem pana la nodul anterior celui care trebuie sters
		temp = temp->next;
		index++;
	}
	if (temp == NULL || temp->next == NULL) {
		printf("Indexul depaseste lungimea listei.\n");
		return inceput;
	}
	struct Nod* nodDeSters = temp->next;
	temp->next = temp->next->next; // Eliminam nodul din lista
	free(nodDeSters->angajat.nume);
	free(nodDeSters);
	return inceput;
}

void sortareLista(struct Nod** cap) {
	if (*cap == NULL || (*cap)->next == NULL) {
		return;
	}

	struct Nod* sortat = NULL;
	struct Nod* current = *cap;
	struct Nod* nextNode = NULL;

	while (current != NULL) {
		nextNode = current->next;
		if (sortat == NULL || sortat->angajat.salariu >= current->angajat.salariu) {
			current->next = sortat;
			sortat = current;
		}
		else {
			struct Nod* temp = sortat;
			while (temp->next != NULL && temp->next->angajat.salariu < current->angajat.salariu) {
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
		current = nextNode;
	}
	*cap = sortat;
}


void inserareSortata(struct Nod** cap, struct Angajat angajat) {
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->angajat = angajat;
	nou->next = NULL;
	if (*cap == NULL || (*cap)->angajat.salariu >= angajat.salariu) {
		nou->next = *cap;
		*cap = nou;
	}
	else {
		struct Nod* temp = *cap;
		while (temp->next != NULL && temp->next->angajat.salariu < angajat.salariu) {
			temp = temp->next;
		}
		nou->next = temp->next;
		temp->next = nou;
	}
}

void copieInVector(struct Nod* cap, struct Angajat** vector, int* dimensiune, float pragSalariu) {
	int index = 0;
	struct Nod* temp = cap;
	while (temp != NULL) {
		if (temp->angajat.salariu > pragSalariu) {
			(*dimensiune)++;
		}
		temp = temp->next;
	}
	*vector = (struct Angajat*)malloc((*dimensiune) * sizeof(struct Angajat));
	if (*vector == NULL) {
		printf("Eroare la alocarea memoriei pentru vector.\n");
		return;
	}
	temp = cap;
	while (temp != NULL) {
		if (temp->angajat.salariu > pragSalariu) {
			(*vector)[index].id = temp->angajat.id;
			(*vector)[index].nume = (char*)malloc(strlen(temp->angajat.nume) + 1);
			strcpy((*vector)[index].nume, temp->angajat.nume);
			(*vector)[index].salariu = temp->angajat.salariu;
			index++;
		}
		temp = temp->next;
	}
}

void interschimbaPozitii(struct Angajat** cap, int pozitie1, int pozitie2) {
	if (*cap == NULL) {
		printf("Lista este goala.\n");
		return;
	}

	if (pozitie1 == pozitie2) {
		printf("Pozitiile sunt identice.\n");
		return;
	}

	struct Nod* temp1 = *cap;
	struct Nod* temp2 = *cap;
	struct Nod* nodAnterior1 = NULL;
	struct Nod* nodAnterior2 = NULL;
	//nodurile precedente pentru pozitii
	for (int i = 0; temp1 != NULL && i < pozitie1; i++) {
		nodAnterior1 = temp1;
		temp1 = temp1->next;
	}
	for (int i = 0; temp2 != NULL && i < pozitie2; i++) {
		nodAnterior2 = temp2;
		temp2 = temp2->next;
	}
	if (temp1 == NULL || temp2 == NULL) {
		printf("Pozitii invalide.\n");
		return;
	}

	if (nodAnterior1 != NULL) {
		nodAnterior1->next = temp2;
	}
	else {
		*cap = temp2;
	}
	if (nodAnterior2 != NULL) {
		nodAnterior2->next = temp1;
	}
	else {
		*cap = temp1;
	}

	struct Angajat* tempNext = temp1->next;
	temp1->next = temp2->next;
	temp2->next = tempNext;
}

void main() {
	FILE* f = fopen("angajati.txt", "r");
	struct Nod* lista = NULL;
	if (f != NULL) {

		int id;
		char nume[100];
		float salariu;
		while (fscanf(f, "%d %s %f", &id, nume, &salariu) == 3) {
			struct Angajat angajat;
			angajat.id = id;
			angajat.nume = (char*)malloc(strlen(nume) + 1);
			strcpy(angajat.nume, nume);
			angajat.salariu = salariu;
			adaugaNod(&lista, angajat);
		}
		fclose(f);
	}
	else {
		printf("Eroare la deschidere");
	}
	printf("\nLista angajatiilor\n");
	afiseazaLista(lista);
	lista = stergereElement(lista, 2);
	printf("\nLista angajatiilor dupa stergere\n");
	afiseazaLista(lista);

	sortareLista(&lista);
	printf("\nLista angajatiilor dupa sortare\n");
	afiseazaLista(lista);

	struct Angajat nouAngajat = { 6, "Tudor", 440.7 };
	inserareSortata(&lista, nouAngajat);
	printf("\nLista sortata a angajatilor dupa inserarea angajatului nou:\n");
	afiseazaLista(lista);

	float prag = 340;
	struct Angajat* vector = (struct Angajat*)malloc(sizeof(struct Angajat) * 10);
	int dimensiune = 0;
	copieInVector(lista, &vector, &dimensiune, prag);
	printf("\nVector angajati cu salariu mai mare decat %.2f:\n", prag);
	for (int i = 0; i < dimensiune; ++i) {
		printf("ID: %d, Nume: %s, Salariu: %.2f\n", vector[i].id, vector[i].nume, vector[i].salariu);
	}

	printf("\n\nLista angajatiilor inainte de interschimbarea pozitiilor\n");
	afiseazaLista(lista);
	interschimbaPozitii(&lista, 1, 2);
	printf("\nLista angajatiilor dupa interschimbarea pozitiilor\n");
	afiseazaLista(lista);



	for (int i = 0; i < dimensiune; ++i) {
		free(vector[i].nume);
	}
	free(vector);

}