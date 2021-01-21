#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

typedef struct cvor* Pozicija;

struct cvor
{
	int element;
	Pozicija next;
};

int Odabir();
int DatUnos(Pozicija head, char* fileName);
int StringUnos(Pozicija head, char* line);
int SortUnos(Pozicija head, int elem);
int Unos(Pozicija head, int elem);
int Unija(Pozicija head, Pozicija p, Pozicija r);
int Presjek(Pozicija head, Pozicija p, Pozicija r);
int Ispis(Pozicija head);

int main()
{
	int success;
	success = Odabir();
	if (success == 0)
	{
		printf("Radi");
	}
	else
	{
		printf("Ne radi");
	}
	return 0;
}

int Odabir()
{
	char datoteka_1[SIZE] = "datoteka_1";
	char datoteka_2[SIZE] = "datoteka_2";
	int success = 0, c = 0;
	struct cvor head1, head2, r;
	head1.next = NULL;
	head2.next = NULL;
	r.next = NULL;
	success = DatUnos(&head1, datoteka_1);
	success = DatUnos(&head2, datoteka_2);
	success = Ispis(head1.next);
	success = Ispis(head2.next);
	printf("Za uniju birajte 1, za presjek 2");
	scanf("%d", &c);
	switch (c)
	{
		case(1):
		{
			success = Unija(head1.next, head2.next, &r);
			if (success != 0)
			{
				printf("Kriva unija!");
			}
			break;
		}
		case(2):
		{
			success = Presjek(head1.next, head2.next, &r);
			if (success != 0)
			{
				printf("Krivi presjek!");
			}
			break;
		}
		default:
		{
			return -1;
		}
	}
	success = Ispis(r.next);
	return 0;
}

int DatUnos(Pozicija head, char* fileName)
{
	int success = 0;
	FILE* fp = NULL;
	char line[SIZE] = { '\0' };
	if (strstr(fileName, ".txt") == NULL)
	{
		strcat(fileName, ".txt");
	}
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		perror("Datoteka greska");
		return -1;
	}
	while (!feof(fp)) 
	{
		fgets(line, SIZE, fp);
		success = StringUnos(head, line);
	}
	fclose(fp);
	return 0;
}

int StringUnos(Pozicija head, char* line)
{
	int ret = 0;
	int n = 0, success = 0;
	int elem;
	while (1) 
	{
		ret = sscanf(line, "%d %n", &elem, &n);
		line += n;
		if (ret != 1)
		{
			break;
		}
		success = SortUnos(head, elem);
	}
	return 0;
}

int SortUnos(Pozicija head, int elem)
{
	int success = 0;
	while (head->next != NULL && head->next->element < elem)
	{
		head = head->next;
	}
	if (head->next != NULL && head->next->element == elem)
	{
		return 0;
	}
	success = Unos(head, elem);
	return 0;
}

int Unos(Pozicija head, int elem)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(struct cvor));
	if (q == NULL)
	{
		return -1;
	}
	q->element = elem;
	q->next = head->next;
	head->next = q;
	return 0;
}
int Unija(Pozicija head, Pozicija p, Pozicija r)
{
	int elem = 0;
	int success = 0;
	while (head != NULL && p != NULL)
	{
		if (head->element == p->element)
		{
			elem = head->element;
			success = Unos(r, elem);
			head = head->next;
			p = p->next;
			r = r->next;
		}
		else if (head->element > p->element)
		{
			elem = p->element;
			success = Unos(r, elem);
			p = p->next;
			r = r->next;
		}
		else
		{
			elem = head->element;
			success = Unos(r, elem);
			head = head->next;
			r = r->next;
		}
	}
	while (head != NULL)
	{
		elem = head->element;
		success = Unos(r, elem);
		head = head->next;
		r = r->next;
	}
	while (p != NULL)
	{
		elem = p->element;
		success = Unos(r, elem);
		p = p->next;
		r = r->next;
	}
	return 0;
}
int Presjek(Pozicija head, Pozicija p, Pozicija r)
{
	int elem = 0, success = 0;
	while (head != NULL && p != NULL)
	{
		if (head->element == p->element)
		{
			elem = head->element;
			success = Unos(r, elem);
			head = head->next;
			p = p->next;
			r = r->next;
		}
		else if (head->element > p->element)
		{
			p = p->next;
		}
		else
		{
			head = head->next;
		}
	}
	return 0;
}

int Ispis(Pozicija head)
{
	while (head != NULL)
	{
		printf("%d ", head->element);
		head = head->next;
	}
	printf("\n");
	return 0;
}
