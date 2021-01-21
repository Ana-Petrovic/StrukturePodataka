#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 255
#define DG 10
#define GG 100

struct cvor;
typedef struct cvor* Pozicija;

struct cvor
 {
	int element;
	Pozicija next;
 };

int Odabir();
int Greska();
char* UnosDat(char* fileName);
int UnosString(Pozicija head, char* buffer);
int Push(Pozicija head, int broj);
int Pop(Pozicija head);
int Racunaj(Pozicija head, char op);
int Ispis(Pozicija head);
int Brisi(Pozicija head);

int main()
{
	int succes;
	succes = Odabir();
	if (succes == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int Odabir()
{
	int succes;
	char fileName[SIZE];
	char* buffer = NULL;
	Pozicija head;
	head = (Pozicija)malloc(sizeof(struct cvor));
	if (head == NULL)
	{
		printf("Malloc greska");
		return -1;
	}
	head->next = NULL;
	printf("Ime datoteke: ");
	scanf(" %s", fileName);
	buffer = UnosDat(fileName);
	if (NULL == buffer)
	{
		printf("Pokvarena datoteka");
		return -1;
	}
	printf("Postfix: %s", buffer);
	succes = UnosString(head, buffer);
	succes = Ispis(head->next);
	if (succes == -1)
	{
		printf("Greska u odabiru");
		return -1;
	}
	succes = Brisi(head);
	if (succes == -1)
	{
		printf("Greska u odabiru");
		return -1;
	}
	free(head);
}

int Greska()
{
	printf("Error");
	return -1;
}

char* UnosDat(char* fileName)
{
	FILE* fp = NULL;
	char bufferZaDuljinu[SIZE] = {'\0'};
	char* buffer  = NULL;
	int duljinaStringa;
	if(strstr(fileName, ".txt") == 0)
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

int UnosString(Pozicija head, char* buffer)
{
	int retVal = 0;
	int succes = 0, n = 0;
	int element;
	char op;
	while (1)
	{
		retVal = sscanf(buffer, "%d %n", &element, &n);
		if (retVal == 1)
		{
			succes = Push(head, element);
		}
		else
		{
			retVal = sscanf(buffer, "%c%n", &op, &n);
			if (retVal == 1) 
			{
				if (op != ' ')
				{
					succes = Racunaj(head, op);
				}
			}
			else
			{
				break;
			}
		}
		buffer += n;
	}
}

int Push(Pozicija head, int broj)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(struct cvor));
	if (NULL == q)
	{
		printf("Push alokacija falivena");
		return -1;
	}
	q->element = broj;
	q->next = head->next;
	head->next = q;
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

int Racunaj(Pozicija head, char op)
{
	int operandPrvi, operandDrugi;
	int succes;
	operandDrugi = head->next->element;
	operandPrvi = head->next->next->element;
	succes = Pop(head);
	succes = Pop(head);
	switch (op)
	{
	    case('+'):
		{
			succes = Push(head, operandPrvi + operandDrugi);
			break;
		}
	    case('-'):
		{
			succes = Push(head, operandPrvi - operandDrugi);
			break;
		}
	    case('*'):
		{
			succes = Push(head, operandPrvi * operandDrugi);
			break;
		}
	    case('/'):
		{
			succes = Push(head, operandPrvi / operandDrugi);
			break;
		}
		default:
		{
			return -1;
		}
	}
	return 0;
}

int Ispis(Pozicija head)
{
	printf("\n");
	while (head != NULL)
	{
		printf("%d ", head->element);
		head = head->next;
	}
	printf("\n");
	return 0;
}

int Brisi(Pozicija head)
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