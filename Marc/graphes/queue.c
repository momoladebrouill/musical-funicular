#define MAXV 10
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
struct queue {
    int elts[MAXV];
    int front;
    int back;
};
typedef struct queue queue;

struct stack {
    int elts[MAXV];
    int back;
};
typedef struct stack stack;

void init_stack(stack *s){
    s -> back = -1;
}
int pop(stack *s){
    return s->elts[s->back--];
}
void push(stack *s, int x){
    s->elts[++(s->back)] = x;
}
bool empty_s(stack *s){
	return s->back==-1;
}

void init_queue(queue *s){
    s->back = 0;
    s->front = -1;
}

int dequeue(queue *s)
{
    int v = s->elts[s->back];
    s->back = (s->back+MAXV+1)%MAXV;
    return v;
}

void enqueue(queue *s, int x)
{
    s->front = (s->front+1)%MAXV;
    s->elts[s->front] = x;
}
bool empty_q(queue *s){
	return (s->back - s->front+MAXV-1)%MAXV==0;
}
/*
int main(void){
	queue * s = malloc(sizeof(queue));
	init_queue(s);
	for(int i=0;i<MAXV/2;i++){enqueue(s,i);printf("enquue %d.\n",i);}
	printf("elements : ");
	for(int i=0;i<MAXV/2;i++)printf("%d ",s->elts[i]);
	printf("\ndeque : ");
	for(int i=0;!empty_q(s);i++)printf("%d ",dequeue(s));
	printf("\n");
}*/
