#define _CRT_SECURE_NO_WARNINGS
#include "racun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ReadFile(rposition rhead) {
	FILE* file;
	file = fopen("racuni.txt", "r");
	if (file == NULL) {
		printf("Neuspjesno otvaranje datoteke!");
		return 1;
	}
	char c = '\0';
	char txt[15];

	while (fgets(txt, sizeof(txt), file) != NULL) {
		txt[strcspn(txt, "\r\n")] = '\0';
		if (txt[0] == '\0') {
			continue;
		}
		AddSortedReceipt(rhead, txt);
	}
	fclose(file);

	return 0;
}

int Menu(rposition rhead) {
	int year1, month1, day1;
	int year2, month2, day2;
	char name[15];
	int op;

	ReadFile(rhead);

	while (1) {
		printf("\n1 - Za kolicinu i utroseni novac na specificni artikal u odredenom vremenskom razdoblju");
		printf("\n2 - Za ispis svih racuna");
		printf("\n3 - Za ispis odredenog racuna");
		printf("\n4 - Za dodavanje novog racuna");
		printf("\n5 - Za brisanje odredenog racuna");
		printf("\n6 - Za izlaz iz programa\n");
		printf("Unesi odabir: ");
		scanf("%d", &op);
		switch (op) {
		case 1:
			printf("\nUnesi pocetni datum(YYYY-MM-DD):");
			scanf("%d-%d-%d", &year1, &month1, &day1);
			printf("\nUnesi zavrsni datum(YYYY-MM-DD):");
			scanf("%d-%d-%d", &year2, &month2, &day2);
			printf("\nUnesi naziv trazenog artikla: ");
			scanf("%s", name);
			SpentOnArticle(rhead, year1, year2, month1, month2, day1, day2, name);
			break;
		case 2:
			PrintReceipts(rhead);
			break;
		case 3:
			printf("\nUnesi datum za trazeni racun(YYYY-MM-DD):");
			scanf("%d-%d-%d", &year1, &month1, &day1);
			FindReceipt(rhead, year1, month1, day1);
			break;
		case 4:
			AddNewReceipt(rhead);
			break;
		case 5:
			DeleteReceipt(rhead);
			break;
		case 6:
			FreeReceipts(rhead);
			exit(0);
			break;
		default:
			return 0;
		}
	}


	return 0;
}

int DeleteReceipt(rposition rhead) {

	FILE* fileIn;
	FILE* fileOut;
	char name[20];
	char buffer[30];
	rposition prev = rhead;
	rposition current = rhead->rnext;

	printf("Unesi ime racuna za brisanje (npr. ime.txt): ");
	scanf("%s", name);
	if (SameReceipt(rhead, name) == 0) {
		printf("Trazeni racun ne postoji.\n");
		return 0;
	}

	remove(name);

	fileIn = fopen("racuni.txt", "r");
	fileOut = fopen("temp.txt", "w");
	if (fileIn == NULL || fileOut == NULL) {
		printf("Neuspjesno otvaranje datoteke!");
		return 1;
	}

	while (!feof(fileIn)) {
		fgets(buffer, sizeof(buffer), fileIn);
		buffer[strcspn(buffer, "\n")] = '\0';
		if (strcmp(buffer, name) == 0) {
			continue;
		}
		fprintf(fileOut, "%s\n", buffer);
	}

	fclose(fileIn);
	fclose(fileOut);

	remove("racuni.txt");
	rename("temp.txt", "racuni.txt");


	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			prev->rnext = current->rnext;
			FreeArticles(current);
			free(current);
			break;
		}
		prev = current;
		current = current->rnext;
	}

	PrintReceipts(rhead);

	return 0;
}

int SameReceipt(rposition rhead, char name[]) {

	rposition p = rhead->rnext;

	while (p != NULL) {
		if (strcmp(p->name, name) == 0) {
			return 1;
		}
		p = p->rnext;
	}

	return 0;
}

int AddNewReceipt(rposition rhead) {
	FILE* file;
	char name[20], name1[20];
	int year, month, day, i, count;
	float price;
	rposition p = rhead->rnext;

	printf("\nUnesi naziv novog racuna (npr. ime.txt): ");
	while (1) {
		scanf("%s", name);
		if (SameReceipt(rhead, name) == 1) {
			printf("Racun s tim imenom vec postoji, unesi drugi naziv: ");
		}
		else
			break;
	}
	file = fopen(name, "a");
	if (file == NULL) {
		printf("\nOtvaranje datoteke neuspjesno!\n");
		return 1;
	}
	printf("Unesi datum izdavanja racuna (YYYY-MM-DD): ");
	scanf("%d-%d-%d", &year, &month, &day);
	fprintf(file, "%d-%d-%d", year, month, day);
	printf("Unesi broj artikala: ");
	scanf("%d", &i);
	printf("Unosi artikle (Naziv kolicina cijena): ");

	while (i != 0) {
		scanf("%s %d %f", name1, &count, &price);
		fprintf(file, "\n%s %d %.2f", name1, count, price);
		i--;
	}
	fclose(file);
	file = fopen("racuni.txt", "a");
	if (file == NULL) {
		printf("\nOtvaranje datoteke neuspjesno!\n");
		return 1;
	}
	fprintf(file, "%s\n", name);
	fclose(file);
	AddSortedReceipt(rhead, name);

	return 0;
}

