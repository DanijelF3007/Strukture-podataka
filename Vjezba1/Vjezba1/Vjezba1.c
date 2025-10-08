#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
	char ime[10];
	char prezime[10];
	int bodovi;
}stud;

int main() {
	int i, brojac = 0;
	FILE* lista;
	stud* studenti;

	lista = fopen("Studenti.txt", "r");
	
	if (lista == NULL) {	//provjerava je li datoteka ispravno otvorena
		printf("Greska pri otvaranju datoteke!");
		return 1;
	}
	while (!feof(lista)) {	//prebrojavanje studenata
		if (fgetc(lista) == '\n')
			brojac++;
	}
	brojac++;	//ako datoteka ne zavrsava s novim redom
	printf("\nPostoji %d studenata.\n",brojac);

	rewind(lista);	//vraca datoteku na pocetak za ponovno citanje

	studenti = (stud*)malloc(brojac * sizeof(stud));	//dinamicko alociranje

	for (i = 0; i < brojac; i++) {	//spremanje podataka u strukture
		fscanf(lista,"%s %s %d", &studenti[i].ime, &studenti[i].prezime, &studenti[i].bodovi);
	}
	printf("%-10s %-10s %-10s %-10s\n","Ime","Prezime","Bodovi","Rel.bod.");
	for (i = 0; i < brojac; i++) {	//ispis struktura na ekran
		printf("%-10s %-10s %7d %10.2f\n",studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, ((float)studenti[i].bodovi/50.0)*100.0);
	}
}