#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct country* Cposition;
typedef struct city* cposition;

typedef struct country2* Cposition2;
typedef struct city2* cposition2;

typedef struct country {
	char name[20];
	char filename[20];
	Cposition next;
	cposition root;
}country;

typedef struct country2 {
	char name[20];
	char filename[20];
	Cposition2 left;
	Cposition2 right;
	cposition2 head;
}country2;

typedef struct city {
	char name[20];
	int population;
	cposition left;
	cposition right;
}city;

typedef struct city2 {
	char name[20];
	int population;
	cposition2 next;
}city2;

int AddSortedCountry1(Cposition head,char name[], char countryfile[]);
cposition AddChild1(cposition root, char name[], int population);
int ReadCities1(Cposition head);
int FreeCountry1(Cposition head);
cposition FreeCities1(cposition root);
int PrintCountry1(Cposition head);
int PrintCities1(cposition root);
int FindCountry1(Cposition head,char name[],int population);
int FindCities1(cposition root, int population);

Cposition2 AddChild2(Cposition2 root, char name[], char countryfile[]);
int ReadCities2(Cposition2 root);
cposition2 AddSortedCity2(cposition2 head, char name[], int pop);
Cposition2 FreeCountry2(Cposition2 root);
int FreeCities2(cposition2 head);
int PrintCities2(cposition2 head);
int PrintCountry2(Cposition2 root);
int FindCountry2(Cposition2 root, char name[], int pop);
int FindCities2(cposition head, int pop);


int main() {

	country head = { .name = "",.filename = "",.next = NULL,.root = NULL };
	Cposition2 root = NULL;
	FILE* file;
	char name[20];
	char countryfile[20];
	int op,population;
	file = fopen("drzave.txt", "r");
	if (!file) {
		printf("Neuspjesno otvaranje datoteke!");
		return 1;
	}

	printf("Odaberi rjesenje:\na) - 1\nb) - 2\n");
	scanf("%d", &op);

	while (fscanf(file, "%s %s", name, countryfile)==2) {
		if (op == 1) {
			AddSortedCountry1(&head, name, countryfile);
		}
		else if (op == 2) {
			root = AddChild2(root, name, countryfile);
		}
		else
		{
			printf("Nije odabrana valjana opcija,\n");
			return 1;
		}
	}
	
	if (op == 1) {
		PrintCountry1(&head);
		printf("\nUnesi drzavu za pretragu i minimalan broj stanovnika: ");
		scanf("%s %d", name, &population);
		FindCountry1(&head,name,population);
		FreeCountry1(&head);
	}
	else if (op == 2) {
		PrintCountry2(root);
		printf("\nUnesi drzavu za pretragu i minimalan broj stanovnika: ");
		scanf("%s %d", name, &population);
		FindCountry2(root, name, population);
		FreeCountry2(root);
	}
	fclose(file);
	return 0;
}

int AddSortedCountry1(Cposition head, char name[], char countryfile[]) {

	Cposition p = head;
	Cposition new;
	new = (Cposition)malloc(sizeof(country));
	if (new == NULL) {
		printf("Greska u alociranju memorije!\n");
		return 1;
	}

	while (p->next != NULL && strcmp(name, p->next->name) > 0) {
		p = p->next;
	}

	new->next = p->next;
	p->next = new;

	strcpy(new->name, name);
	strcpy(new->filename, countryfile);
	new->root = NULL;

	ReadCities1(new);

	return 0;
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

	while (fscanf(file, "%s %d", name, &population) ==2) {
		head->root=AddChild1(head->root,name,population);
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

	Cposition p = head->next;
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

	Cposition p = head->next;

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
	printf("%s  (%d)\n", S->name,S->population);
	PrintCities1(S->right);

	return 0;

}

int FindCountry1(Cposition head, char name[],int population) {

	Cposition p = head->next;

	while (p != NULL) {
		if (strcmp(p->name, name) == 0) {
			FindCities1(p->root,population);
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

Cposition2 AddChild2(Cposition2 root, char name[], char countryfile[]) {

	Cposition2 S = root;
	if (S == NULL) {
		S = (Cposition2)malloc(sizeof(country2));
		if (S == NULL) {
			printf("Greska u alociranju!\n");
			return NULL;
		}
		S->left = NULL;
		S->right = NULL;
		S->head = NULL;
		strcpy(S->name, name);
		strcpy(S->filename, countryfile);
		ReadCities2(S);
		return S;
	}
	if (strcmp(name, S->name) < 0) {
		S->left = AddChild2(S->left, name, countryfile);
		return S;
	}
	else if (strcmp(name, S->name) > 0) {
		S->right = AddChild2(S->right, name, countryfile);
		return S;
	}


	return S;
}

int ReadCities2(Cposition2 root) {

	FILE* file;
	char name[20];
	int pop;
	file = fopen(root->filename, "r");
	if (!file) {
		printf("Greska u otvaranju datoteke!");
		return 1;
	}

	while (fscanf(file, "%s %d", name, &pop) == 2) {
		root->head=AddSortedCity2(root->head,name,pop);
	}

	fclose(file);
	return 0;
}

cposition2 AddSortedCity2(cposition2 head, char name[], int pop) {

	cposition2 p = head;
	cposition2 new;
	new = (cposition2)malloc(sizeof(city2));
	if (new == NULL) {
		printf("Greska u alociranju!");
		return head;
	}
	new->next = NULL;
	strcpy(new->name, name);
	new->population = pop;

	if (!p || pop > p->population || (pop == p->population && strcmp(name, p->name) < 0)) {
		new->next=p;
		return new;
	}
	
	while (p->next && (p->next->population>pop ||(p->next->population==pop && strcmp(p->next->name,name)<0))) {
		p = p->next;
	}

	new->next = p->next;
	p->next = new;

	return head;
}

Cposition2 FreeCountry2(Cposition2 root) {

	Cposition2 S = root;

	if (S != NULL) {
		FreeCountry2(S->left);
		FreeCountry2(S->right);
		FreeCities2(S->head);
		free(S);
	}

	return NULL;
}

int FreeCities2(cposition2 head) {

	cposition2 p = head;
	cposition2 temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		temp->next = NULL;
		free(temp);
	}

	return 0;
}

int PrintCountry2(Cposition2 root) {

	Cposition2 S = root;
	if (S == NULL) {
		return 1;
	}

	PrintCountry2(S->left);
	printf("\n\n%s:\n", S->name);
	PrintCities2(S->head);
	PrintCountry2(S->right);

	return 0;

}

int PrintCities2(cposition2 head) {

	cposition2 p = head;

	while (p != NULL) {
		printf("\n%s  (%d)", p->name,p->population);
		p = p->next;
	}

	return 0;
}

int FindCountry2(Cposition2 root, char name[], int pop) {

	Cposition2 S = root;
	if (S == NULL) {
		return 1;
	}
	if (strcmp(name, S->name) < 0) {
		FindCountry2(S->left, name, pop);
	}
	else if (strcmp(name, S->name) > 0) {
		FindCountry2(S->right, name, pop);
	}
	else{
		FindCities2(S->head, pop);
	}

	return 0;
}

int FindCities2(cposition2 head, int pop) {
	
	cposition2 p = head;

	while (p != NULL) {
		if (p->population > pop) {
			printf("\n%s %d", p->name, p->population);
		}
		p = p->next;
	}

	return 0;
}