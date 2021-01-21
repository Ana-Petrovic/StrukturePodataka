#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024
#define ELEMENT_SIZE 20

struct _cvor;
typedef struct _cvor* Stablo;
typedef struct _cvor
{
	char element[ELEMENT_SIZE];
	Stablo L;
	Stablo D;
}Cvor;

struct _stog;
typedef struct _stog* Pozicija;
typedef struct _stog
{
	Stablo cvorStabla;
	char element[ELEMENT_SIZE];
	Pozicija next;
}Stog;


Stablo KreirajCvor(char* element);
int PushStog(Pozicija head, Stablo s);
int PushRed(Pozicija r, char* element);
int Pop(Pozicija head);
char* UpisIzDatoteke(char* fileName);
int UpisIzStringa(char* buffer, Pozicija head);
int UpisUDatoteku(Pozicija r, char* fileName);
void IspisInOrder(Stablo s, Pozicija r);
int JeliBroj(char* element);
int BrisiListu(Pozicija head);
int BrisiStablo(Stablo s);


int main()
{
	Pozicija head = NULL;
	Pozicija red = NULL;
	char imeUlazneDatoteke[SIZE] = "postfix.txt";
	char imeIzlazneDatoteke[SIZE] = "infix.txt";
	head = (Pozicija)malloc(sizeof(Stog));
	if (head == NULL)
	{
		puts("Alokacija falivena");
		return -1;
	}
	head->next = NULL;
	red = (Pozicija)malloc(sizeof(Stog));
	if (red == NULL)
	{
		puts("Alokacija falivena");
		return -1;
	}
	red->next = NULL;
	UpisIzStringa(imeUlazneDatoteke, head);
	IspisInOrder(head->next->cvorStabla, red);
	UpisUDatoteku(red, imeIzlazneDatoteke);
	BrisiStablo(head->next->cvorStabla);
	BrisiListu(red);
	BrisiListu(head);
}

int PushStog(Pozicija head, Stablo s) 
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Stog));
	if (NULL == q)
	{
		printf("Stog alokacija falivena");
		return -1;
	}
	q->cvorStabla = s;
	q->next = head->next;
	head->next = q;
	return 0;
}

int PushRed(Pozicija r, char* element)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Stog));
	if (NULL == q)
	{
		printf("Stog alokacija falivena");
		return -1;
	}
	strcpy(q->element, element);
	q->next = r->next;
	r->next = q;
	return 0;
}

int Pop(Pozicija head)
{
	Pozicija tmp;
	if (head->next == NULL)
	{
		return 0;
	}
	else
	{
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}
	return 0;
}

Stablo KreirajCvor(char* element)
{
	Stablo p = NULL;
	p = (Stablo)malloc(sizeof(Cvor));
	if (NULL == p)
	{
		printf("Alokacija falivena");
		return NULL;
	}
	strcpy(p->element, element);
	p->D = NULL;
	p->L = NULL;
	return p;
}

char* UpisIzDatoteke(char* fileName)
{
	FILE* fp = NULL;
	char bufferZaDuljinu[SIZE] = { '\0' };
	char* buffer = NULL;
	int duljinaStringa;
	if (strstr(fileName, ".txt") == 0)
	{
		strcat(fileName, ".txt");
	}
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena");
		return NULL;
	}
	fgets(bufferZaDuljinu, SIZE, fp);
	rewind(fp);
	duljinaStringa = strlen(bufferZaDuljinu);
	duljinaStringa += 1;
	buffer = (char*)malloc((duljinaStringa) * sizeof(char));
	if (buffer == NULL)
	{
		printf("String malloc faliven");
		return NULL;
	}
	fgets(buffer, duljinaStringa, fp);
	fclose(fp);
	return buffer;
}

int UpisIzStringa(char* fileName, Pozicija head)
{
	int retVal = 0;
	int succ = 0, n = 0;
	char element[ELEMENT_SIZE] = { '\0' };
	char op = '\0';
	char* buffer;
	buffer = UpisIzDatoteke(fileName);
	while (1)
	{
		retVal = sscanf(buffer, "%s%n", &element, &n);
		if (retVal != 1)
		{
			puts("Unos gotov");
			break;
		}
		if(JeliBroj(element))
		{
			PushStog(head, KreirajCvor(element));
		}
		else
		{
			if (element != ' ')
			{
				Stablo opStablo = KreirajCvor(element);
				opStablo->D = head->next->cvorStabla;
				Pop(head);
				opStablo->L = head->next->cvorStabla;
				Pop(head);
				PushStog(head, opStablo);
			}
		}
		buffer += n;
	}
	return 0;
}

void IspisInOrder(Stablo s, Pozicija r)
{
	if (NULL == s)
	{
		return;
	}
	IspisInOrder(s->L, r);
	printf("%s ", s->element);
	PushRed(r, s->element);
	IspisInOrder(s->D, r);
}

int UpisUDatoteku(Pozicija r, char* fileName)
{

	FILE* fp;
	if (strstr(fileName, ".txt") == 0)
	{
		strcat(fileName, ".txt");
	}
	fp = fopen(fileName, "w");
	if (fp == NULL)
	{
		printf("Upisna datoteka nije otvorena");
		return -1;
	}
	rewind(fp);
	while (r != NULL)
	{
		fprintf(fp, "%s ", r->element);
		r = r->next;
	}
	fclose(fp);
	return 0;
}

int JeliBroj(char* element)
{
	int number = 0;
	if (sscanf(element, "%d", &number) == 1)
	{
		return 1;
	}
	return 0;
}

int BrisiListu(Pozicija head)
{
	Pozicija temp;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}

int BrisiStablo(Stablo s)
{
	if (NULL != s)
	{
		BrisiStablo(s->L);
		BrisiStablo(s->D);
		free(s);
	}
}
