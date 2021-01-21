#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 255
#define DG 10
#define GG 100

struct _cvor;
typedef struct _cvor* Stablo;
typedef struct _cvor
{
	char* imeMape;
	Stablo djete;
	Stablo nextBrat;
}Cvor; 

struct _stog;
typedef struct _stog* Pozicija;
typedef struct _stog
{
	Stablo cvorStabla;
	Pozicija next;
}Stog;

int mainMenu();
char* CharAlokacija(char* string);
int Push(Pozicija head, Stablo stablo);
Stablo Pop(Pozicija head);
int ProstorZaNovuMapu(Stablo* stablo);
int NovaMapa(Stablo stablo, char* imeMape);
Stablo PromijeniMapu(Stablo stablo, Pozicija head, char* imeMape, char* path);
Stablo NatragMapa(Stablo stablo, Pozicija head, char* path);
int PrikaziSveMape(Stablo stablo);
int IspisPutanje(char* path);
int BrisiStablo(Stablo stablo);
int BrisiStog(Pozicija head);

int main()
{
	int success;
	success = mainMenu();
	if (success != 0)
	{
		return -1;
	}
	return 0;
}

int mainMenu()
{
	Stablo root = NULL;
	Stablo trenutnaPozicija = NULL;
	Pozicija head = NULL;
	char* naredbeniRedak = "\0";
	char* naredba = "\0";
	char* imeMape = "\0";
	char* putanja = "\0";
	int retVal = 0;
	int success = 0;
	naredbeniRedak = CharAlokacija(naredbeniRedak);
	naredba = CharAlokacija(naredba);
	imeMape = CharAlokacija(imeMape);
	putanja = CharAlokacija(putanja);
	ProstorZaNovuMapu(&root);
	root->imeMape = (char*)malloc(SIZE * sizeof(char));
	memset(root->imeMape, '\0', sizeof(root->imeMape));
	root->imeMape = "C:";
	root->djete = NULL;
	root->nextBrat = NULL;
	trenutnaPozicija = root;
	memset(putanja, '\0', sizeof(putanja));
	strcat(putanja, root->imeMape);
	head = (Pozicija)malloc(sizeof(Stog));
	if (NULL == head) return -1;
	head->next = NULL;
	while (1)
	{
		success = IspisPutanje(putanja);
		memset(naredbeniRedak, '\0', SIZE);
		memset(naredba, '\0', SIZE);
		memset(imeMape, '\0', SIZE);
		fgets(naredbeniRedak, SIZE, stdin);
		retVal = sscanf(naredbeniRedak, "%s %s", naredba, imeMape);
		if (strcmp(naredba, "md") == 0)
		{
			success = NovaMapa(trenutnaPozicija, imeMape);
		}
		else if (strcmp(naredba, "dir") == 0)
		{
			success = PrikaziSveMape(trenutnaPozicija);
		}
		else if (strcmp(naredba, "cd") == 0)
		{
			trenutnaPozicija = PromijeniMapu(trenutnaPozicija, head, imeMape, putanja);
		}
		else if (strcmp(naredba, "cd..") == 0)
		{
			trenutnaPozicija = NatragMapa(trenutnaPozicija, head, putanja);
		}
		else if (strcmp(naredba, "exit") == 0)
		{
			break;
		}
		else
		{
			printf("Neispravan unos");
		}
	}
	return 0;
}

char* CharAlokacija(char* string) 
{
	string = (char*)malloc(SIZE * sizeof(char));
	return string;
}

int Push(Pozicija head, Stablo stablo)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Stog));
	if (NULL == q)
	{
		printf("Push malloc faliven");
		return -1;
	}
	q->cvorStabla = stablo;
	q->next = head->next;
	head->next = q;
	return 0;
}

Stablo Pop(Pozicija head)
{
	Pozicija tmp;
	Stablo ret;
	if (NULL != head->next)
	{
		ret = head->next->cvorStabla;
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
		return ret;
	}
	return NULL;
}

int ProstorZaNovuMapu(Stablo* stablo)
{
	Stablo tmp = NULL;
	tmp = (Stablo)malloc(sizeof(Cvor));
	if (tmp == NULL)
	{
		return -1;
	}
	tmp->djete = NULL;
	tmp->nextBrat = NULL;
	*stablo = tmp;
	return 0;
}

int NovaMapa(Stablo stablo, char* imeMape)
{
	Stablo p;
	ProstorZaNovuMapu(&p);
	p->imeMape = (char*)malloc(sizeof(strlen(imeMape) + 1));
	strcpy(p->imeMape, imeMape);
	p->nextBrat = stablo->djete;
	stablo->djete = p;
	return 0;
}

Stablo PromijeniMapu(Stablo stablo, Pozicija head, char* imeMape, char* path)
{
	Stablo temp = stablo;
	Push(head, stablo);
	stablo = stablo->djete;
	while (NULL != stablo && strcmp(stablo->imeMape, imeMape) != 0)
	{
		stablo = stablo->nextBrat;
	}
	if (NULL == stablo)
	{
		printf("Nema mape: %s!", imeMape);
		return temp;
	}
	strcat(path, "\\");
	strcat(path, imeMape);
	return stablo;
}

Stablo NatragMapa(Stablo stablo, Pozicija head, char* path)
{
	char* krajPatha = NULL;
	Stablo temp;
	temp = Pop(head);
	if (temp == NULL)
	{
		printf("U root-u si!");
	}
	else
	{
		stablo = temp;
		krajPatha = strrchr(path, '\\');
		*krajPatha = '\0';
	}
	return stablo;
}

int PrikaziSveMape(Stablo stablo)
{
	stablo = stablo->djete;
	while (stablo != NULL)
	{
		printf("\n\t<DIR>\t %s", stablo->imeMape);
		stablo = stablo->nextBrat;
	}
	return 0;
}

int IspisPutanje(char* path)
{
	printf("\n%s>", path);
}

int BrisiStablo(Stablo stablo)
{
	if (stablo == NULL)
	{
		return 0;
	}
	BrisiStablo(stablo->djete);
	BrisiStablo(stablo->nextBrat);
	free(stablo->imeMape);
	free(stablo);
	return 0;
}

int BrisiStog(Pozicija head) 
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
