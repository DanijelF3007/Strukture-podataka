#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct stack* stackPosition;
typedef struct directory* dirPosition;

typedef struct stack {
	stackPosition next;
	dirPosition dirLevel;
}stack;

typedef struct directory {
	char name[MAX];
	dirPosition next;
	dirPosition firstChild;
}directory;

int Menu();
int AddChild(dirPosition parent);
dirPosition ChangeDirectory(dirPosition parent, stackPosition current);
int Push(dirPosition dir, stackPosition shead);
int PrintStack(stackPosition shead);
dirPosition GoBack(stackPosition shead);
int Pop(stackPosition shead);
int FreeStack(stackPosition shead);
dirPosition FreeTree(dirPosition root);
int PrintTree(dirPosition root, int depth);
int PrintStack1(stackPosition shead);

int main() {

	directory root = { .name = "C:",.next = NULL,.firstChild = NULL };
	stack shead = {.next=NULL,.dirLevel=NULL};
	dirPosition temp=&root;

	int op;

	while (1) {
		printf("1 - md - Napravi novi direktorij\n");
		printf("2 - cd dir - Udi u direktorij\n");
		printf("3 - cd.. Vrati se u prethodni direktorij\n");
		printf("4 - dir - Ispisi sve pod-direktorije\n");
		printf("5 - Izadi iz programa\n\n");
		PrintStack(&shead);
		scanf("%d",&op);
		
		switch (op) {
		case 1:
			AddChild(temp);
			break;
		case 2:
			temp = ChangeDirectory(temp,&shead);
			break;
		case 3:
			temp = GoBack(&shead);
			if (temp == NULL)
				temp = &root;
			break;
		case 4:
			PrintTree(temp,1);
			break; 
		case 5:
			FreeStack(&shead);
			FreeTree(root.firstChild);
			exit(0);
			break;
		default:
			printf("Greska! Default izlaz...\n");
			FreeStack(&shead);
			FreeTree(root.firstChild);
			exit(1);
			break;
		}
	}

	return 0;
}

int PrintTree(dirPosition root, int depth) {
	
	int i;

	if (root == NULL) {
		return 1;
	}

	for (int i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("%s\n",root->name);

	PrintTree(root->firstChild, depth + 1);
	PrintTree(root->next, depth);

	return 0;
}

dirPosition FreeTree(dirPosition root) {

	if (root != NULL) {
		FreeTree(root->firstChild);
		FreeTree(root->next);
		free(root);
	}

	return NULL;
}

int FreeStack(stackPosition shead) {

	stackPosition p = shead->next;
	stackPosition temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		temp->next = NULL;
		free(temp);
	}

	return 0;
}

int Pop(stackPosition shead) {

	stackPosition p = shead;
	stackPosition temp=shead->next;

	if (temp == NULL) {
		printf("Stog je prazan\n");
		return 1;
	}

	p->next = temp->next;
	temp->next = NULL;
	free(temp);

	return 0;
}

dirPosition GoBack(stackPosition shead) {

	stackPosition p;

	Pop(shead);

	p = shead->next;

	if (p == NULL) {
		return NULL;
	}

	return p->dirLevel;
}

int PrintStack(stackPosition shead) {

	stackPosition p = shead->next;

	printf("C:");

	PrintStack1(p);

	printf(" ");

	return 0;
}

int PrintStack1(stackPosition shead) {

	if (shead == NULL)
		return 0;

	PrintStack1(shead->next);
	printf("\\%s", shead->dirLevel->name);

	return 0;
}

int Push(dirPosition dir, stackPosition shead) {

	stackPosition p = shead;
	stackPosition new;
	new = (stackPosition)malloc(sizeof(stack));
	if (new == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}

	new->dirLevel = dir;
	new->next = p->next;
	p->next = new;

	return 0;
}

int AddChild(dirPosition parent) {

	char name[MAX];
	dirPosition p = parent;
	dirPosition child;
	child = (dirPosition)malloc(sizeof(directory));
	if (child == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}

	printf("Unesi naziv novog direktorija (max. 20 znakova): ");
	scanf("%s", name);

	strcpy(child->name, name);

	child->next = p->firstChild;
	p->firstChild = child;
	child->firstChild = NULL;


	return 0;
}

dirPosition ChangeDirectory(dirPosition parent, stackPosition current) {

	dirPosition p = parent->firstChild;
	char name[MAX];

	printf("Unesi naziv direktorija u koji se ulazi: ");
	scanf("%s",name);

	while (p!=NULL && strcmp(p->name, name) != 0) {
		p = p->next;
	}

	if (p == NULL) {
		printf("Direktorij ne postoji!\n");
		return parent;
	}

	Push(p, current);

	return p;
}

int Menu() {

	return 0;
}