#include<stdio.h>
#include<malloc.h>

struct Calculator {
	char* serie;
	float pret;
	int nrPorturi;
};

struct Calculator initializare(const char* serie, float pret, int nrPorturi) {
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	strcpy(c.serie, serie);
	c.nrPorturi = nrPorturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(struct Calculator c) {
	printf("Calculatorul cu seria %s, costa %5.2f si are %d porturi\n", c.serie, c.pret, c.nrPorturi);
}

struct Calculator* CopyNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalcCopy) {
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalcCopy);
	for (int i = 0; i < nrCalcCopy; i++) {
		//copiate[i] = calculatoare[i];//shallow cpy->probleme la dezalocare

		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (1 + strlen(calculatoare[i].serie)));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
	return copiate;
}

void afisareVectorCalculatoare(struct Calculator* vector, int nrCalc) {
	if (nrCalc > 0 && vector != NULL) {
		for (int i = 0; i < nrCalc; i++) {
			afisareCalculator(vector[i]);
		}
	}
}

struct Calculator* CopyCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalc, int pragNrPorturi, int* nrCalcPorturi) {
	*nrCalcPorturi = 0;
	for (int i = 0; i < nrCalc; i++) {
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			(*nrCalcPorturi)++;//deferentiere,altfel modifica adresa
		}
	}
	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalcPorturi));
	int k = 0;
	for (int i = 0; i < nrCalc; i++) {
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);//deep copy
		}
	}
	return v;
}

void dezalocare(struct Calculator** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].serie);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

void main() {
	//int v[10];//alocare statica->stack->ocupa 4*10 octeti intotdeauna
	//int* v1;//pointer catre adresa primului element->ocupa 4

	//declaram un pointer catre structura calculator
	int nrCalc = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalc);
	for (int i = 0; i < nrCalc; i++) {
		calculatoare[i] = initializare("123456789", i * 20 + 10, i + 1);
	}
	afisareVectorCalculatoare(calculatoare, nrCalc);
	printf("\n\n\n\n");
	int nrCalcCpy = 3;
	struct Calculator* calcCopy = CopyNCalculatoare(calculatoare, nrCalc, nrCalcCpy);
	afisareVectorCalculatoare(calcCopy, nrCalcCpy);
	int nrCalcPorturi = 0;
	struct Calculator* calcPorturi = CopyCalculatoareCuMultePorturi(calculatoare, nrCalc, 3, &nrCalcPorturi);
	printf("\n\n\n\n");
	afisareVectorCalculatoare(calcPorturi, nrCalcPorturi);
	dezalocare(&calculatoare, &nrCalc);
}