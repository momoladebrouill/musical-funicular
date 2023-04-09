#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef unsigned int T;

uint64_t pow2(uint64_t p)
{
    uint64_t one = 1;
    return one << p;
}

uint64_t hash(uint64_t x, char p)
{
    uint64_t one = 1;
    uint64_t mask = (one << p) - one;
    uint64_t modulo = x & mask;
    return modulo;
}

char EMPTY = 0;
char OCCUPIED = 1;
char TOMBSTONE = 2;

struct bucket {
    char status;
    T element;
};
typedef struct bucket bucket;

struct set {
    char p;
    bucket *a;
    uint64_t nb_empty;
};
typedef struct set set;

set *set_new(void)
{
    set * s = malloc(sizeof(set));
    s->p=1;
    s->a = malloc(pow2(s->p)*sizeof(bucket));
    s->nb_empty = pow2(s->p);
    s->a[0].status = EMPTY;
    s->a[1].status = EMPTY;
    return s;
}

set *set_example(void)
{
    set * s = set_new();
    s->p = 2;
    s->a = malloc(pow2(s->p)*sizeof(bucket));
    s->nb_empty = 1;
    s->a[0].status = OCCUPIED;
    s->a[0].element = 1492;
    s->a[1].status = OCCUPIED;
    s->a[1].element = 1939;
    s->a[2].status = EMPTY;
    s->a[3].status = OCCUPIED;
    s->a[3].element = 1515;
    return s;

}

void set_delete(set *s)
{
    free(s->a);
    free(s);
}


uint64_t set_search(set *s, T x, bool *found)
{
    T depart = hash(x,s->p);
    T i = depart;
    for(;;){
        if(s->a[i].status == EMPTY){
            *found=false;
            break;
        }
        if(s->a[i].element == x && s->a[i].status == OCCUPIED){
            *found=true;
            break;
        }
        i++;
        i = i % pow2(s->p);
    }
    return i;
}


bool set_is_member(set *s, T x)
{
    bool found;
    set_search(s,x,&found);
    return found;
}
void set_resize(set *s, int p)
{
    bucket *a = malloc(pow2(p)*sizeof(bucket));
    for(int i=0;i<pow2(s->p);i++){
        if(s->a[i].status==OCCUPIED)
            a[hash(a[i].element,pow2(p))].element = a[i].element;
            a->status=OCCUPIED;
    }
    s->a = a;
    s->p = p;
    s->nb_empty+=pow2(p);
}

void set_add(set *s, T x)
{
    if(s->nb_empty - 1 < pow2(s->p)/3)
      set_resize(s,s->p+1);
    bool found;
    T to_go = set_search(s,x,&found);
    if(!found){
        s->a[to_go].status=OCCUPIED;
        s->a[to_go].element=x;
    }

}

void set_remove(set *s, T x)
{
    bool found;
    T where = set_search(s,x,&found);
    if(found)
        s->a[where].status=TOMBSTONE;

}

T *read_data(const char *filename, int *n, int *error)
{
    FILE *fp = fopen(filename, "r");
    if(ferror(fp))
    {
        *error = 1;
        return NULL;
    }
    // on parcours le fichier une première fois->pour obtenir
    // le nombre d'adresses.
    *n = 0;
    while(!feof(fp))
    {
        int a1, a2, a3, a4;
        if(fscanf(fp, "%d.%d.%d.%d\n", &a1, &a2, &a3, &a4) == EOF)
        {
            // erreur de fichier
            *error = 1;
            return NULL;
        }
        (*n)++;
    }

    T *t = malloc(sizeof(T) * (*n));
    // on retourne au début du fichier
    rewind(fp);
    int i = 0;
    for(int i = 0; i < *n; i++)
    {
        int a1, a2, a3, a4;
        fscanf(fp, "%d.%d.%d.%d\n", &a1, &a2, &a3, &a4);
        t[i] = (a1 << 24) + (a2 << 16) + (a3 << 8) + a4;
    }
    *error = 0;
    return t;
}


void set_skip_stats(set *s, double *average, uint64_t *max)
{
}

int main(void){
    printf("%lu\n",pow2(89788));
    set * e = set_example();
    printf("1492 : %b\n",set_is_member(e,1492));
    set_add(e,1493);
    set_remove(e,1493);
    printf("1493 : %b\n",set_is_member(e,1493));
    set_delete(e);
    set * 
    return 0;
}
