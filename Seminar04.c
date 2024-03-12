#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));
	copie[(*dimensiune)] = aeroport;
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}

	if (vector)
		free(vector);
	(*dimensiune)++;
	return copie;
}

void afisareAeroport(struct Aeroport* aeroport) {
	if (aeroport != NULL) {
		printf("%d. %s are %d terminale.\t", aeroport->id, aeroport->nume, aeroport->nrTerminale);
	}
	else {
		printf("\nNu exista acest aeroport\n");
	}

}

void afisareVector(struct Aeroport* aeroporturi, int dim) {
	printf("\nAfisare vector\n");
	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}

void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane) {
	for (int i = 0; i < nrClustere; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareAeroport(&matrice[i][j]);
		}
		printf("\n");
	}
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		(*nrAeroporturi) = 0;
		char buffer[100];
		//fgets(buffer, 99, f);
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			//strtok->pentru a face despartirea
			char delimitator[] = ",\n";//, SAU \n
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);//ISI CAUTA EL APELUL ANTERIOR
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);
		}
		fclose(f);
	}
	return vectorAeroporturi;
}

void citireMatriceFisier(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere, struct Aeroport** aeroporturi) {
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			//strtok->pentru a face despartirea
			char delimitator[] = ",\n";//, SAU \n
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);//ISI CAUTA EL APELUL ANTERIOR
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);
			int poz = aeroport.nrTerminale % 2;


			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz]));
		}
		fclose(f);
	}
}


struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int id) {
	for (int i = 0; i < dim; i++) {
		if (aeroporturi[i].id == id)
			return aeroporturi[i];
	}
	struct Aeroport aeroport;
	aeroport.id = -1;
	aeroport.nrTerminale = -1;
	aeroport.nume = malloc(sizeof(char) * (1 + strlen("N/A")));
	strcpy(aeroport.nume, "N/A");
	return aeroport;
}

//stiu in ce cluster ma duc
float mediaTerminale(struct Aeroport** matrice, int* nrAeroporturiLinie, int paritate) {
	paritate = paritate % 2;
	int suma = 0;
	for (int i = 0; i < nrAeroporturiLinie[paritate]; i++) {
		suma += matrice[paritate][i].nrTerminale;
	}
	if (nrAeroporturiLinie[paritate]) {
		return suma / nrAeroporturiLinie[paritate];
	}
	return 0;
}

//fct care returneaza un aeroport dupa id->cautam in toata matricea
struct Aeroport* cautaAeroportID(struct Aeroport** matrice, int* nrColoane, int nrLinii, int Id) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			if (matrice[i][j].id == Id) {
				return &(matrice[i][j]);//ret pointer->tb sa ontinem adresa acelui ob
			}
		}
	}
	return NULL;
}


void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void dezalocareMatrice(struct Aeroprot*** matrice, int** nrColoane, int* nrClustere) {
	for (int i = 0; i < (*nrClustere); i++) {
		dezalocareVector(&((*matrice)[i]), &((*nrColoane)[i]));
	}
	free(*matrice);
	(*matrice) = NULL;
	free(*nrColoane); 
	(*nrColoane) = NULL;
	(*nrClustere) = 0;
}

void main() {
	//declaram matricea in care salvam aeroporturi
	struct Aeroport** aeroporturi;
	//declaram nr de linii si coloane
	int nrLinii = 2;//2 clustere
	int* nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;
	}
	citireMatriceFisier("aeroporturi.txt", nrColoane, nrLinii, aeroporturi);
	afisareMatrice(aeroporturi, nrLinii, nrColoane);
	float medie = mediaTerminale(aeroporturi, nrColoane, 12);
	printf("Media paritate->%.2f", medie);
	printf("\n\n\n");
	afisareAeroport(cautaAeroportID(aeroporturi, nrColoane, nrLinii, 7));
	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);
}