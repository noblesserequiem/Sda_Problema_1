#include<stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
	char nume[30], prenume[30];
	float nota;
	struct nod *urm;
}nod;

typedef struct arb {
	char disciplina[30];
	struct arb *st, *dr;
	struct nod *prim;
}arb;

nod *adaugare_lista(nod *prim, char nume[30], char prenume[30], float nota)
{
	nod *p, *q;
	p = (nod*)malloc(sizeof(nod));
	//p->nume = (char*)malloc(sizeof(strlen(nume) + 1));
	//p->prenume = (char*)malloc(sizeof(strlen(prenume) + 1));
	strcpy(p->nume, nume);
	strcpy(p->prenume, prenume);
	p->nota = nota;
	p->urm = NULL;
	q = prim;
	if (prim == NULL)
	{
		prim = p;
		return p;
	}
	else
	{
		if (prim->nota > p->nota)
		{
			p->urm = prim;
			return p;
		}
		else
		{
			while (q->urm != NULL && q->urm->nota < p->nota)
			{
				q = q->urm;
			}
			p->urm = q->urm;
			q->urm = p;
			
		}
	}
	return prim;
}

arb *adaugare_arbore(arb *t, char nume[30],char prenume[30],float nota,char disciplina[30])
{
	
	if (t == NULL)
	{
		arb *p;
	p = (arb*)malloc(sizeof(arb));
	//p->disciplina = (char*)malloc(sizeof(strlen(disciplina) + 1));
	p->dr = NULL;
	p->st = NULL;
	strcpy(p->disciplina, disciplina);
		t = p;
		t->prim = NULL;
		t->prim = adaugare_lista(t->prim, nume, prenume, nota);
		return t;
	}
	else
	{
		if (strcmp(t->disciplina, disciplina) < 0)
			t->dr = adaugare_arbore(t->dr, nume,prenume,nota,disciplina);
		if (strcmp(t->disciplina, disciplina) > 0)
			t->st = adaugare_arbore(t->st, nume, prenume, nota, disciplina);
		if (strcmp(t->disciplina, disciplina) == 0)
			t->prim = adaugare_lista(t->prim, nume, prenume, nota);
	}
	return t;
}
void afisare(arb *t)
{
	if (t != NULL) {
		nod *p;
		afisare(t->dr);

		if (t != NULL)
		{
			printf("%s", t->disciplina);
			p = t->prim;
			while (p != NULL)
			{
				printf("\n%s %s %f\n----------------\n", p->nume, p->prenume, p->nota);
				p = p->urm;
			}
		}
		afisare(t->st);
	}
}

arb *stergere_elev(arb *t, char nume[30])
{
	
	if (t != NULL)
	{
		nod *q, *aux;
		if (strcmp(t->prim->nume, nume) == 0)
		{
			aux = t->prim;
			t->prim = t->prim->urm;
			free(aux);
		}
		else
		{
			q = t->prim;
			while (q->urm != NULL && strcmp(q->urm->nume, nume) != 0)
			{
				q = q->urm;
			}
			if (strcmp(q->urm->nume, nume)==0)
			{
				aux = q->urm;
				q->urm = q->urm->urm;
				free(aux);
			}
		}
		t->dr = stergere_elev(t->dr,nume);
		t->st = stergere_elev(t->st,nume);
	}
	return t;
}
int main()
{
	arb *t=NULL;
	
	
	int opt;
	do {
		printf("\nopt=");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1: 
		{ 
			char nume[30], prenume[30], disciplina[30]; 
			float nota;
			scanf("%s %s %s %f", nume, prenume, disciplina, &nota); 
			t=adaugare_arbore(t, nume, prenume, nota, disciplina); 
			break; 
		}
		case 2: {afisare(t); getchar(); break; }
		case 3: {char nume[30]; scanf("%s", nume); t = stergere_elev(t, nume); break; }
		case 5: {exit(0); break; }
		}
	} while (opt != 5);

	return 0;
}