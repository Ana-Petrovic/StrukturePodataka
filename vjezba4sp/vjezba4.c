#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR (-1)
#define OKAY 0
#define lng 1024

typedef struct poli* Polinom;
struct poli {
	double Koef;
	int Exp;
	Polinom next;
};

int Selection();
int Err();
int InputFile(Polinom p, char* fileName);
int InputString(Polinom p, char* line);
int SortInput(Polinom p, double koef, int exp);
int Input(Polinom p, double koef, int exp);
int PolAddition(Polinom p, Polinom q, Polinom r);
int MulPolinom(Polinom p, Polinom q, Polinom r);
int PrintPol(Polinom p);


int main() {

	int succ = Selection();
	if (succ == OKAY)
		printf("\n\nSuccess");
	else
		Err();

	return 0;
}

int Selection() {
	int c;
	int succ;
	char poli1[lng] = "pol1";
	char poli2[lng] = "pol2";

	struct poli p1;
	struct poli p2;
	struct poli rez;

	p1.next = NULL;
	p2.next = NULL;
	rez.next = NULL;

	succ = InputFile(&p1, &poli1);
	if (succ != OKAY)
		printf("Error Input1 ");
	succ = PrintPol(p1.next);

	succ = InputFile(&p2, &poli2);
	if (succ != OKAY)
		printf("Error Input2");
	succ = PrintPol(p2.next);

	printf("Select the operation:\n1 - Polinom Additiom\n2 - Multipying polinoms\n");
	scanf("%d", &c);

	switch (c) {
	case(1):
		succ = PolAddition(p1.next, p2.next, &rez);
		if (succ != OKAY)
			printf("Addition dosen't work!");
		break;

	case(2):
		succ = MulPolinom(p1.next, p2.next, &rez);
		if (succ != OKAY)
			printf("Addition dosen't work!");
		break;

	default:
		Err();
		return ERR;
	}
	succ = PrintPol(p1.next);
	succ = PrintPol(p2.next);
	succ = PrintPol(rez.next);

	return OKAY;
}

int Err() {
	printf("Error!");
	return OKAY;
}

int InputFile(Polinom p, char* fileName) {

	FILE* fp = NULL;
	char line[lng] = { '\0' };


	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("datERROR");
		return ERR;
	}

	while (!feof(fp)) {
		memset(line, '\0', lng); 
		fgets(line, lng - 1, fp);
		InputString(p, line);
	}

	fclose(fp);

	return OKAY;
}

int InputString(Polinom p, char* line) {
	int ret = 2; 
	double p_koef = 0;
	int p_exp = 0;
	int n = 0;

	while (1) {
		ret = sscanf(line, "%lf %d %n", &p_koef, &p_exp, &n);
		line += n;
		if (ret != 2)
			break;
		SortInput(p, p_koef, p_exp);
	}

	return OKAY;
}
int SortInput(Polinom p, double koef, int exp) {

	int succ;
	Polinom temp;

	while (p->next != NULL && p->next->Exp < exp)
		p = p->next;

	if (p->next != NULL && p->next->Exp == exp) {
		p->Koef += koef;

		if (p->next->Koef == 0) {
			temp = p->next;
			p->next = p->next->next;
			free(temp);
		}
	}
	else
		succ = Input(p, koef, exp);

	return OKAY;
}
int Input(Polinom p, double koef, int exp) {

	Polinom q;

	q = (Polinom)malloc(sizeof(struct poli));
	if (q == NULL)
		return ERR;

	q->Exp = exp;
	q->Koef = koef;

	q->next = p->next;
	p->next = q;

	return OKAY;
}

int PolAddition(Polinom p, Polinom q, Polinom r) {

	double t_koef;
	int t_exp;

	while (p != NULL && q != NULL) {
		if (p->Exp == q->Exp) {
			t_koef = p->Koef + q->Koef;
			t_exp = p->Exp; 
			SortInput(r, t_koef, t_exp);
			p = p->next;
			q = q->next;
		}
		else if (p->Exp < q->Exp) {
			t_koef = p->Koef;
			t_exp = p->Exp;
			SortInput(r, t_koef, t_exp);
			p = p->next;
		}
		else {
			t_koef = q->Koef;
			t_exp = q->Exp;
			SortInput(r, t_koef, t_exp);
			q = q->next;
		}

	}
	while (p != NULL) {
		t_koef = p->Koef;
		t_exp = p->Exp;
		SortInput(r, t_koef, t_exp);
		p = p->next;
	}

	while (q != NULL) {
		t_koef = q->Koef;
		t_exp = q->Exp;
		SortInput(r, t_koef, t_exp);
		q = q->next;
	}

	return OKAY;
}
int MulPolinom(Polinom p, Polinom q, Polinom r) {

	Polinom pamti_q = q;
	double t_koef;
	int t_exp;
	int succ;

	while (p != NULL) {
		while (q != NULL) {
			t_koef = p->Koef * q->Koef;
			t_exp = p->Exp + q->Exp;
			succ = SortInput(r, t_koef, t_exp);
			q = q->next;
		}
		q = pamti_q;
		p = p->next;
	}

	return OKAY;
}
int PrintPol(Polinom p) {

	printf("\nPrinting polinoms:\n\n");

	while (p != NULL) {
		printf("(%.2lf * x ^ %d) ", p->Koef, p->Exp);
		p = p->next;
	}

	return OKAY;
}