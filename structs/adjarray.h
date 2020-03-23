#ifndef ADJARRAY_DEF
#define ADJARRAY_DEF

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

//edge list structure:
typedef struct {
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	edge *edges;//list of edges
	unsigned long *cd;//cumulative degree cd[0]=0 length=n+1
	unsigned long *adj;//concatenated lists of neighbors of all nodes
	unsigned long *outD;
	long double *weights;
    long double totalWeight;
    unsigned long *map;
} adjlist;

inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c);
adjlist* readedgelist(char* input);
void mkadjlist(adjlist* g);
void free_adjlist(adjlist *g);

#endif