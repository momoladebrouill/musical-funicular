#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE_ALPHABET 256

int cherche_motif(char *m,char *s, int i){
    int p = strlen(m);
    for(int j=0;j<p;j++){
        if(s[i+j] != m[j])
            return false;
    }
    return true;
}

int recherche_naive(char *m,char*s){
    int n = strlen(s);
    int p = strlen(m);
    for(int i=0;i < n-p+1;i++){
        if(cherche_motif(m,s,i))
            return i;
    }
    return -1;
}

int * calcule_droite(char *m){
    int * droite = malloc(TAILLE_ALPHABET * sizeof(int));
    for(int i = 0 ; i < TAILLE_ALPHABET;i++) droite[i] = -1;
    int p = strlen(m);
    for(int i=0; i < p-2;i++){
        int j = p-2-i;
        char c = m[j];
        if(droite[c] == -1) droite[c] = j;
    }
    return droite;
}

int recherche_BMH(char * m, char * s){
    int n = strlen(s);
    int p = strlen(m);
    int i = 0;
    int * droite = calcule_droite(m);
    while(i <= n-p){
        bool present = true;
        for(int j = p-1; j >= 0; j--){
            if(s[i+j] != m[j]){
                present = false;
                int dec = 1;
                int k = droite[s[i+j]];
                
                if(k == -1)
                    dec = j+1;
                else if(k<j)
                    dec = j-k;
                
                i += dec;
                break;
            }
        }
        if(present) 
            return i;
    }
    return -1;
}

int main(void){
    char *m = "aba";
    char *s = "cabcaaaba";
    printf("On cherche \"%s\" dans \"%s\"...\n",m,s);
    int ind  = recherche_BMH(m,s);
    if(ind == -1){
        printf("Not found\n");
        return 0;
    }
    int j=0,i=0;
    for(;i<ind;i++)printf("%c",s[i]);
    printf("\x1b[33m");
    for(j = 0;j<strlen(m) && j+i < strlen(s);j++)printf("%c",s[j+i]);
    printf("\x1b[0m");
    for(i=i+j;i<strlen(s);i++)printf("%c",s[i]);
    printf("\n");

    return 0;
}
