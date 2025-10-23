#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* position;
typedef struct Person {
	char name[10];
	char surname[10];
	int yob;
	position next;
}person;

void InsertFirst(position p, char* name, char* surname, int yob);
void PrintList(position head);
void InsertLast(position p, char* name, char* surname, int yob);
void Find(position p, char* surname);
void Delete(position p, char* surname);
void FreeList(position head);
void InsertBehind(position p, char* surname1, char* name, char* surname, int yob);
void InsertInFront(position p, char* surname1, char* name, char* surname, int yob);
void WriteList(position p);
void ReadList();
void SortList(position p);
void Insertion(position p);

int main() {

	person head;
	position p = &head;
	p->next = NULL;
	int op;
	char surname[10];

	while (1) {
		printf("Odaberi opciju za rad nad listom:\n1 - Ubaci element\n");
		printf("2 - Ispis liste\n3 - Pronadi element u listi\n4 - Izbrisi element\n5 - Upis u datoteku\n");
		printf("6 - Citanje iz datoteke\n7 - Sortiranje liste\n8 - Izadi iz programa\n");
		scanf("%d", &op);
		if (op < 1 || op>8) {
			printf("Nije odabrana valjana opcija. Ponovi.\n");
			break;
		}
		switch (op) {
		case 1:
			Insertion(p);
			break;
		case 2:
			PrintList(p);
			break;
		case 3:
			printf("Unesi prezime elementa za trazenje: ");
			scanf("%s", surname);
			Find(p, surname);
			break;
		case 4:
			printf("Unesi prezime elementa za brisanje: ");
			scanf("%s", surname);
			Delete(p, surname);
			break;
		case 5:
			WriteList(p);
			printf("\nUpis u datoteku obavljen\n\n");
			break;
		case 6:
			printf("Ispis liste iz datoteke:\n");
			ReadList();
			break;
		case 7:
			printf("Sortiranje liste...\n\n");
			SortList(p);
			break;
		case 8:
			printf("Izlaz iz programa...\n");
			exit(1);
		default:
			printf("Greska! Ponovi.\n");
			break;
		}
	}
	FreeList(p);

	return 0;
}

void Insertion(position p) {
	int op;
	char name[10];
	char surname[10];
	char surname1[10];
	int yob;

	printf("\n1 - Unos na pocetak\n2 - Unos na kraj\n3 - Unos ispred\n4 - Unos iza\n");
	scanf("%d", &op);

	if (op < 1 || op>4) {
		printf("Nije odabrana valjana opcija. Ponovi.\n");
		return;
	}
	else {
		switch (op) {
		case 1:
			printf("Unesi element u formatu (ime prezime god): ");
			scanf("%s %s %d", name, surname, &yob);
			InsertFirst(p, name, surname, yob);
			break;
		case 2:
			printf("Unesi element u formatu (ime prezime god): ");
			scanf("%s %s %d", name, surname, &yob);
			InsertLast(p, name, surname, yob);
			break;
		case 3:
			printf("Unesi prezime iza kojeg se unosi i odgovarajuci element: ");
			scanf("%s %s %s %d", surname1, name, surname, &yob);
			InsertBehind(p, surname1, name, surname, yob);
			break;
		case 4:
			printf("Unesi prezime ispred kojeg se unosi i odgovarajuci element: ");
			scanf("%s %s %s %d", surname1, name, surname, &yob);
			InsertInFront(p, surname1, name, surname, yob);
			break;
		default:
			printf("Greska! Ponovi.\n");
			break;
		}
	}
}

void InsertFirst(position p, char* name, char* surname, int yob) {
	position new = (position)malloc(sizeof(person));
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

void PrintList(position head) {
	if (head == NULL || head->next == NULL) {
		printf("Lista je prazna.\n\n");
	}
	else {
		position p = head->next;
		printf("\n%-10s %-10s %-10s\n", "Ime", "Prezime", "Godina rodenja");
		while (p != NULL) {
			printf("%-10s %-10s %10d\n", p->name, p->surname, p->yob);
			p = p->next;
		}
		printf("\n");
	}
}

void InsertLast(position p, char* name, char* surname, int yob) {
	position new = (position)malloc(sizeof(person));
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

void Find(position p, char* surname) {
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

void Delete(position p, char* surname) {
	position prev = p;
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

void FreeList(position head) {
	position p = head->next;
	while (p != NULL) {
		position temp = p->next;
		free(p);
		p = temp;
	}
	head->next = NULL;
}

void InsertBehind(position p, char* surname1, char* name, char* surname, int yob) {
	int found = 0;
	position new = (position)malloc(sizeof(person));
	if (new == NULL)
		printf("Greska pri alociranju!");
	while (p != NULL) {
		if (strcmp(p->surname, surname1) == 0) {
			new->next = p->next;
			p->next = new;
			found = 1;
			strcpy(new->name, name);
			strcpy(new->surname, surname);
			new->yob = yob;
		}
		p = p->next;
	}
	if (!found)
		printf("Element ne postoji u listi.\n\n");
}

void InsertInFront(position p, char* surname1, char* name, char* surname, int yob) {
	int found = 0;
	position prev = p;
	p = p->next;
	position new = (position)malloc(sizeof(person));
	if (new == NULL)
		printf("Greska pri alociranju!");
	while (p != NULL) {
		if (strcmp(p->surname, surname1) == 0) {
			new->next = prev->next;
			prev->next = new;
			found = 1;
			strcpy(new->name, name);
			strcpy(new->surname, surname);
			new->yob = yob;
		}
		prev = p;
		p = p->next;
	}
	if (!found)
		printf("Element ne postoji u listi.\n\n");
}

void WriteList(position p) {
	FILE* file;
	file = fopen("lista.txt", "w");

	if (p == NULL || p->next == NULL) {
		fprintf(file,"Lista je prazna.\n\n");
	}
	else {
		p = p->next;
		fprintf(file,"\n%-10s %-10s %-10s\n", "Ime", "Prezime", "Godina rodenja");
		while (p != NULL) {
			fprintf(file,"%-10s %-10s %10d\n", p->name, p->surname, p->yob);
			p = p->next;
		}
	}
	fclose(file);
}

void ReadList() {
	int c;
	FILE* file;
	file = fopen("lista.txt","r");
	if (file != NULL) {
		while ((c = getc(file)) != EOF) {
			putchar(c);
		}
	}
	else
		printf("Datoteka ne postoji!\n");
	printf("\n");
	fclose(file);
}

void SortList(position p) {
	int counter = 0;
	int i, j;
	position temp1, temp2,prev;
	position first = p;
	while (p->next != NULL) {
		p = p->next;
		counter++;
	}
	for (i = 0; i < counter - 1; i++) {
		prev = first;
		p = first->next;
		for (j = 0; j < counter - i - 1; j++) {
			if (strcmp(p->surname,p->next->surname) > 0) {
				temp1 = p->next->next;
				temp2 = p->next;
				prev->next = temp2;
				temp2->next = p;
				p->next = temp1;
				p = temp2;
			}
			prev = prev->next;
			p = p->next;
		}
	}
}