int FindReceipt(rposition rhead, int year, int month, int day) {

	rposition p = rhead->rnext;
	aposition a;
	float sum = 0;

	while (p != NULL) {
		if (p->year == year && p->month == month && p->day == day) {
			a = p->anext;
			printf("%d-%d-%d\n", p->year, p->month, p->day);
			printf("%-10s %-10s %-10s\n", "Naziv", "Kolicina", "Cijena");
			while (a != NULL) {
				printf("%-10s %8d %8.2f\n", a->name, a->count, a->price);
				sum += (float)a->count * a->price;
				a = a->next;
			}
			printf("----------------------------\n");
			printf("%-10s %17.2f\n", "Ukupno:", sum);
			return 0;
		}
		p = p->rnext;
	}
	printf("\nTrazeni racun ne postoji.\n");

	return 0;
}

int AddSortedReceipt(rposition rhead, char txt[]) {
	FILE* file;
	rposition p = rhead;
	rposition new;
	new = (rposition)malloc(sizeof(receipts));
	if (new == NULL) {
		printf("Neuspjesna alokacija!");
		return 1;
	}
	new->anext = NULL;
	strcpy(new->name, txt);

	file = fopen(new->name, "r");
	if (file == NULL) {
		printf("Neuspjesno otvaranje datoteke!");
		return 1;
	}
	fscanf(file, "%d-%d-%d\n", &new->year, &new->month, &new->day);

	while (p->rnext != NULL && CompareDates(p->rnext, new) < 0) {
		p = p->rnext;
	}
	new->rnext = p->rnext;
	p->rnext = new;
	fclose(file);
	ReadArticles(new);

	return 0;
}

int CompareDates(rposition first, rposition second) {
	if (first->year != second->year) {
		return first->year - second->year;
	}
	if (first->month != second->month) {
		return first->month - second->month;
	}
	return first->day - second->day;
}

int FreeReceipts(rposition rhead) {
	rposition p = rhead->rnext;
	rposition temp;

	while (p != NULL) {
		temp = p;
		p = p->rnext;
		temp->rnext = NULL;
		FreeArticles(temp);
		free(temp);
	}

	return 0;
}

int ReadArticles(rposition receipt) {
	FILE* file;
	char buffer[20];
	int count;
	float price;
	file = fopen(receipt->name, "r");
	if (file == NULL) {
		printf("Neuspjesno otvaranje datoteke!");
	}
	fgets(buffer, sizeof(buffer), file);
	while (!feof(file)) {
		fscanf(file, "%s %d %f", buffer, &count, &price);
		AddSortedArticle(receipt, buffer, count, price);
	}

	fclose(file);
	return 0;
}

int AddSortedArticle(rposition rhead, char name[], int count, float price) {
	aposition p;
	aposition new;
	new = (aposition)malloc(sizeof(article));

	strcpy(new->name, name);
	new->count = count;
	new->price = price;
	if (rhead->anext == NULL || strcmp(name, rhead->anext->name) < 0) {
		new->next = rhead->anext;
		rhead->anext = new;
		return 0;
	}
	p = rhead->anext;
	while (p->next != NULL && strcmp(name, p->next->name) > 0) {
		p = p->next;
	}
	new->next = p->next;
	p->next = new;

	return 0;
}

int FreeArticles(rposition rhead) {
	aposition p = rhead->anext;
	aposition temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		temp->next = NULL;
		free(temp);
	}
	rhead->anext = NULL;

	return 0;
}

int PrintReceipts(rposition rhead) {

	rposition p = rhead->rnext;
	aposition a = p->anext;
	float sum;
	printf("\n\nIspis racuna:\n\n");
	while (p != NULL) {
		sum = 0;
		printf("%s\n\n", p->name);
		printf("%d-%d-%d\n", p->year, p->month, p->day);
		printf("%-10s %-10s %-10s\n", "Naziv", "Kolicina", "Cijena");
		a = p->anext;
		while (a != NULL) {
			printf("%-10s %8d %8.2f\n", a->name, a->count, a->price);
			sum += (float)a->count * a->price;
			a = a->next;
		}
		printf("----------------------------\n");
		printf("%-10s %17.2f\n", "Ukupno:", sum);
		printf("\n");
		p = p->rnext;
	}

	return 0;
}

int SpentOnArticle(rposition rhead, int year1, int year2, int month1, int month2, int day1, int day2, char name[]) {

	rposition p = rhead->rnext;
	aposition a = p->anext;
	int sum = 0;
	float price = 0;

	while (p != NULL) {
		if (CompareDates1(p, year1, month1, day1) > 0 && CompareDates1(p, year2, month2, day2) < 0) {
			a = p->anext;
			while (a != NULL) {
				if (strcmp(a->name, name) == 0) {
					sum += a->count;
					price = a->price;
				}
				a = a->next;
			}
		}
		p = p->rnext;
	}
	printf("\nNa %s je potroseno %.2f u razdoblju od %d-%d-%d do %d-%d-%d.\n\n", name, sum * price, year1, month1, day1, year2, month2, day2);

	return 0;
}

int CompareDates1(rposition first, int year, int month, int day) {
	if (first->year != year) {
		return first->year - year;
	}
	if (first->month != month) {
		return first->month - month;
	}
	return first->day - day;
}
