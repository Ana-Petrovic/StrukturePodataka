
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR (-1)
#define OKAY 0
#define MAX_NAME 256

typedef struct _student* Pozicija;
typedef struct _student {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int year;
	Pozicija next;
}student;


int InputP(Pozicija h);
int InputK(Pozicija h);
int Print(Pozicija h);
Pozicija FindLast(Pozicija h);
Pozicija FindBefore(Pozicija h, char prez);
int DeleteElement(Pozicija h);

int main() {

	int succ;
	student Head;
	Pozicija tr;
	Head.next = NULL;

	succ = InputP(&Head);
	if (succ == ERR)
		printf("Inputp doesnt work ");

	succ = InputP(&Head);
	if (succ == ERR)
		printf("unosP doesnt work");

	succ = InputK(&Head);
	if (succ == ERR)
		printf("inoutK doesnt work");

	succ = Print(Head.next);
	if (succ == ERR)
		printf("Print doesnt work");

	tr = FindLast(&Head);
	if (tr == ERR)
		printf("Error occured");

	printf("Surname is: %s", tr->surname); 


	succ = DeleteElement(&Head);
	if (succ != OKAY)
		printf("Delete ERR");

	succ = Print(Head.next);
	if (succ == ERR)
		printf("Print Err");

	return 0;
}

int InputP(Pozicija h) {

	Pozicija p;
	p = (Pozicija)malloc(sizeof(student));
	if (p == NULL)
		return ERR;


	printf("Unesite ime prezime i godinu rodjenja(U istom ovom formatu!!):\n");
	scanf("%s %s %d", p->name, p->surname &p->year);

	p->next = h->next;
	h->next = p;

	return OKAY;
}
int InputK(Pozicija h) {

	int succ;
	while (h->next != NULL) {
		h = h->next;

		succ = InputP(h);
		if (succ == ERR) {
			printf("Error");
			return ERR;
		}
			
	}
	

	return OKAY;
}
int Print(Pozicija h) {

	printf("List print:\n\n");

	while (h != NULL) {
		printf("%s %s %d\n", h->name, h->surname, h->year);
		h = h->next;
	}

}
Pozicija FindLast(Pozicija h) {

	char prez[MAX_NAME];
	printf("Enter the surname that you need: ");
	scanf("%s/n", prez);

	while (h != NULL && strcmp(h->surname, prez) != 0)
		h = h->next;

	return h;
}
Pozicija FindBefore(Pozicija h, char prez) {

	Pozicija Prev = h;
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
int DeleteElement(Pozicija h) {

	char prez[MAX_NAME];
	Pozicija Prev;

	printf("Enter the name: ");
	scanf("%s\n", prez);

	Prev = FindBefore(h, prez);

	if (Prev != NULL) {
		h = Prev->next;
		Prev->next = h->next;
		free(h);
	}

	return OKAY;
}