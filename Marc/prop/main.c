#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define AND  "∧"
#define OR "∨"
char nums[10][10] =  {"₀","₁","₂","₃","₄","₅","₆","₇","₈","₉"};

struct litteral {
    int ident;
    bool negatif;
};
typedef struct litteral litteral;

struct clause {
    int nlitteraux;
    litteral *litteraux;
};
typedef struct clause clause;

struct formule {
    int nclauses;
    clause *clauses;
};
typedef struct formule formule;

void libere_formule(formule *f){
	for(int i=0; i < f->nclauses; i++){// pour chaque clause
		free(f->clauses[i].litteraux);
	}
	free(f);
}

int num_variables(formule *f){
	int max = -1;
	for(int i=0; i < f->nclauses; i++){// pour chaque clause
		for(int j=0; j < f->clauses[i].nlitteraux; j++){
			int v = f->clauses[i].litteraux[j].ident;
			max = (v > max) ? v : max;
		}
	}
	return max + 1;
}

void affiche_formule(formule *f){
	for(int i=0; i < f->nclauses; i++){
		int l = f->clauses[i].nlitteraux;
		if(l>1)printf("(");
		for(int j=0; j < l; j++){
			int v = f->clauses[i].litteraux[j].ident;
			printf("X%s",nums[v]);
			if(j+1 < l) printf(OR);
		}
		if(l>1)printf(")");
		if(i+1<f->nclauses) printf(AND);
	}
	printf("\n");
}

bool evalue_litteral(litteral *l, bool *valuation){
	if(valuation[l->ident]){
		return l->negatif;
	}else{
		return !l->negatif;
	}
}

bool evalue_clause(clause *c, bool *valuation){
	int b = false;
	for(int j = 0; j < c->nlitteraux; j++)
		b = b || evalue_litteral(c->litteraux+j, valuation);
	return b;
}

bool evalue(formule *f, bool *valuation){	
	int b = true;
	for(int i = 0; i < f->nclauses; i++)
		b = b && evalue_clause(f->clauses+i, valuation);
	return b;
}

bool suivante(int n, bool *valuation){
	for(int i=0;i<n;i++){
		if(valuation[i]){
			valuation[i] = 0;
		}else{
			valuation[i] = 1;
			return true;
		}
	}
	return false;
}
			
bool tautologie(formule *f){
	int n = num_variables(f);
	bool * valuation = calloc(n,sizeof(bool));
	do{
		if(!evalue(f,valuation))
			return false;
	}while(suivante(n,valuation));
	return true;
}

bool * satisfiable(formule *f){
	int n = num_variables(f);
	bool * valuation = calloc(n,sizeof(bool));
	do{
		if(evalue(f,valuation))
			return valuation;
	}while(suivante(n,valuation));
	return NULL;
}

bool consequence(formule *f, formule *g){
	int n = num_variables(f);
	bool * valuation = calloc(n,sizeof(bool));
	do{
		if(evalue(f,valuation) && !evalue(g,valuation)){
			free(valuation);
			return false;
		}
	}while(suivante(n,valuation));
	free(valuation);
	return true;
}


int main(void){
	// FNC
	formule *f = malloc(sizeof(formule));
	f->nclauses = 3;
	f->clauses = malloc(sizeof(clause)*3);
	// Première clause
	f->clauses[0].nlitteraux = 2;
	f->clauses[0].litteraux = malloc(sizeof(clause)*2);
	f->clauses[0].litteraux[0].ident = 0;
	f->clauses[0].litteraux[0].negatif= 0;
	f->clauses[0].litteraux[1].ident = 1;
	f->clauses[0].litteraux[1].negatif= 1;
	// Deuxième clause
	f->clauses[1].nlitteraux = 3;
	f->clauses[1].litteraux = malloc(sizeof(clause)*3);
	f->clauses[1].litteraux[0].ident = 1;
	f->clauses[1].litteraux[0].negatif= 0;
	f->clauses[1].litteraux[1].ident = 2;
	f->clauses[1].litteraux[1].negatif= 1;
	f->clauses[1].litteraux[2].ident = 0;
	f->clauses[1].litteraux[2].negatif= 1;
	// Deuxième clause
	f->clauses[2].nlitteraux = 1;
	f->clauses[2].litteraux = malloc(sizeof(clause));
	f->clauses[2].litteraux[0].ident = 2;
	f->clauses[2].litteraux[0].negatif= 1;

	printf("Nombre de variables : %d\n",num_variables(f));
	affiche_formule(f);	
	printf("Tautologie : %d\n",tautologie(f));
	libere_formule(f);
}




