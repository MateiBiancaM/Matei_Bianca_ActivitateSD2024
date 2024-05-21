#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Pacient Pacient; 
typedef struct Heap Heap;

struct Pacient {
    char* name;
    char* condition;
    int urgency;
};

struct Heap {
    Pacient* vector;
    int dimensiune;
    int dimensiuneTotala;
};

Pacient initPacient(const char* name, const char* condition, int urgency) {
    Pacient p;
    p.name = malloc(sizeof(char) * (1 + strlen(name)));
    strcpy(p.name, name);
    p.condition = malloc(sizeof(char) * (1 + strlen(condition)));
    strcpy(p.condition, condition);
    p.urgency = urgency;
    return p;
}

Heap initHeap(int dimensiune) {
    Heap h;
    h.vector = malloc(sizeof(Pacient) * dimensiune);
    h.dimensiune = 0;
    h.dimensiuneTotala = dimensiune;
    return h;
}

void afisarePacient(Pacient p) {
    printf("Pacientul %s cu conditia %s are urgenta %d\n", p.name, p.condition, p.urgency);
}

void afisareHeap(Heap h) {
    for (int i = 0; i < h.dimensiune; i++) {
        afisarePacient(h.vector[i]);
    }
}

void filtrareHeap(Heap h, int poz) {
    int poz_s = poz * 2 + 1;
    int poz_d = poz * 2 + 2;
    int poz_m = poz;
    if (poz_s < h.dimensiune && h.vector[poz_s].urgency > h.vector[poz_m].urgency) {
        poz_m = poz_s;
    }
    if (poz_d < h.dimensiune && h.vector[poz_d].urgency > h.vector[poz_m].urgency) {
        poz_m = poz_d;
    }
    if (poz_m != poz) {
        Pacient aux = h.vector[poz];
        h.vector[poz] = h.vector[poz_m];
        h.vector[poz_m] = aux;
        if (poz_m * 2 + 1 < h.dimensiune) {
            filtrareHeap(h, poz_m);
        }
    }
}

Pacient ExtragereHeap(Heap* h) {
    if (h->dimensiune > 0) {
        Pacient aux = h->vector[0];
        h->vector[0] = h->vector[h->dimensiune - 1];
        h->vector[h->dimensiune - 1] = aux;
        h->dimensiune--;
        for (int i = h->dimensiune / 2; i >= 0; i--) {
            filtrareHeap(*h, i);
        }
        return aux;
    }
}

void afisareHeapTotala(Heap h) {
    for (int i = 0; i < h.dimensiuneTotala; i++) {
        afisarePacient(h.vector[i]);
    }
}

void DezalocareHeap(Heap* h) {
    if (h->vector != NULL) {
        while (h->dimensiuneTotala > 0) {
            free(h->vector[h->dimensiuneTotala - 1].name);
            free(h->vector[h->dimensiuneTotala - 1].condition);
            h->dimensiuneTotala--;
        }
        free(h->vector);
        h->vector = NULL;
        h->dimensiune = 0;
    }
}

void main() {
    Heap h = initHeap(6);

    h.vector[0] = initPacient("Ioana", "Critic", 5);
    h.vector[1] = initPacient("Andrei", "Moderat", 3);
    h.vector[2] = initPacient("Maria", "Sever", 4);
    h.vector[3] = initPacient("Alex", "Usor", 2);
    h.vector[4] = initPacient("Ionut", "Critic", 5);
    h.vector[5] = initPacient("Cosmin", "Sever", 4);
    h.dimensiune = 6;

    printf("Initial:\n");
    afisareHeap(h);
    //max-heap
    for (int i = (h.dimensiune / 2) - 1; i >= 0; i--) {
        filtrareHeap(h, i);
    }

    printf("\n---afisare heap---\n");
    afisareHeap(h);

    printf("\n------\n");
    afisarePacient(ExtragereHeap(&h));
    afisarePacient(ExtragereHeap(&h));
    afisarePacient(ExtragereHeap(&h));
    afisarePacient(ExtragereHeap(&h));
    afisarePacient(ExtragereHeap(&h));
    afisarePacient(ExtragereHeap(&h));

    printf("\n------\n");
    afisareHeapTotala(h);
    DezalocareHeap(&h);
}
