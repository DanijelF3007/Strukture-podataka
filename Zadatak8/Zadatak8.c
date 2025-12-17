#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct queue* qPos;
typedef struct tree* treePos;
typedef struct tree {
	int value;
	treePos left;
	treePos right;
}tree;

typedef struct queue {
	qPos next;
	treePos el;
}queue;

treePos insert(treePos root, int value);
treePos find(treePos root, int value);
treePos delete(treePos root, int value);
treePos findMin(treePos root);
treePos freeTree(treePos root);
treePos inorder(treePos root, int depth);
treePos preorder(treePos root, int depth);
treePos postorder(treePos root, int depth);
treePos levelorder(treePos root);
treePos Menu(treePos root);
int Printing(treePos root);
int enqueue(qPos head, treePos root);
treePos dequeue(qPos head);

int main() {

	treePos root = NULL;
	
	root=Menu(root);

	return 0;
}

treePos Menu(treePos root) {

	treePos temp;
	int op, value;

	while (1) {
		printf("\n1 - Unos novog elementa\n");
		printf("2 - Pronalazenje elementa\n");
		printf("3 - Brisanje elementa\n");
		printf("4 - Ispis elemenata\n");
		printf("5 - Izlaz iz programa\n\n");
		printf("Unesi odabir: ");
		scanf("%d", &op);

		switch (op) {
		case 1:
			printf("Unesi vrijednost za unos: ");
			scanf("%d", &value);
			root=insert(root, value);
			break;
		case 2:
			printf("Unesi vrijednost za pretragu: ");
			scanf("%d", &value);
			temp = find(root, value);
			if (temp == NULL) {
				printf("ELement nije pronađen.\n");
			}
			else {
				printf("Element je pronaden na adresi %p", temp);
			}
			break;
		case 3:
			printf("Unesi vrijednost za brisanje: ");
			scanf("%d", &value);
			root=delete(root, value);
			break;
		case 4:
			Printing(root);
			break;
		case 5:
			freeTree(root);
			exit(0);
			break;
		default:
			freeTree(root);
			exit(1);
			break;
		}
	}

	return root;
}

int Printing(treePos root) {

	int op;

	printf("Odaberi nacin ispisa:\n");
	printf("1 - inorder\n");
	printf("2 - preorder\n");
	printf("3 - postorder\n");
	printf("4 - level order\n\n");
	printf("Unesi odabir: ");
	scanf("%d", &op);

	switch (op) {
	case 1:
		inorder(root,1);
		break;
	case 2:
		preorder(root,1);
		break;
	case 3:
		postorder(root,1);
		break;
	case 4:
		levelorder(root);
		break;
	default:
		printf("Greska!\n");
		break;
	}

	return 0;
}

treePos inorder(treePos root, int depth) {
	
	treePos S = root;
	int i;

	if (S == NULL) {
		return NULL;
	}

	inorder(S->left, depth + 1);
	for (i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("%d\n", S->value);
	inorder(S->right, depth + 1);



	return NULL;
}

treePos preorder(treePos root, int depth) {
	
	treePos S = root;
	int i;

	if (S == NULL) {
		return NULL;
	}

	for (i = 0; i < depth; i++) {
		printf("  ");
	}

	printf("%d\n", S->value);

	preorder(S->left, depth + 1);
	preorder(S->right, depth + 1);

	return NULL;
}

treePos postorder(treePos root, int depth) {
	
	treePos S = root;
	int i;

	if (S == NULL) {
		return NULL;
	}

	postorder(S->left, depth + 1);
	postorder(S->right, depth + 1);

	for (i = 0; i < depth; i++) {
		printf("  ");
	}

	printf("%d\n", S->value);

	return NULL;
}

treePos levelorder(treePos root) {
	
	treePos S = root;
	treePos temp;
	queue head = { .next = NULL,.el = NULL };

	if (S == NULL) {
		return NULL;
	}

	enqueue(&head,root);

	while (head.next != NULL) {
		temp= dequeue(&head);
		printf("%d ", temp->value);
		if (temp->left != NULL) {
		enqueue(&head, temp->left);
		}
		if (temp->right != NULL) {
		enqueue(&head, temp->right);
		}
	}

	return NULL;
}

treePos dequeue(qPos head) {

	if (head->next == NULL) {
		return NULL;
	}

	qPos q = head->next;
	qPos prev = head;
	treePos el;

	while (q->next!=NULL) {
		prev = q;
		q = q->next;
	}
	
	el = q->el;

	prev->next = q->next;
	free(q);

	return el;
}

int enqueue(qPos head, treePos root) {

	qPos q=head;
	qPos new;
	new = (qPos)malloc(sizeof(queue));
	if (new == NULL) {
		printf("Greska u alokaciji!");
		return 1;
	}

	new->next = q->next;
	q->next = new;
	new->el = root;

	return 0;
}

treePos insert(treePos root, int value) {

	treePos S = root;

	if (S == NULL) {
		S = (treePos)malloc(sizeof(tree));
		if (S == NULL) {
			printf("Greska u alociranju!\n");
			return NULL;
		}
		S->value = value;
		S->left = NULL;
		S->right = NULL;
		return S;
	}

	if (value < S->value) {
		S->left = insert(S->left, value);
	}
	else if (value > S->value) {
		S->right = insert(S->right, value);
	}

	return S;

}

treePos find(treePos root, int value) {

	treePos S = root;

	if (S == NULL) {
		return NULL;
	}

	if (value < S->value) {
		return find(S->left,value);
	}
	else if (value > S->value) {
		return find(S->right, value);
	}

	return S;
}

treePos delete(treePos root, int value) {

	treePos S = root;
	treePos temp;

	if (S == NULL) {
		printf("Cvor s elementom %d ne postoji.\n",value);
		return S;
	}
	else if (value < S->value) {
		S->left = delete(S->left, value);
	}
	else if (value > S->value) {
		S->right = delete(S->right, value);
	}
	else if(S->left != NULL && S->right != NULL) {
		temp = findMin(S->right);
		S->value = temp->value;
		S->right = delete(S->right, S->value);
	}
	else {
		temp = S;

		if (S->left == NULL) {
			S = S->right;
			free(temp);
		}
		else {
			S = S->left;
			free(temp);
		}
	}

	return S;
}

treePos findMin(treePos root) {

	treePos S = root;

	if (S == NULL) {
		return NULL;
	}
	else if (S->left == NULL) {
		return S;
	}
	
	return findMin(S->left);
}

treePos freeTree(treePos root) {

	treePos S = root;

	if (S != NULL) {
		freeTree(S->left);
		freeTree(S->right);
		free(S);
	}

	return NULL;
}