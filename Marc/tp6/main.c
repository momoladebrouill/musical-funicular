#include <stdio.h>
#include <stdlib.h>

struct maillon {
    int valeur;
    struct maillon *suivant;
};
typedef struct maillon maillon;

struct liste {
    maillon *premier;
    maillon *dernier;
};
typedef struct liste liste;

liste *liste_creer(maillon *premier, maillon *dernier){
  liste * l = malloc(sizeof(liste));
  l->premier = premier;
  l->dernier = dernier;
  return l;
}

liste *liste_vide(){return liste_creer(NULL,NULL);}

void liste_affiche(liste *l){
    putchar('[');
    for(maillon * p = l ->premier;p!=NULL;p=p->suivant){
        printf("%i",p->valeur);
        if(p->suivant)putchar(',');
    }
    putchar(']');
    putchar('\n');
}

maillon *maillon_creer(int valeur, maillon *suivant){
    maillon * m = malloc(sizeof(maillon));
    m->valeur = valeur;
    m->suivant = suivant;
    return m;
}

void maillon_detruire(maillon *m){free(m);}

void chaine_detruire(maillon *m){
    maillon * n;
    if(m->suivant==NULL){
        free(m);
    }else{
        while((n = m->suivant)!=NULL){
            maillon_detruire(m);
            m = n;
        }
    }
}

void liste_detruire(liste *l){
    if(l->premier)
      chaine_detruire(l->premier);
    free(l);
}

int liste_longueur(liste *l){
    int len=0;
    for(maillon * p = l ->premier;p!=NULL;p=p->suivant)len++;
    return len;
}

int liste_tete(liste *l){return l->premier->valeur;}

liste *liste_queue(liste *l){
    return liste_creer(l->premier->suivant,l->dernier);
}

void liste_ajout_en_tete(liste *l, int valeur){
    l->premier = maillon_creer(valeur,l->premier);
    if(l->dernier==NULL)l->dernier=l->premier;
}

void liste_suppr_en_tete(liste *l){
    maillon * oldH = l->premier;
    if(l->premier->suivant)
        l->premier = l->premier->suivant;
    else
        l->dernier = l->premier;
    maillon_detruire(oldH);
}

void liste_ajout_en_fin(liste *l, int valeur){
    maillon * n =  maillon_creer(valeur,NULL);
    if(l->dernier==NULL)
        l->dernier=n;
    else{
        l->dernier->suivant = n;
        l->dernier = n;
    }
}

maillon *liste_cherche_maillon(liste *l, int valeur){ 
    for(maillon * p = l ->premier;p!=NULL;p=p->suivant)
        if(p->valeur==valeur)
            return p;
    return NULL;
}

void liste_ajout_maillon_apres(liste *l, maillon *m, int valeur){
  
}

int main(void)
{
    liste *l = liste_vide();
    liste_affiche(l);
    liste_ajout_en_tete(l, 3);
    liste_ajout_en_tete(l, 2);
    liste_ajout_en_tete(l, 1);
    liste_affiche(l);
    liste_ajout_en_fin(l, 5);
    liste_affiche(l);
/*    maillon *m = liste_cherche_maillon(l, 3);
    liste_ajout_maillon_apres(l, m, 4);
    liste_affiche(l);
    liste_suppr_maillon(l, m);
    liste_affiche(l);*/
    liste_detruire(l);
    return 0;
}
