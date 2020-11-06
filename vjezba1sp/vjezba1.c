#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#define ERR (-1)
#define MAX_NAME 256

typedef struct _stud
{
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int result;
}student;

int RowCounter();
int Input(student*, int);
int Output(student*, int);

int main() {

	student* a = NULL;
	int br, inputVar, outputVar;

	br = RowCounter();

	if (br == ERR) {
		printf("Datoteka nije otvorena!(br.redaka)");
	}
	printf("Broj redaka je: %d\n", br);

	a = (student*)malloc(br * sizeof(student));

	if (a == NULL)
		printf("Allocation failed");

	inputVar = Input(a, br);

	if (inputVar == ERR)
		printf("Datoteka nije otvorena!(unos)");

	outputVar = Output(a, br);

	if (outputVar != 0)
		printf("There is no output");

	free(a);

	return 0;

}

int RowCounter() {

	FILE* fp = fopen("student.txt", "r");
	int brojac = 0;

	if (fp == NULL)
	{
		printf("Error occured");
		return ERR;
	}
	rewind(fp);

	while (!feof(fp))
	{
		fscanf(fp, "%*s %*s %*d");
		brojac++;
	}
	fclose(fp);

	return brojac;

}

int Input(student* a, int br) {

	int i;
	FILE* fp = fopen("student.txt", "r");
	int brojac = 0;

	if (fp == NULL)
	{
		printf("Error occured");
		return ERR;
	}

	rewind(fp);

	for (i = 0; i < br; i++)
		fscanf(fp, "%s %s %d", a[i].firstName, a[i].lastName, &a[i].result);


	fclose(fp);

	return 0;
}

int Output(student* a, int br) {
	int i;

	for (i = 0; i < br; i++)
		printf("%s %s %d %.2f\n", a[i].firstName, a[i].lastName, a[i].result, ((float)a[i].result / 50) * 100);

	return 0;
}