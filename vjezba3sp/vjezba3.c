#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR (-1)
#define OKAY 0
#define MAX_NAME 256


typedef struct _student* Position;
typedef struct _student {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int year;
	Position next;
}student;

int InputP(Position h);
int InputK(Position h);
int Print(Position h);
Position FindL(Position h, char* prez);
Position FindPrevious(Position h, char* prez);
int DeleteElement(Position h);
int Sort(Position h);
int InputBehind(Position h);
int InputForward(Position h);
int WriteFile(Position h);
int ReadFile(Position h);

int main() {

	int succ;
	student Head;
	Position tr;
	Head.next = NULL;

	ReadFile(&Head);

	succ = Print(Head.next);
	if (succ == ERR)
		printf("Print doesn't work.....");

	succ = Sort(&Head);
	if (succ != OKAY)
		printf("Sort doesn't work.....");

	succ = Print(Head.next);
	if (succ == ERR)
		printf("Print doesn't work.....");

	return 0;
}

int InputP(Position h) {

	Position p;
	p = (Position)malloc(sizeof(student));
	p->next = NULL;
	if (p == NULL)
		return ERR;

	printf("Enter name surname and year of birth \n");
	scanf("%s %s %d", p->name, p->surname, &p->year);

	p->next = h->next;
	h->next = p;

	return OKAY;
}
int InputK(Position h) {

	int succ;

	while (h->next != NULL)
		h = h->next;

	succ = InputP(h);
	if (succ == ERR)
		printf("Input doesn't work.....");

	return OKAY;
}
int Print(Position h) {

	printf("\nPrint liste:\n");

	while (h != NULL) {
		printf("%s %s %d\n", h->name, h->surname, h->year);
		h = h->next;
	}

	return OKAY;

}
Position FindL(Position h, char* prez) {

	while (h != NULL && strcmp(h->surname, prez) != 0)
		h = h->next;

	return h;
}
Position FindPrevious(Position h, char* prez) {

	Position Prev = h;
	h = h->next;

	while (h != NULL && strcmp(h->surname, prez) != 0) {
		Prev = h;
		h = h->next;
	}

	if (h == NULL) {
		printf("Element is not in list!!!");
		return NULL;
	}

	return Prev;
}
int DeleteElement(Position h) {

	char prez[MAX_NAME];
	Position Prev, pom = NULL;

	printf("Enter surname of element that you want delete ");
	scanf(" %s", prez);

	Prev = FindPrevious(h, prez);

	if (Prev != NULL) {
		pom = Prev->next;
		Prev->next = pom->next;
		free(pom);

	}

	return OKAY;
}
int Sort(Position h) {

	Position j, jprev, temp, temp1, zam;
	temp = h;
	temp1 = h;

	while (temp != NULL) {
		while (temp1 != NULL) {
			jprev = temp1;
			j = temp1->next;
			if (strcmp(jprev->surname[0], j->surname[0]) > 0)
			{
				zam = jprev;
				jprev = j;
				jprev->next = j->next;
				j = zam;
				j->next = jprev;
			}
			temp1 = temp1->next;
		}

		temp = temp->next;
		temp1 = h;
	}


	return OKAY;
}
int InputBehind(Position h) {
	Position pr;
	char iza[MAX_NAME];
	int succ;

	printf("Enter surname of the element: ");
	scanf(" %s", iza);

	pr = FindL(h, iza);

	succ = InputP(pr);
	if (succ == ERR) {
		printf("Input from behind doesn't work.........");
		return ERR;
	}

	return OKAY;
}
int InputForward(Position h) {
	char ispred[MAX_NAME];
	Position pred;
	int succ;

	printf("Enter surname of the element: ");
	scanf(" %s", ispred);

	pred = FindPrevious(h, ispred);

	succ = InputP(pred);
	if (succ == ERR) {
		printf("Input doesnt work");
		return ERR;
	}

	return OKAY;

}
int WriteFile(Position h) {

	FILE* fp;

	fp = fopen("studenti.txt", "w");
	if (fp == NULL) {
		printf("Error while opening the file....");
		return ERR;
	}
	rewind(fp);

	while (h != NULL) {
		fprintf(fp, "%s %s %d\n", h->name, h->surname, h->year);
		h = h->next;
	}

	fclose(fp);
	return OKAY;
}
int ReadFile(Position h) {
	FILE* fp;

	fp = fopen("studenti1.txt", "r");
	if (fp == NULL) {
		printf("Error while opening the file");
		return ERR;
	}
	rewind(fp);

	while (!feof(fp)) {
		Position q;
		q = (Position)malloc(sizeof(student));
		q->next = NULL;

		fscanf(fp, "%s %s %d", q->name, q->surname, &q->year);
		q->next = h->next;
		h->next = q;
	}
	fclose(fp);
	return OKAY;
}