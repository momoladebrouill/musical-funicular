/* DS de l'an dernier
On considère un ensemble avec des entiers
Le tableau stock si l'entier naturel est dans le tableau */

#include <stdio.h>
#include <stlib.h>

int t[]={0,1,0,1,0,1};

int is_in(int x){
  return t[x];
}

int sum(int from,int to){
  int s=0;
  for(int i=from;i<=to;i++)
    s+=t[i]*i;
  return s;
}

int qqty(int from,int to){
  int s=0;
  for(int i=from;i<=to;i++)
    s+=t[i];
  return s;
}

void complementaire(int *e,int *ce){
  for(int i=0;i<n;i++)ce[i]=!e[i];
}

int main(){
  printf("sum : %i\n",sum(0,5));
}
