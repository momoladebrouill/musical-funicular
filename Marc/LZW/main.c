#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// le nombre de bits dans un byte
#define BITS_IN_BYTES 8
// la taille maximale des schemas qui reviennent souvent
#define CODELENGTH 2
#define taille_table 256+(1<<CODELENGTH)
#include "hastable.c"
#include "fileop.c"

typedef struct table_bidir {
    maillon * indices;
    int n_elements;
    char **elements;
}table_dir;

table_dir * cree_table(){
    table_dir * t = malloc(sizeof(table_dir));
    t->n_elements = 256;
    t->indices = create();
    t->elements = malloc(sizeof(char*)*(taille_table));
    char s[] = "r";
    for(int i=0;i<256;i++){
        s[0] = i;
        t->elements[i] = malloc(sizeof(char)*2);
        strcpy(t->elements[i],s);
        t->indices = add(t->indices,s,i);
    }
    return t;
}

void ajoute_entree(table_dir * t,char * s){
    if(t->n_elements > taille_table){
        printf("je n'ai plus de place !!\n");
        return ;
    }
    printf("->on ajoute l'element %s\n",s);
    t->elements[t->n_elements] = malloc(sizeof(char)*CODELENGTH);
    strcpy(t->elements[t->n_elements],s);
    t->indices = add(t->indices,s,t->n_elements);
    t->n_elements++;
}

char * concat_s_c(char *s,char c,int l){
    char * o = malloc(sizeof(char)*(l+2));
    strcpy(o,s);
    o[l] = c;
    o[l+1] = 0;
    return o;
}

void compress_file(FILE * f_in,FILE * f_out){
    table_dir * t = cree_table();
    
    int msize = 1;
    char *m = concat_s_c("",fgetc(f_in),0);
    char c;
    
    while( (c = fgetc(f_in)) != EOF){
        char * mc = concat_s_c(m,c,msize);
        int found = find(t->indices,mc);
        if(found == -1){ //not found
            int i = find(t->indices,m);
            output_code(f_out,i);
            ajoute_entree(t,mc);
            m = concat_s_c("",c,0);
            msize = 1;
        }else{
            printf("on a trouve mc : '%s'\n",mc);
            m = mc;
            msize++;
        }
    }

    int i = find(t->indices,m);
    printf("nombre d'elements : %d \n",t->n_elements);
    output_code(f_out,i);
}



void decompress_file(FILE * f_in,FILE * f_out){
    table_dir * t = cree_table();
    int code = input_code(f_in); 
    fputs(t->elements[code],f_out);
    int  nouveau;
    while( (nouveau = input_code(f_in)) ){
        char *s_code = t->elements[code];
        char *s;
        if(nouveau == t->n_elements){
            s = concat_s_c(s_code,s_code[0],CODELENGTH);
        }else{
            s = malloc(sizeof(char)*CODELENGTH);
            strcpy(s,t->elements[nouveau]);
        }
        fputs(s,f_out);
        if(t->n_elements<taille_table)
            ajoute_entree(t,concat_s_c(s_code,s_code[0],CODELENGTH));
        code = nouveau;
    }
}

int main(void){
    FILE * f,*g,*h;
    f = fopen("test","rb");
    g = fopen("test.zipped","wb");
    h = fopen("test.unzipped","wb");
    
    compress_file(f,g);
    decompress_file(g,h);
    
    fclose(g);
    fclose(f);
    fclose(h);
    return 0;
}
