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

void init_stack(stack *s)
{
    s -> back = -1;
}

int pop(stack *s)
{
    return s->elts[s->back--];
}

void push(stack *s, int x)
{
    s->elts[++s->back] = x;
}

void init_queue(queue *s)
{
    // initialise la file
}

int dequeue(queue *s)
{
    // defile un élément
}

void enqueue(queue *s, int x)
{
    // enfile x sur la file s
}
