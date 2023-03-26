#include <stdio.h>
#include <stdlib.h>
#define MAX(X,Y) X>Y ? X:Y 
#define SIZE 3

struct noeud {
    struct noeud * gauche;
    struct noeud * droite;
    int valeur;
};

typedef struct noeud arbre;

arbre* generate(int n){
    arbre * a = calloc(1,sizeof(arbre));
    a->valeur = n;
    if(n){
        a->gauche = generate(n-1);
        a->droite = generate(n-1);
    }
    return a;
}

arbre * parfait(int n){
    if(n){
        arbre * a = malloc(sizeof(arbre));
        a->valeur = 1;
        a->gauche = parfait(n-1);
        a->droite = parfait(n-1);
        return a;
    }
    else
        return NULL;
}

void freetree(arbre * a){
    if(a){
        freetree(a->gauche);
        freetree(a->droite);
        free(a);
   }
}

void print_arbre(int niv,arbre *a){
    if(a){
        for(int i=niv;i--;)printf("|--");
        printf(":%d\n",a->valeur);
        print_arbre(niv+1,a->gauche);
        print_arbre(niv+1,a->droite);
    }
}

void print_prefixe(arbre*a){
    if(a){
        printf("%d",a->valeur);
        print_prefixe(a->gauche);
        print_prefixe(a->droite);
    }
}

void print_infixe(arbre*a){
    if(a){
        print_infixe(a->gauche);
        printf("%d",a->valeur);
        print_infixe(a->droite);
    }
}

void print_postfixe(arbre*a){
    if(a){
        print_postfixe(a->gauche);
        print_postfixe(a->droite);
        printf("%d",a->valeur);
    }
}

int hauteur(arbre *a){
    return a ? MAX(hauteur(a->gauche),hauteur(a->droite))+1 : -1;
}

int taille(arbre *a){
    return a ? taille(a->gauche)+taille(a->droite)+1 : 0;
}

void incr(arbre *a){
    if(a){
    (a->valeur)++;
    incr(a->gauche);
    incr(a->droite);
    }
}
int main(void){
    /*
       arbre * a = malloc(sizeof(arbre));
       a->valeur = 5;
       a->gauche = calloc(1,sizeof(arbre));
       a->droite = calloc(1,sizeof(arbre));
       a->gauche->valeur = 1;
       a->droite->valeur = 2;*/
    arbre * a = parfait(SIZE);
    incr(a);
    print_arbre(0,a);
    printf("\n%d\n",taille(a));
    freetree(a);
}


