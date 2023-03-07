#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NB 20
#define somme(n) n*(n+1)*(2*n+1)/6
#define arg_max(t,s) recherche(t,max(t,s),s)

int syrac(int n){
    return n%2 ? 3*n + 1 : n/2;
}

int syracuse(int a,int n){
    int r=a;
    for(int i=n;i--;){
        r=syrac(r);
    }
    return r;
}

int temps_de_vol(int a){
    int i=0;
    while(syracuse(a,i)-1)i++;
    return i;
}

int altitude_maximale(int a){
    int max;
    int u=a;
    max=a;
    for(int i=temps_de_vol(a)+3;i--;){
        u=syrac(u);
        max= u>max ? u:max;
    }
    return max;
}

int recherche(int t[],size_t taille,int elem){
    int i;
    for(i=0; i<taille && t[i]^elem; i++);
    return i==taille ? -1 : i;
}

int max(int t[],size_t size){
    int max=0;
    for(int i=size;i;i--){
        max=t[i]>max? t[i]:max;
    }
    return max;
}

int suplog2(int m){
    int n=0;
    int v=1;
    while (v<=m){
        n++;
        v*=2;
    }
    return n;
}

void plus_petite_distance(const int *t, int nb, int *i, int *j){
    int max=0;
    unsigned int v;
    for(int a=0;a<nb;a++){
        for(int b=a;b<nb;b++){
            v=(t[a]-t[b]);
            if(v>=max){
                *i=a;
                *j=b;
                max=v;
            }
        }
    }

};

int est_trie(int t[],size_t len){
    for(int i=1;i<len;i++){
        if(t[i-1]>t[i])
            return 0;
    }
    return 1;
}

int len(char * s){
    int i;
    for(i=0;s[i];i++);
    return i;
}

int main(){
    /*for(int i=NB;i--;){
      printf("%i %i\n",NB-i,syrac(NB-i));
      }*/
    int T[] ={1,2,3};
    printf("%i\n",syracuse(3,5));
    printf("%i,%i,%i\n",suplog2(0),suplog2(1),suplog2(15));
    printf("%i\n",temps_de_vol(14));
    printf("%i\n",altitude_maximale(2));
    printf("%i\n",somme(13));
    printf("%i\n",recherche(T,3,3));
    printf("%i\n",arg_max(T,3));
    int t[] = { 5, 2, 7, 10 };
    int i, j;
    printf("len de caca : %i\n",len("caca"));
    plus_petite_distance(t, 4, &i, &j);
    assert( i == 0 && j == 2 );
}



