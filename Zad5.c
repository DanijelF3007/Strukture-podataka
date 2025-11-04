#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct postfix* Position;
typedef struct postfix {
	double number;
	Position next;
}postfix;

int Push(Position head, double num);
int Pop(Position head, Position first, Position second,char Op);
int isOp(char Op);

int main() {

	postfix head;
	FILE* izraz;
	char buffer[100];
	int i = 0;
	int c;
	head.number = 0;
	head.next = NULL;

	izraz = fopen("izraz.txt", "r");
	if (izraz == NULL) {
		printf("Datoteka nije ispravno otvorena.\n");
		return 1;
	}
	while ((c=fgetc(izraz))!=EOF) {
		buffer[i] = c;
		i++;
	}
	buffer[i]='\0';
	fclose(izraz);
	i = 0;

	while (buffer[i] != '\0') {
		if (isdigit(buffer[i])) {
			Push(&head, buffer[i] - '0');
		}
		else if (isOp(buffer[i])) {
			if (head.next == NULL || head.next->next == NULL){
				printf("Nedovoljno operanada!\n");
			return 1;
			}
			else {
				Pop(&head, head.next, head.next->next, buffer[i]);
			}
		}
		else {
			printf("Izraz nije valjan.\n");
			break;
		}
		i++;
	}
	printf("Rezultat je %.2lf", head.next->number);

	return 0;
}

int isOp(char Op) {
	return Op == '+' || Op == '-' || Op == '*' || Op == '/';
}

int Push(Position head, double num) {

	Position q = head;
	Position new = (Position)malloc(sizeof(postfix));
	if (new == NULL)
		printf("Memorija nije ispravno alocirana.\n");

	new->number = num;
	new->next = q->next;
	q->next = new;

	return 0;
}

int Pop(Position head, Position first, Position second, char Op) {
	
	Position q = head;
	double result;

	switch (Op) {
	case '+':
		result = first->number + second->number;
		break;
	case '-':
		result = first->number - second->number;
		break;
	case '*':
		result = first->number * second->number;
		break;
	case '/':
		result = first->number / second->number;
		break;
	default:
		printf("Greska!\n");
		break;
	}

	q->next = second->next;
	first->next = NULL;
	second->next = NULL;
	free(first);
	free(second);
	
	Push(head, result);

	return 0;
}