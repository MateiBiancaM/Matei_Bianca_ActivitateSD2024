#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Biblioteca Biblioteca;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};


typedef struct Nod Nod;
struct Nod {
    Biblioteca info;
    Nod* next;
    Nod* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    Nod* head;
    Nod* tail;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

void InserareInceput(ListaDubla* listaDubla, Biblioteca b) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = b;
    nod->next = listaDubla->head;
    nod->prev = NULL;
    if (listaDubla->head) {
        listaDubla->head->prev = nod;
    }
    else {
        listaDubla->tail = nod;
    }
    listaDubla->head = nod;
}

void afisareListaInceput(ListaDubla listaDubla) {
    while (listaDubla.head) {
        printf("Biblioteca: %s; Nr cititori: %d; Nr carti: %d\n", listaDubla.head->info.nume, listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
        listaDubla.head = listaDubla.head->next;
    }
    printf("\n");
}

void stergereNodNume(ListaDubla* listaDubla, const char* nume) {
    Nod* aux = listaDubla->head;
    while (aux && strcmp(nume, aux->info.nume) != 0) {
        aux = aux->next;
    }
    if (aux) {
        if (aux == listaDubla->head) {
            if (aux == listaDubla->tail) {
                listaDubla->head = NULL;
                listaDubla->tail = NULL;
            }
            else {
                listaDubla->head = listaDubla->head->next;
                listaDubla->head->prev = NULL;
            }
        }
        else {
            if (aux == listaDubla->tail) {
                aux->prev->next = NULL;
                listaDubla->tail = aux->prev;
            }
            else {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            }
        }
        free(aux->info.nume);
        free(aux);
    }
}

void stergereLista(ListaDubla* listaDubla) {
    while (listaDubla->head) {
        free(listaDubla->head->info.nume);
        Nod* aux = listaDubla->head;
        listaDubla->head = listaDubla->head->next;
        free(aux);
    }
    listaDubla->head = NULL;
    listaDubla->tail = NULL;
}

int nrCartiTotal(ListaDubla listaDubla) {
    int rez = 0;
    while (listaDubla.tail) {
        rez += listaDubla.tail->info.nrCarti;
        listaDubla.tail = listaDubla.tail->prev;
    }
    return rez;
}


void main() {

    Biblioteca b1 = initializare("Mihai Eminescu", 234, 20);
    Biblioteca b2 = initializare("Ioan Slavici", 220, 30);
    Biblioteca b3 = initializare("Ion Creanga", 100, 15);

    ListaDubla listaDubla;
    listaDubla.head = NULL;
    listaDubla.tail = NULL;
    InserareInceput(&listaDubla, b1);
    InserareInceput(&listaDubla, b2);
    InserareInceput(&listaDubla, b3);

    afisareListaInceput(listaDubla);

    /* stergereNodNume(&listaDubla, "Ioan Slavici");
       afisareListaInceput(listaDubla);
       stergereNodNume(&listaDubla, "Mihai Eminescu");
       afisareListaInceput(listaDubla);
       stergereNodNume(&listaDubla, "Ion Creanga");
       afisareListaInceput(listaDubla);*/

    int rez = nrCartiTotal(listaDubla);
    printf("\nTotal nr carti:%d\n", rez);
    stergereLista(&listaDubla);
    afisareListaInceput(listaDubla);

}