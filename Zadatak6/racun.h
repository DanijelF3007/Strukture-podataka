#ifndef RACUN_H
#define RACUN_H

typedef struct receipts* rposition;
typedef struct article* aposition;

typedef struct receipts {
	int year;
	int month;
	int day;
	char name[15];
	rposition rnext;
	aposition anext;
}receipts;

typedef struct article {
	char name[15];
	int count;
	float price;
	aposition next;
}article;

int AddSortedReceipt(rposition rhead, char txt[]);
int CompareDates(rposition first, rposition second);
int CompareDates1(rposition first, int year, int month, int day);
int FreeReceipts(rposition rhead);
int ReadArticles(rposition rhead);
int AddSortedArticle(rposition rhead, char name[], int count, float price);
int FreeArticles(rposition rhead);
int PrintReceipts(rposition rhead);
int SpentOnArticle(rposition rhead, int year1, int year2, int month1, int month2, int day1, int day2, char name[]);
int Menu(rposition rhead);
int ReadFile(rposition rhead);
int FindReceipt(rposition rhead, int year, int month, int day);
int AddNewReceipt(rposition rhead);
int SameReceipt(rposition rhead, char name[]);
int DeleteReceipt(rposition rhead);

#endif