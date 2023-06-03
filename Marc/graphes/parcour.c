#define MAXV 100 /* nombre maximum de sommets */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define TREE 0
#define BACK 1
#define FORWARD 2
#define CROSS 3

struct edgenode {
	int y; // le voisin
	struct edgenode *next; // la suite de la liste
};
typedef struct edgenode edgenode;

struct graph {
	edgenode* edges[MAXV]; // tableau de listes d'adjacence
	int degree[MAXV]; // le degré de chaque sommet
	int nvertices;
	int nedges;
	bool directed; // indique si le graphe est orienté
	bool discovered[MAXV]; // Quels sommets sont connus
	bool processed[MAXV]; // Quels sommets sont traités
	int parent[MAXV]; // parent[x] est le père de x dans le parcours
			  // s'il n'y en a pas, c'est -1
	int time; // l'horloge
int entry_time[MAXV];
int exit_time[MAXV];
};
typedef struct graph graph;

void initialize_graph(graph *g, bool directed){
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	for(int i=0;i<MAXV;i++){
		g->edges[i] = NULL;
		g->degree[i] = 0;
	}
}

void insert_edge(graph *g, int x, int y, bool directed){
	edgenode * n = malloc(sizeof(edgenode));
	n->y = y;
	n->next = g->edges[x];
	g->edges[x] = n;
	g->degree[x]++;
	if(directed)
		g->nvertices++;
	else
		insert_edge(g,y,x,true);
}

void read_graph(graph *g){
	int n,p,o,x,y;
	scanf("%d %d %d",&n,&p,&o);
	initialize_graph(g,o);
	for(int i=0; i<p; i++){
		scanf("%d %d",&x,&y);
		insert_edge(g,x,y,g->directed);
	}
}

void free_edges(graph *g){
	edgenode *s;
	edgenode *n;
	for(int x = 0; x < MAXV;x++){
		s = g->edges[x];
		while(s){
			n = s->next;
			free(s);
			s = n;
		}
	}
}

void initialize_search(graph *g){
	for(int x=0;x<MAXV;x++){
		g->discovered[x] = g->processed[x] = false;
		g->parent[x] = -1;
		g->entry_time[x] = g->exit_time[x] = 0;
	}
	g->time = 0;
}

void print_graph(graph * g){
	printf("Edges %d Vertices %d\n",g->nedges,g->nvertices);
	edgenode *s;
	for(int i=0;i<MAXV;i++){
		if(g->edges[i]){
			printf("%d : ",i);
			s = g->edges[i];
			while(s){
				printf("%d ",s->y);
				s = s ->next;
			}
			printf("\n");
		}
	}
}

void process_vertex_early(graph *g, int v){printf("processing vertex %d\n", v);}
void process_vertex_late(graph *g, int v){}
void process_edge(graph *g, int x, int y){printf("processed edge %d --> %d\n", x, y);}

void dfs(graph *g, int x){
	process_vertex_early(g,x);
	edgenode * s = g->edges[x];
	g->discovered[x] = true;
	g->time++;
	g->entry_time[x] = g->time;
	while(s){
		if(!(g->discovered[s->y])){
			process_edge(g,x,s->y);
			dfs(g,s->y);
		}
		s = s->next;
	}
	g->exit_time[x] = g->time;
	process_vertex_late(g,x);
	g->processed[x] = true;
}

void connected_components(graph *g);

int edge_classification(graph *g, int x, int y){
	int 
		prex = g->entry_time[x],
		postx = g->entry_time[x],
		prey = g->entry_time[y],
		posty = g->entry_time[y];
	if(prex<prey && posty<postx){
		if(prex + 1 == prey) return TREE;
		else return BACK;
	}
	if(edge_classification(g,y,x) == TREE || edge_classification(g,y,x) == BACK) return FORWARD;
	else return CROSS;
}

int main(void){
	graph * g = malloc(sizeof(graph));
	read_graph(g);
	print_graph(g);
	initialize_search(g);
	dfs(g,0);
	free_edges(g);
	return 0;
}
