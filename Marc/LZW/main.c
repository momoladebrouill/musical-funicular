#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TAILLE_ALPHABET 128
#define BITS_IN_BYTES 8

bool fgetb(FILE *f,int *g,int*d){
    (*g)++;
    if(*g == BITS_IN_BYTES+1){
        *g = 1;
        *d = fgetc(f);
        if(*d == EOF)printf("WARNING : you've reached the end of the file! :(");
    }
    return (*d) & (1<<(BITS_IN_BYTES - (*g)));
}

bool fputb(FILE *f,bool val,int *g,int *d){
    if(val) *d |= (1<<(*g));
    (*g)--;
    if(*g == -1){
        *g = BITS_IN_BYTES;
        fputc(*d,f);
        *d = 0;
    }
}


int input_code(FILE *f,int l){
    int c = 0;
    int g = 0;
    int d = fgetc(f);
    for(int i=0;i<l && d!=EOF ;i++){
        bool b = fgetb(f,&g,&d);
        if(b)
            c+=1<<i;
    }
    return c;
}

void output_code(FILE *f, int code, int l){
    if(!(code < (1<<l))){
            printf("Vous cherchez à insérer un code plus long que la longueur max AIE !!!");
            return ;
    }
    int c = code;
    int g = BITS_IN_BYTES-1;
    int d = 0;
    for(int i=0;i<l;i++){
        fputb(f,c & 1,&g,&d);
        c = c/2;
    }
    fputc(d,f);
    fputc(EOF,f);
}

int main(void){
    FILE * f,*g;
    f = fopen("test","rb");
    g = fopen("tested","wb");
    for(int i=0;i<16;i++)
    output_code(g,input_code(f,8),8);
    printf("\n");
    fclose(g);
    fclose(f);
    return 0;
}
