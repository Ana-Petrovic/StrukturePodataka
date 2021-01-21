#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define SIZE 255
#define DG 10
#define GG 100

typedef struct Cvor* Pozicija;
struct Cvor
 {
	int broj;
	Pozicija next;
 };

int Odabir();
int Stog(Pozicija head);
int Red(Pozicija head);
int Greska();
int RandBr(); 
int PushStog(Pozicija head, int broj);
int PopStog(Pozicija head);
int PushRed(Pozicija head, int broj);
int PopRed(Pozicija head);
int Ispis(Pozicija head);

int main() 
{
	int succes;
	succes = Odabir();
	if (succes == 0) 
	{
		printf("Sve je okay!");
		return -1;
	} 
	    else if (succes == -2)
		printf("Izasli smo s izlazom.");
	    else
		printf("Nece nesto!");

	return 0;
};

int Odabir()
{
	int c = 0;
	int succes = 0;
	srand(time(NULL));
	struct Cvor head;
	head.next = 0;

	while (1)
		{
		printf("\nZelite li koristiti stog ili red?\n1 - Stog\n2 - Red\n3 - Izlaz iz programa\n");
		scanf("%d", &c);
		
		switch (c)
		{
		case(1):
			succes = Stog(&head);
			break;
			
		case(2):
			succes = Red(&head);
			break;

		case(3):
			return -2;
			break;
			
		default:
			printf("\nUnijeli ste nesto krivo! Pokusajte ponovno!\n\n");
		}
		if (c == 3)
			break;
	    }
		
	return 0;
}

int Stog(Pozicija head)
{

	int i;
	int n; 
	int c;
	int succes;
	int broj;

	while (1) 
	{
		printf("\n1 - Push\n2 - Pop\n3 - Kraj\n");
		scanf("%d", &c);
	switch(c)
		{
		case 1:
		{
			broj = RandBr();
			PushStog(head, broj);
			succes = Ispis(head->next);
			break;
		}
		case 2:
		{
			PopStog(head);
			succes = Ispis(head->next);
			break;
		}
		case 3:
		{
			succes = Brisi(head);
			break;
		}
		default:
		{
			printf("Unijeli ste nesto krivo! Pokusajte ponovno!");
		}
		}
		if (c == 3)
			break;
	}
	return 0;
}

int Red(Pozicija head)
{
	int i;
	int n;
	int c;
	int broj;
	int succes;

	while (1) {
		printf("\n1 - Push\n2 - Pop\n3 - Kraj\n");
		scanf("%d", &c);

		switch (c) {
		case 1:
			broj = RandBr();
			PushRed(head, broj);
			succes = Ispis(head->next);
			break;

		case 2:
			PopRed(head);
			succes = Ispis(head->next);
			break;

		case 3:
			succes = Brisi(head);
			break;

		default:
			printf("Unijeli ste nesto pogresno! Pokusajte ponovno!");
		}
		if (c == 3)
			break;
	}
	return -2;
}

int Greska()
{
	printf("Nešto nece!");

	return -1;
}

int RandBr()
{

	return rand() % (GG - DG + 1);
}

int PushStog(Pozicija head, int broj)
   {
	Pozicija q = NULL;
	
	q = (Pozicija)malloc(sizeof(struct Cvor));
	if (NULL == q)
		{
		printf("Nece alokacija(push stog)");
		return -1;
	    }
	q->broj = broj;

	q->next = head->next;
	head->next = q;
	
	return 0;
   }

int PopStog(Pozicija head)
{
	Pozicija tmp;
	if (head->next == NULL)
		return 0;
	else {
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}

	return 0;
}

int PushRed(Pozicija head, int broj)
{

	while (head->next != NULL)
		head = head->next;

	PushStog(head, broj);

	return 0;
}

int PopRed(Pozicija head)
{
	Pozicija tmp;

	if (head->next == NULL)
		return 0;
	else {
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}

	return 0;
}

int Ispis(Pozicija head)
{
	while (head != NULL) {
		printf("%d ", head->broj);
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
