#include <stdlib.h>
#include <assert.h>
#include <string.h>
struct array_t {
    int *elements;
    int nelements;
};
typedef struct array_t *array;

array array_alloc(int n)
{
    array p;
    p->elements=malloc(n*sizeof(int));
    p->nelements=n+1;
    return p;
}

int array_get(array t, int i){
    assert(i<t->nelements);
    return t->elements[i];
}

void array_set(array t, int i, int v){
    assert(i<t->nelements);
    t->elements[i]=v;
}

void array_free(array t){
    free(t->elements);
}

void array_append(array t, int v){
    int size=t->nelements;
    array nt=array_alloc(size+1);
    memcpy(nt->elements,t->elements,size);
    array_set(nt,size+1,v);
    t->elements=nt->elements;
    t->nelements=nt->nelements;
    free(nt);
}

int main(void){}
