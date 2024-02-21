#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

// Nume: Matei Maria => M si M => Articolul:Marmelada
struct Marmelada {
    int nrSortimente;
    char** sortimente;
    float* preturi;
};

// Functia pentru citirea de la tastatura a articolului creat
struct Marmelada citesteArticol() {

    struct Marmelada marmelada;
    printf("Introduceti numarul de sortimente de marmelada: ");
    scanf("%d", &marmelada.nrSortimente);
    marmelada.sortimente = (char**)malloc(marmelada.nrSortimente * sizeof(char*));
    marmelada.preturi = (float*)malloc(marmelada.nrSortimente * sizeof(float));
    for (int i = 0; i < marmelada.nrSortimente; i++) {
        marmelada.sortimente[i] = (char*)malloc(50 * sizeof(char));
        printf("Introduceti denumirea pentru sortimentul %d: ", i + 1);
        scanf("%s", marmelada.sortimente[i]);
        printf("Introduceti pretul pentru sortimentul %d: ", i + 1);
        scanf("%f", &marmelada.preturi[i]);
    }
    return marmelada;
}

// Functie pentru calcularea mediei preturilor pentru obiectul creat
float calculeazaMedie(struct Marmelada marmelada) {
    float suma = 0.0;
    for (int i = 0; i < marmelada.nrSortimente; i++) {
        suma += marmelada.preturi[i];
    }
    return suma / marmelada.nrSortimente;
}

// Functie pentru modificarea pretului sortimentului
void modificaPret(struct Marmelada* marmelada, float noulPret, int indexSortiment) {
    marmelada->preturi[indexSortiment] = noulPret;
}

// Functie pentru afisarea sortimentului de marmelada
void afiseazaArticol(struct Marmelada marmelada) {
    printf("\nSortimentele de marmelada:\n");
    for (int i = 0; i < marmelada.nrSortimente; i++) {
        printf("Sortimentul %d: %s are pretul: %.2f lei\n", i + 1, marmelada.sortimente[i], marmelada.preturi[i]);
    }
}

int main() {

    struct Marmelada marmeladaCitita = citesteArticol();
    afiseazaArticol(marmeladaCitita);
    modificaPret(&marmeladaCitita, 21.5, 0);
    printf("\nDupa modificare:\n");
    afiseazaArticol(marmeladaCitita);
    printf("\nMedia preturilor: %.2f lei\n", calculeazaMedie(marmeladaCitita));
    for (int i = 0; i < marmeladaCitita.nrSortimente; i++) {
        free(marmeladaCitita.sortimente[i]);
    }
    free(marmeladaCitita.sortimente);
    free(marmeladaCitita.preturi);
    return 0;

}