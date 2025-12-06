#define _CRT_SECURE_NO_WARNINGS

#include "racun.h"
#include <stdio.h>

int main() {

	receipts rhead = { .year = 0,.month = 0,.day = 0,.name="",.rnext = NULL};

	Menu(&rhead);

	return 0;
}