
struct maillon {
    struct maillon * next;
    char * key;
    int value;
}; 
typedef struct maillon maillon;


maillon * create(){
    maillon * m = malloc(sizeof(maillon));
    m->key = malloc(sizeof(char));
    m->next = NULL;
    return m;
}

maillon * add(maillon * current,char * key,int value){
    maillon * n = create();
    n->next = current;
    n->key = malloc(sizeof(char)*CODELENGTH);
    strcpy(n->key,key);
    n->value = value;
    return n;
}

int find(maillon * l, char * key){
    if(strcmp(l->key,key)==0)
        return l->value;
    if(l->next==0)
        return -1;
    return find(l->next,key);
}


