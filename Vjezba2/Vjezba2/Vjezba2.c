#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
	char name[10];
	char surname[10];
	int yob;
	struct Person* next;
}person;

void InsertFirst(person* p,char* name, char* surname, int yob);
void PrintList(person* head);
void InsertLast(person* p, char* name, char* surname, int yob);
void Find(person* p, char* surname);
void Delete(person* p, char* surname);
void FreeList(person* head);

int main() {

	person head;
	person* p = &head;
	p->next = NULL;
	int op;
	char name[10];
	char surname[10];
	int yob;

	start:
	printf("Odaberi opciju za rad nad listom:\nUbaci element na pocetak - 1\nUbaci element na kraj - 2\n");
	printf("Ispis liste - 3\nPronadi element u listi - 4\nIzbrisi element - 5\nIzadi iz programa - 6\n");
	scanf("%d",&op);
	if (op < 1 || op>6) {
		printf("Nije odabrana valjana opcija. Ponovi.\n");
		goto start;
	}
	switch (op) {
	case 1:
		printf("Unesi element u formatu (ime prezime god): ");
		scanf("%s %s %d",name,surname,&yob);
		InsertFirst(p, name, surname, yob);
		goto start;
	case 2:
		printf("Unesi element u formatu (ime prezime god): ");
		scanf("%s %s %d", name, surname, &yob);
		InsertLast(p, name, surname, yob);
		goto start;
	case 3:
		PrintList(p);
		goto start;
	case 4:
		printf("Unesi prezime elementa za trazenje: ");
		scanf("%s", surname);
		Find(p, surname);
		goto start;
	case 5:
		printf("Unesi prezime elementa za brisanje: ");
		scanf("%s", surname);
		Delete(p, surname);
		goto start;
	case 6:
		printf("Izlaz iz programa...\n");
		exit(1);
	default:
		printf("Greska! Ponovi.\n");
		goto start;
	}
	FreeList(p);

	return 0;
}

void InsertFirst(person* p, char* name, char* surname, int yob) {
	person* new = (person*)malloc(sizeof(person));
	if (new == NULL) {
		printf("Greška pri alociranju memorije!\n");
		exit(1);
	}
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->yob = yob;

	new->next = p->next;
	p->next = new;
}

void PrintList(person* head) {
	if (head==NULL || head->next==NULL) {
		printf("Lista je prazna.\n\n");
	}
	else {
		person* p = head->next;
		printf("\n%-10s %-10s %-10s\n", "Ime", "Prezime", "Godina rodenja");
		while (p != NULL) {
			printf("%-10s %-10s %10d\n", p->name, p->surname, p->yob);
			p = p->next;
		}
		printf("\n");
	}
}

void InsertLast(person* p, char* name, char* surname, int yob) {
	person* new = (person*)malloc(sizeof(person));
	if (new == NULL) {
		printf("Greška pri alociranju memorije!\n");
		exit(1);
	}
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->yob = yob;
	while (p->next != NULL) {
		p = p->next;
	}
	new->next = p->next;
	p->next = new;
}

void Find(person* p, char* surname) {
	int found = 0;
	while (p != NULL) {
		if (strcmp(p->surname, surname) == 0) {
			printf("Element %s je pronađen na adresi %p\n\n", p->surname, p);
			found = 1;
		}
		p = p->next;
	}
	if (!found)
		printf("Element ne postoji u listi.\n\n");
}

void Delete(person* p, char* surname) {
	person* prev = p;
	p = p->next;
	while (p != NULL) {
		if (strcmp(p->surname, surname) != 0) {
			prev = p;
			p = p->next;
		}
		else
			break;
	}
	if (p == NULL) {
		printf("Element ne postoji u listi.\n\n");
		return;
	}
	prev->next = p->next;
	free(p);
}

void FreeList(person* head) {
	person* p = head->next;
	while (p != NULL) {
		person* temp = p->next;
		free(p);
		p = temp;
	}
	head->next = NULL;
}