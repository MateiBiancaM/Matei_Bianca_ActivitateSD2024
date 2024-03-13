#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Apartament {
	char* zona;
	int nrCamere;
	float suprafata;
};



struct Apartament initializareApartament(const char* zona, int nrCamere, float suprafata) {
	struct Apartament apartament;
	if (zona != NULL) {
		apartament.zona = malloc(strlen(zona) + 1);
		strcpy(apartament.zona, zona);
	}
	else {
		apartament.zona = malloc(strlen("N\A") + 1);
		strcpy(apartament.zona, "N\A");
	}
	apartament.nrCamere = nrCamere;
	apartament.suprafata = suprafata;
	return apartament;
}

struct Apartament copiereApartament(const struct Apartament* apartament) {
	struct Apartament copie;
	copie.zona = malloc(strlen(apartament->zona) + 1);
	if (copie.zona != NULL) {
		strcpy(copie.zona, apartament->zona);
	}
	copie.nrCamere = apartament->nrCamere;
	copie.suprafata = apartament->suprafata;
	return copie;
}

void afisareApartament(const struct Apartament* apartament) {
	if (apartament->zona) {
		printf("Zona:%s |", apartament->zona);
	}
	else {
		printf("Zona: - |");
	}
	printf(" Nr camere:%d | Suprafata: %.2f \n", apartament->nrCamere, apartament->suprafata);
}

struct Apartament citireApartament() {
	struct Apartament apartament;
	char buffer[50];
	printf("Zona:");
	scanf("%s", buffer);
	apartament.zona = malloc(strlen(buffer) + 1);
	if (apartament.zona != NULL) {
		strcpy(apartament.zona, buffer);
	}
	printf("Nr. camere:");
	scanf("%d", &apartament.nrCamere);
	printf("Suprafata:");
	scanf("%f", &apartament.suprafata);
	return apartament;
}

float costApartament(const struct Apartament apartament, float pretMP) {
	return apartament.suprafata * pretMP;
}

struct Apartament apartamentMulteCamere(const struct Apartament apartament1, const struct Apartament apartament2) {
	struct Apartament apartament;
	if (apartament1.nrCamere > apartament2.nrCamere) {
		return apartament = copiereApartament(&apartament1);
	}
	else {
		return apartament = copiereApartament(&apartament2);
	}
}

void modificaNrCamere(struct Apartament* apartament, int nrCamere) {
	apartament->nrCamere = nrCamere;
}

void dezalocareApartament(struct Apartament* apartament) {
	free(apartament->zona);
	apartament->zona = NULL;
}
void main() {
	struct Apartament apartament = initializareApartament("Militari", 3, 57.5);
	struct Apartament apartament2 = initializareApartament("Obor", 2, 49.7);
	afisareApartament(&apartament);
	afisareApartament(&apartament2);

	struct Apartament apartament3 = citireApartament();
	printf("\nApartament citit de la tastatura:\n");
	afisareApartament(&apartament3);

	float cost = costApartament(apartament2, 1.7);
	printf("\n\Costul total pentru apartamentul dat: %.2f ", cost);
	struct Apartament apartament4 = apartamentMulteCamere(apartament, apartament2);
	printf("\n\nApartamentul cu mai multe camere este:");
	afisareApartament(&apartament4);

	printf("\nDupa modificarea numarului de camera avem:\n");
	modificaNrCamere(&apartament, 4);
	afisareApartament(&apartament);

	dezalocareApartament(&apartament);
	dezalocareApartament(&apartament2);
	dezalocareApartament(&apartament3);
	dezalocareApartament(&apartament4);

	printf("\nApartament dupa dezalocare memorie\n");
	afisareApartament(&apartament2);
}
