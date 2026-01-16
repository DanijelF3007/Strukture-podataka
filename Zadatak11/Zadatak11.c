#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct country* Cposition;
typedef struct city* cposition;

typedef struct country {
	char name[20];
	char filename[20];
	Cposition next;
	cposition root;
}country;

typedef struct city {
	char name[20];
	int population;
	cposition left;
	cposition right;
}city;

Cposition AddSortedCountry1(Cposition head, char name[], char countryfile[]);
cposition AddChild1(cposition root, char name[], int population);
int ReadCities1(Cposition head);
int FreeCountry1(Cposition head);
cposition FreeCities1(cposition root);
int PrintCountry1(Cposition head);
int PrintCities1(cposition root);
int FindCountry1(Cposition head, char name[], int population);
int FindCities1(cposition root, int population);

int HashFunction(char name[]);

int main() {

	Cposition hashTable[11] = { NULL };
	FILE* file;
	char name[20];
	char countryfile[20];
	int population,index,i;
	file = fopen("drzave.txt", "r");
	if (!file) {
		printf("Neuspjesno otvaranje datoteke!");
		return 1;
	}

	while (fscanf(file, "%s %s", name, countryfile) == 2) {
		index = HashFunction(name);
		hashTable[index]=AddSortedCountry1(hashTable[index], name, countryfile);
	}

	for(i=0;i<11;i++){
		PrintCountry1(hashTable[i]);
	}
	printf("\nUnesi drzavu za pretragu i minimalan broj stanovnika: ");
	scanf("%s %d", name, &population);
	index = HashFunction(name);
	FindCountry1(hashTable[index], name, population);
	for(i=0;i<11;i++){
		FreeCountry1(hashTable[i]);
	}
	
	fclose(file);
	return 0;
}

int HashFunction(char name[]) {

	int sum = 0;
	int i;

	for (i = 0; i < 5; i++) {
		sum = sum + (int)name[i];
	}

	return sum % 11;
	
}

Cposition AddSortedCountry1(Cposition head, char name[], char countryfile[]) {

	Cposition p = head;
	Cposition new;
	new = (Cposition)malloc(sizeof(country));
	if (new == NULL) {
		printf("Greska u alociranju memorije!\n");
		return head;
	}

	strcpy(new->name, name);
	strcpy(new->filename, countryfile);
	new->root = NULL;
	new->next = NULL;

	ReadCities1(new);

	if (p == NULL) {
		return new;
	}

	if (strcmp(name, p->name) < 0) {
		new->next = p;
		return new;
	}

	while (p->next != NULL && strcmp(name, p->next->name) > 0) {
		p = p->next;
	}

	new->next = p->next;
	p->next = new;

	return head;
}

int ReadCities1(Cposition head) {

	FILE* file;
	file = fopen(head->filename, "r");
	if (file == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return 1;
	}
	char name[20];
	int population;

	while (fscanf(file, "%s %d", name, &population) == 2) {
		head->root = AddChild1(head->root, name, population);
	}

	fclose(file);
	return 0;
}

cposition AddChild1(cposition root, char name[], int population) {

	cposition S = root;
	if (S == NULL) {
		S = (cposition)malloc(sizeof(city));
		if (S == NULL) {
			printf("Greska u alociranju memorije!\n");
			return NULL;
		}
		S->left = NULL;
		S->right = NULL;
		strcpy(S->name, name);
		S->population = population;
		return S;
	}
	if (population < S->population) {
		S->left = AddChild1(S->left, name, population);
		return S;
	}
	else if (population > S->population) {
		S->right = AddChild1(S->right, name, population);
		return S;
	}
	else if (population == S->population) {
		if (strcmp(name, S->name) < 0) {
			S->left = AddChild1(S->left, name, population);
		}
		else {
			S->right = AddChild1(S->right, name, population);
		}
	}

	return S;
}

int FreeCountry1(Cposition head) {

	Cposition p = head;
	Cposition temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		temp->next = NULL;
		FreeCities1(temp->root);
		free(temp);
	}

	return 0;
}

cposition FreeCities1(cposition root) {

	cposition S = root;

	if (S != NULL) {
		FreeCities1(S->left);
		FreeCities1(S->right);
		free(S);
	}

	return NULL;
}

int PrintCountry1(Cposition head) {

	Cposition p = head;

	while (p != NULL) {
		printf("\n%s:\n", p->name);
		PrintCities1(p->root);
		p = p->next;
	}

	return 0;
}

int PrintCities1(cposition root) {

	cposition S = root;
	if (S == NULL) {
		return 1;
	}

	PrintCities1(S->left);
	printf("%s  (%d)\n", S->name, S->population);
	PrintCities1(S->right);

	return 0;

}

int FindCountry1(Cposition head, char name[], int population) {

	Cposition p = head;

	while (p != NULL) {
		if (strcmp(p->name, name) == 0) {
			FindCities1(p->root, population);
		}
		p = p->next;
	}

	return 0;
}

int FindCities1(cposition root, int population) {

	cposition S = root;
	if (S == NULL) {
		return 1;
	}

	if (S->population > population) {
		FindCities1(S->left, population);
		printf("%s %d\n", S->name, S->population);
		FindCities1(S->right, population);
	}
	else {
		FindCities1(S->right, population);
	}

	return 0;
}