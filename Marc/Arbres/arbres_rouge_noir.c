#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX(X,Y) X>Y ? X:Y 
#define SIZE 3

struct noeud {
    struct noeud * gauche;
    struct noeud * droite;
    bool rouge;
    int valeur;
};

typedef struct noeud arbre;

arbre* generate(int n){
    arbre * a = calloc(1,sizeof(arbre));
    a->valeur = n;
    a->rouge = true;
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
        a->rouge = 1;
        a->gauche = parfait(n-1);
        a->droite = parfait(n-1);
        return a;
    }
    else
        return NULL;
}

arbre * cree_feuille(int x){
    arbre * r = parfait(1);
    r->valeur =x;
    return r;
}

arbre * rotation_droite(arbre *x) {
    arbre * r = malloc(sizeof(arbre));
    r -> rouge = x -> rouge; 
    r -> valeur = x -> gauche -> valeur;
    r -> gauche = x -> gauche -> gauche;
    r -> droite = malloc(sizeof(arbre));

    arbre * y = r->droite;
    y -> rouge = true;
    y -> valeur = x -> valeur;
    y -> droite = x -> droite;
    y -> gauche = x -> gauche -> droite;
    free(x->gauche);
    free(x);
    return r;
}

arbre * rotation_gauche(arbre* a) {
    arbre * r = malloc(sizeof(arbre));
    r -> rouge = a -> rouge; 
    r -> valeur = a -> droite -> valeur;
    r -> droite = a -> droite -> droite;
    r -> gauche = malloc(sizeof(arbre));

    arbre * y = r->gauche;
    y -> rouge = true;
    y -> valeur = a -> valeur;
    y -> droite = a -> droite -> gauche;
    y -> gauche = a -> gauche;
    free(a->droite);
    free(a);
    return r;
}

arbre * bascule(arbre* a) {
    arbre * r = malloc(sizeof(arbre));
    r -> gauche = malloc(sizeof(arbre));
    r -> droite = malloc(sizeof(arbre));
    memcpy(r,a,sizeof(arbre));
    memcpy(r->droite,a->droite,sizeof(arbre));
    memcpy(r->gauche,a->gauche,sizeof(arbre));
    r->rouge=true;
    r->droite->rouge=r->gauche->rouge=false;
    return r;
}

bool rouge(arbre *a){
    return a ? a->rouge : false;
}
bool noir(arbre *a){
    return !rouge( a);
}

arbre * essai_rotdroite(arbre *a){
    if(a)
        if(rouge(a->gauche) && noir(a->droite))
            return rotation_droite(a);
    return a;
}

arbre * essai_rotgauche(arbre* a){
    if(a)
        if(noir(a) && rouge(a->droite))
            if(a->droite->droite)
                if(rouge(a->droite->droite))
                    return rotation_gauche(a);
    return a;
}

arbre * essai_bascule(arbre* a){
    if(a)
        if(noir(a) && rouge(a->gauche) && rouge(a->droite))
            return bascule(a);
    return a;
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
        for(int i=niv;i--;)printf("- ");
        printf("%s%d\033[0m\n", a->rouge ?  "\033[1;31m" : "",a->valeur);
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

arbre * insere_aux(arbre *a,int x){
    if(a){
        arbre * b = malloc(sizeof(arbre));
        b -> rouge = a->rouge;
        b -> valeur = a->valeur;
        if(x < a->valeur){
            b -> gauche = insere_aux(a->gauche,x);
            b -> droite = a->droite;
        }else{
            b -> gauche = a->gauche;
            b -> droite = insere_aux(a->droite,x);
        }
        return essai_bascule(essai_rotgauche(essai_rotdroite(b)));
    }
    return cree_feuille(x);
}

arbre * insere(arbre *a, int x){
    arbre * r = insere_aux(a,x);
    r->rouge = false;
    return r;
}


int main(void){
    /*
       arbre * a = malloc(sizeof(arbre));
       a->valeur = 5;
       a->gauche = calloc(1,sizeof(arbre));
       a->droite = calloc(1,sizeof(arbre));
       a->gauche->valeur = 1;
       a->droite->valeur = 2;*/
    arbre * a = generate(SIZE);
    incr(a);
    print_arbre(0,a);
    printf("\n%d\n",taille(a));
    freetree(a);
    a = NULL;
    for(int i=0;i<10;i++){
        a = insere(a,i);
        print_arbre(0,a);
    }

}


