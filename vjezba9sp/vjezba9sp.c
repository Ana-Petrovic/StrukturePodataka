#include <stdio.h> 
#include <stdlib.h>

struct _cvor;
typedef struct _cvor* Stablo;

typedef struct _cvor
{
	int element;
	Stablo L;
	Stablo D;
}Cvor;

Stablo kreirajCvor(int element);
Stablo unesiCvor(Stablo stablo, Stablo element);
void ispisInOrder(Stablo stablo);
Stablo traziCvor(Stablo stablo, int element);
Stablo traziMax(Stablo stablo);
Stablo traziMin(Stablo stablo);
Stablo brisiCvor(Stablo stablo, int element);
Stablo brisiSve(Stablo stablo);

int main() 
{
	Stablo root = NULL;
	Stablo p = NULL;
	Stablo trazi = NULL;
	Stablo brisi = NULL;
	p = kreirajCvor(16);
	root = unesiCvor(root, p);
	p = kreirajCvor(7);
	root = unesiCvor(root, p);
	p = kreirajCvor(19);
	root = unesiCvor(root, p);
	p = kreirajCvor(6);
	root = unesiCvor(root, p);
	p = kreirajCvor(8);
	root = unesiCvor(root, p);
	p = kreirajCvor(3);
	root = unesiCvor(root, p);
	ispisInOrder(root);
	puts("\n");
	trazi = traziCvor(root, 7);
	printf("%d", trazi->element);
	puts("\n");
	brisiCvor(root, 3);
	ispisInOrder(root);
	brisiSve(root);
	return 0;
}

Stablo kreirajCvor(int element)
{
	Stablo p = NULL;
	p = (Stablo)malloc(sizeof(Cvor));
	if (NULL == p)
	{
		printf("Alokacija falivena");
		return NULL;
	}
	p->element = element;
	p->D = NULL;
	p->L = NULL;
	return p;
}

Stablo unesiCvor(Stablo stablo, Stablo p)
{
	if (NULL == stablo)
	{
		return p;
	}
	if (stablo->element > p->element)
	{
		stablo->L = unesiCvor(stablo->L, p);
	}
	else if (stablo->element < p->element)
	{
		stablo->D = unesiCvor(stablo->D, p);
	}
	else
	{
		printf("Element %d veæ postoji", p->element);
		free(p);
	}
	return stablo;
}

void ispisInOrder(Stablo stablo)
{
	if (NULL == stablo)
	{
		return;
	}
	ispisInOrder(stablo->L);
	printf("%d ", stablo->element);
	ispisInOrder(stablo->D);
}

Stablo traziCvor(Stablo stablo, int element)
{
	if (NULL == stablo) 
	{
		return NULL;
	}
	if (stablo->element == element)
	{
		return stablo;
	}
	else if (stablo->element > element)
	{
		return traziCvor(stablo->L, element);
	}
	else
	{
		return traziCvor(stablo->D, element);
	}
}

Stablo traziMax(Stablo stablo)
{
	if (NULL != stablo)
	{
		while (NULL != stablo->D)
		{
			stablo = stablo->D;
		}
	}
	return stablo;
}

Stablo traziMin(Stablo stablo)
{
	if (NULL != stablo)
	{
		while (NULL != stablo->L)
		{
			stablo = stablo->L;
		}
	}
	return stablo;
}

Stablo brisiCvor(Stablo stablo, int element)
{
	if (NULL == stablo)
	{
		printf("Ne postoji element %d. ", element);
		return stablo;
	}
	else if (element < stablo->element)
	{
		stablo->L = brisiCvor(stablo->L, element);
	}
	else if(element > stablo->element)
	{
		stablo->D = brisiCvor(stablo->D, element);
	}
	else
	{
		Stablo temp = NULL;
		if (NULL != stablo->L && NULL != stablo->D)
		{
			temp = traziMin(stablo->D);
			stablo->element = temp->element;
			stablo->D = brisiCvor(stablo->D, temp->element);
		}
		else
		{
			temp = stablo;
			if (NULL == stablo->L)
			{
				stablo = stablo->D;
			}
			else
			{
				stablo = stablo->L;
			}
			free(temp);
		}
	}
	return stablo;
}

Stablo brisiSve(Stablo stablo)
{
	if (NULL != stablo)
	{
		brisiSve(stablo->L);
		brisiSve(stablo->D);
		free(stablo);
	}
	return NULL;
}
