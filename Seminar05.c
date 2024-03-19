#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};

struct Nod {
    Biblioteca info;
    Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = initializare(b.nume, b.nrCarti, b.nrCititori);//deep cpy
    nou->next = cap;
    return nou;
}

void afisareLista(Nod* cap) {
    while (cap != NULL) {
        //procesare
        printf("Biblioteca %s are %d carti si %d cititri\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
        cap = cap->next;//deplasare
    }
}

//fct procesare:det nr bibliotecii cu cele mai multe carti/cititor ca medie
char* getBibliotecaNrCartiPerCititor(Nod* cap) {
    float max = 0;
    char* nume_aux = NULL;
    while (cap) {
        //procesare
        if (cap->info.nrCititori / cap->info.nrCititori > max) {
            max = cap->info.nrCititori / cap->info.nrCititori;
            nume_aux = cap->info.nume;
        }
        //deplasare
        cap = cap->next;
    }
    char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
    strcpy(nume, nume_aux);
    return nume;
}

//inserare la sfarsitul listei
void inserareSfarsit(Nod** cap, Biblioteca biblioteca) {
    Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
    sfarsit->next = NULL;
    sfarsit->info = initializare(biblioteca.nume, biblioteca.nrCarti, biblioteca.nrCititori);

    if ((*cap) != NULL) {
        Nod* aux = (*cap);
        while (aux->next != NULL) {//deplasarea
            aux = aux->next;
        }
        //legatura
        aux->next = sfarsit;
    }
    else {
        (*cap) = sfarsit;
    }
}

void stergereLista(Nod** cap) {
    while ((*cap) != NULL) {
        free((*cap)->info.nume);
        Nod* copie = *cap;
        *cap = (*cap)->next;
        free(copie);
    }
}
void main() {
    //declarare lista-adresa primului nod
    Nod* cap = NULL;
    Biblioteca b1 = initializare("Mihai Eminescu", 234, 20);
    cap = inserareInceput(cap, b1);
    Biblioteca b2 = initializare("Ioan Slavici", 220, 30);
    cap = inserareInceput(cap, b2);
    Biblioteca b3 = initializare("Ion Creanga", 100, 15);
    cap = inserareInceput(cap, b3);
    afisareLista(cap);
    char* numeAfisat = getBibliotecaNrCartiPerCititor(cap);
    printf("\nBiblioteca cu media max:%s\n", numeAfisat);
    free(numeAfisat);
    printf("\n");
    inserareSfarsit(&cap, b3);
    afisareLista(cap);

    stergereLista(&cap);
    afisareLista(cap);
    free(b1.nume);
    free(b2.nume);
    free(b3.nume);

}