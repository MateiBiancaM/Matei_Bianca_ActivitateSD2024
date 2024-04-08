#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Biblioteca Biblioteca;
typedef struct NodBiblioteca NodBiblioteca;



struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};

struct NodBiblioteca {
    struct Biblioteca info;
    struct NodBiblioteca* next;
    struct NodBiblioteca* prev;
};

NodBiblioteca* adaugaBiblioteca(NodBiblioteca* lista, Biblioteca biblioteca, int* dimensiune) {
    NodBiblioteca* copie = (NodBiblioteca*)malloc(sizeof(NodBiblioteca));

    copie->info = biblioteca;
    copie->next = NULL;
    copie->prev = NULL;

    if (lista == NULL) {
        return copie;
    }

    NodBiblioteca* temp = lista;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = copie;
    copie->prev = temp;

    (*dimensiune)++;
    return lista;
}

NodBiblioteca* citireFisier(const char* numeFisier, int* nrBiblioteci) {
    NodBiblioteca* listaBiblioteci = NULL;
    FILE* f = fopen(numeFisier, "r");
    if (f != NULL) {
        *nrBiblioteci = 0;
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), f) != NULL) {
            Biblioteca biblioteca;
            char delimitator[] = ",\n";
            char* token = strtok(buffer, delimitator);
            biblioteca.nume = (char*)malloc(strlen(token) + 1);
            strcpy(biblioteca.nume, token);
            token = strtok(NULL, delimitator);
            biblioteca.nrCarti = atoi(token);
            token = strtok(NULL, delimitator);
            biblioteca.nrCititori = atoi(token);
            listaBiblioteci = adaugaBiblioteca(listaBiblioteci, biblioteca, nrBiblioteci);
        }
        fclose(f);
    }
    else {
        printf("Eroare la deschidere");
    }
    return listaBiblioteci;
}

void afisareLista(NodBiblioteca* lista) {
    printf("\nAfisare lista:\n");
    while (lista != NULL) {
        printf("Nume biblioteca: %s; Numar carti: %d; Numar cititori: %d\n", lista->info.nume, lista->info.nrCarti, lista->info.nrCititori);
        lista = lista->next;
    }
}

void stergereNodPozitie(NodBiblioteca** lista, int pozitie) {
    NodBiblioteca* temp = *lista;

    if (temp != NULL && pozitie >= 0) {
        for (int i = 0; temp != NULL && i < pozitie; i++) {
            temp = temp->next;
        }

        if (temp != NULL) {
            if (temp == *lista) {
                if (temp->next == NULL) {
                    *lista = NULL;
                }
                else {
                    *lista = temp->next;
                    (*lista)->prev = NULL;
                }
            }
            else {
                if (temp->next == NULL) {
                    temp->prev->next = NULL;
                }
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
            }

            free(temp->info.nume);
            free(temp);
        }
    }
}


void afisareListaCrescator(NodBiblioteca* lista) {
    printf("\nLista dublu inlantuita (crescator):\n");
    while (lista != NULL) {
        printf("Nume biblioteca: %s; Numar carti: %d; Numar cititori: %d\n", lista->info.nume, lista->info.nrCarti, lista->info.nrCititori);
        lista = lista->next;
    }
}

void afisareListaDescrescator(NodBiblioteca* lista) {
    printf("\nLista dublu inlantuita (descrescator):\n");
    while (lista->next != NULL) {
        lista = lista->next;
    }
    while (lista != NULL) {
        printf("Nume biblioteca: %s; Numar carti: %d; Numar cititori: %d\n", lista->info.nume, lista->info.nrCarti, lista->info.nrCititori);
        lista = lista->prev;
    }
}

NodBiblioteca* filtrareLista(NodBiblioteca* lista, int valoare) {
    NodBiblioteca* listaFiltrata = NULL;
    while (lista != NULL) {
        if (lista->info.nrCarti > valoare) {
            listaFiltrata = adaugaBiblioteca(listaFiltrata, lista->info, &valoare);
        }
        lista = lista->next;
    }
    return listaFiltrata;
}

void interschimbareElemente(NodBiblioteca* lista, int pozitie1, int pozitie2) {
    NodBiblioteca* nod1 = lista;
    NodBiblioteca* nod2 = lista;

    for (int i = 0; i < pozitie1; i++) {
        nod1 = nod1->next;
    }
    for (int i = 0; i < pozitie2; i++) {
        nod2 = nod2->next;
    }
    Biblioteca temp = nod1->info;
    nod1->info = nod2->info;
    nod2->info = temp;
}


void eliberareMemorieLista(NodBiblioteca* lista) {
    while (lista != NULL) {
        NodBiblioteca* temp = lista;
        lista = lista->next;
        free(temp->info.nume);
        free(temp);
    }
}


void main() {
    int nrBiblioteci;
    NodBiblioteca* listaBiblioteci = citireFisier("biblioteca.txt", &nrBiblioteci);

    afisareLista(listaBiblioteci);

    stergereNodPozitie(&listaBiblioteci, 2);
    afisareLista(listaBiblioteci);

    afisareListaCrescator(listaBiblioteci);
    afisareListaDescrescator(listaBiblioteci);

    NodBiblioteca* listaFiltrata = filtrareLista(listaBiblioteci, 100);
    afisareLista(listaFiltrata);

    interschimbareElemente(listaBiblioteci, 1, 2);
    afisareLista(listaBiblioteci);

    eliberareMemorieLista(listaBiblioteci);

}
