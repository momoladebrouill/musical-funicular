#include <stdio.h>

int cherche_minimum(int *t, int nb, int *indice){
    int min=t[0]; // on supposera t non vide
    (*indice)=0;
    for(int i=0;i<nb;i++){
        if(t[i]<min){
            (*indice)=i;
            min=t[i];
        }
   } 
    return min;
          

}

int main(void){
    int t[] = { 1, 3, 0, 2, 4 };
    int indice;
    int min = cherche_minimum(t, 5, &indice); // on passe un pointeur sur indice
    printf("Le minimum est %d et il est à l'indice %d\n", min, indice);
}
