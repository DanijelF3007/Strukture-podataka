#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct poly* position;
typedef struct poly {
	int coefficient;
	int exponent;
	position next;
}poly;

int Sortedinput(position head, int coefficient, int exponent);
int FreeList(position head);
int AddPoly(position head1, position head2);
int MultiplyPoly(position head1, position head2);

int main() {

	poly head1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	poly head2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	char c;
	int coefficient, exponent;
	FILE* file;
	file = fopen("poly1.txt", "r");

	if (file == NULL) {
		printf("Datoteka nije ispravno otvorena.");
		return 1;
	}
	c = '\0';
	while (c != '\n') {
		fscanf(file, "%d %d", &coefficient, &exponent);
		Sortedinput(&head1, coefficient, exponent);
		c = fgetc(file);
	}
	while (c != EOF) {
		fscanf(file, "%d %d", &coefficient, &exponent);
		Sortedinput(&head2, coefficient, exponent);
		c=fgetc(file);
	}

	AddPoly(&head1, &head2);
	MultiplyPoly(&head1, &head2);

	fclose(file);
	FreeList(&head1);
	FreeList(&head2);
		

	return 0;
}

int FreeList(position head) {

	position p = head->next;
	position temp;
	
	while (p != NULL) {
		temp = p;
		p = p->next;
		temp->next = NULL;
		free(temp);
	}

	return 0;
}

int Sortedinput(position head, int coefficient, int exponent) {
	
	position p = head;
	position new;
	position temp;

	new = (position)malloc(sizeof(poly));
	if (new == NULL) {
		printf("Greska u alociranju memorije.");
		return 1;
	}
	new->coefficient = coefficient;
	new->exponent = exponent;

	while (p->next != NULL && exponent < p->next->exponent) {
		p = p->next;
	}
	if (p->next!=NULL && exponent == p->next->exponent) {
		p->next->coefficient += coefficient;
		if (p->next != NULL && p->next->coefficient == 0) {
			temp = p->next;
			p->next = temp->next;
			temp->next = NULL;
			free(temp);
			return 0;
		}
		free(new);
		return 0;
	}
	
	new->next = p->next;
	p->next = new;

	return 0;
}

int AddPoly(position head1, position head2) {
	position p1 = head1->next;
	position p2 = head2->next;
	poly headR = { .coefficient = 0,.exponent = 0,.next = NULL };

	while (p1 != NULL) {
		Sortedinput(&headR, p1->coefficient, p1->exponent);
		p1 = p1->next;
	}
	while (p2 != NULL) {
		Sortedinput(&headR, p2->coefficient, p2->exponent);
		p2 = p2->next;
	}
	position pR = headR.next;

	while (pR != NULL) {
		if (pR->next == NULL) {
			printf("(%dx^%d)", pR->coefficient, pR->exponent);
			pR = pR->next;
		}
		else {
			printf("(%dx^%d)+", pR->coefficient, pR->exponent);
			pR = pR->next;
		}
	}
	printf("\n");

	FreeList(&headR);

	return 0;
}

int MultiplyPoly(position head1, position head2) {
	position p1 = head1->next;
	position p2 = head2->next;
	poly headR = { .coefficient = 0,.exponent = 0,.next = NULL };
	int co, exp;

	while (p1 != NULL) {
		p2 = head2->next;
		while (p2 != NULL) {
			co = p1->coefficient * p2->coefficient;
			exp = p1->exponent + p2->exponent;
			Sortedinput(&headR, co, exp);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	position pR = headR.next;

	while (pR != NULL) {
		if (pR->next == NULL) {
			printf("(%dx^%d)", pR->coefficient, pR->exponent);
			pR = pR->next;
		}
		else {
			printf("(%dx^%d)+", pR->coefficient, pR->exponent);
			pR = pR->next;
		}
	}
	printf("\n");

	FreeList(&headR);

	return 0;
}