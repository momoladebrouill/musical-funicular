#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/*
 * t : tableau d'entiers
 * nb : nombre d'éléments du tableau
 *
 * i, j : valeurs de retours passées par pointeurs
 *
 * Renvoie dans (i,j) le couple tel |t[i]-t[j]| minimal
 * et i < j. En cas de plusieurs couples valides, renvoie le couple
 * dont la première coordonnées est minimale.
 */

void plus_petite_distance(int *t, int nb, int *i, int *j)
{
    (*i)=0;
    (*j)=1;
    int ci,cj;
    cj=1;
    while(cj<nb){
        ci=0;
        while(ci<cj){
            if(abs(t[ci]-t[cj])<abs(t[*i]-t[*j])){
                (*i)=ci;
                (*j)=cj;
            
            }
            ci++;
        }
        cj++;
    }
}

int main(void){
    // Exemple de test
    int t[] = { 5, 2, 7, 10 };
    int i, j;
    plus_petite_distance(t, 4, &i, &j);
    assert( i == 0 && j == 2 );
}
