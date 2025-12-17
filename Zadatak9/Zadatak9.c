#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree* treePos;
typedef struct tree {
	int value;
	treePos left;
	treePos right;
}tree;

treePos insert(treePos root, int value);
treePos freeTree(treePos root);
treePos inorder(treePos root, int depth);
int replace(treePos root);
int inorderfile(treePos root, FILE* f);

int main() {

	treePos root = NULL;
	int n,i,x;
	FILE* file;
	file = fopen("inorder.txt", "w");
	if (file == NULL) {
		printf("Greska u otvaranju datoteke!");
		return 1;
	}
	srand(time(NULL));
	
	printf("Unesi broj nasumicnih elemenata za dodavanje u stablo: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		x = rand() % 81 + 10;
		root = insert(root, x);
	}

	inorder(root, 1);
	fprintf(file, "Prije replace: ");
	inorderfile(root, file);
	fprintf(file, "\n");

	replace(root);

	inorder(root, 1);
	fprintf(file, "Poslije replace: ");
	inorderfile(root, file);
	fprintf(file, "\n");

	fclose(file);
	freeTree(root);

	return 0;
}

int inorderfile(treePos root, FILE* f) {

	treePos S = root;

	if (S == NULL) {
		return 0;
	}

	inorderfile(S->left, f);
	fprintf(f, "%d ", S->value);
	inorderfile(S->right, f);

	return 0;
}

int replace(treePos root) {

	int leftsum, rightsum;
	int oldvalue;
	if (root == NULL) {
		return 0;
	}

	oldvalue = root->value;

	leftsum = replace(root->left);
	rightsum = replace(root->right);

	root->value = leftsum + rightsum;

	return oldvalue + root->value;
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
		S->right = insert(S->right, value);
	}
	else if (value > S->value) {
		S->left = insert(S->left, value);
	}

	return S;

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