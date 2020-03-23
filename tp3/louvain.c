#ifndef LOUVAIN
#define LOUVAIN

#include "louvain_partition.h"

//reading the list of edges and building the adjacency array
//NOT USED IN THE CURRENT VERSION
#define BUFFER_SIZE (16 * 1024)

int
read_two_integers(int fd, unsigned long *u, unsigned long *v) {
  static char buf[BUFFER_SIZE];
  static ssize_t how_many = 0;
  static int pos = 0;
  unsigned long node_number=0;
  int readu = 0;

  while (1) {
    while(pos < how_many) {
      if (buf[pos] == ' ') {
	*u = node_number;
	readu=1;
	node_number = 0;
	pos++;
      } else if (buf[pos] == '\n') {
	*v = node_number;
	node_number = 0;
	readu=0;
	pos++;
	return 2;
      } else {
	node_number = node_number * 10 + buf[pos] - '0';
	pos++;
      }
    }

    how_many = read (fd, buf, BUFFER_SIZE);
    pos = 0;
    if (how_many == 0) {
      if(readu==1) {
	*v = node_number;
	return 2;
      }	    
      return 0;;
    }
  } 
}

void louvain_method(adjlist *g, STATS *s){
    unsigned long *labels;
    unsigned long i;

    labels = malloc(g->n * sizeof(unsigned long));
    louvainComplete(g, labels);

    // Number of communities
    mergeSort(labels, 0, g->n-1);
    s->louvain_nb_communities = 1;
    for (i=0; i<g->n-1; ++i){
        //printf("%lu ", labels[i]);
        if (labels[i]<labels[i+1]){
            ++ s->louvain_nb_communities;
        }
    }
}

/*int main(int argc,char** argv){
  adjlist* g;
  unsigned long *part;
  unsigned long i;

  time_t t0 = time(NULL), t1, t2, t3;
  srand(time(NULL));

  printf("Reading edgelist from file %s and building adjacency array\n", argv[1]);
  g = readadjlist(argv[1]);
  printf("Number of nodes: %lu\n", g->n);
  printf("Number of edges: %llu\n", g->e);

  t1 = time(NULL);
  printf("- Time to load the graph = %ldh%ldm%lds\n", (t1-t0)/3600, ((t1-t0)%3600)/60, ((t1-t0)%60));

  printf("Starting louvain\n");
  part = malloc(g->n * sizeof(unsigned long));
  louvainComplete(g, part);
  t2 = time(NULL);
  printf("- Time to compute communities = %ldh%ldm%lds\n", (t2-t1)/3600, ((t2-t1)%3600)/60, ((t2-t1)%60));
  
  printf("Prints result in file %s\n", argv[2]);
  FILE* out = fopen(argv[2], "w");
  for(i = 0; i < g->n; i++){
    fprintf(out, "%lu %lu\n", i, part[i]);
  }
  fclose(out);
  t3 = time(NULL);
  printf("- Time to export communities = %ldh%ldm%lds\n", (t3-t2)/3600, ((t3-t2)%3600)/60, ((t3-t2)%60));

  printf("- Overall time = %ldh%ldm%lds\n", (t3-t0)/3600, ((t3-t0)%3600)/60, ((t3-t0)%60));

  return 0;
}
*/

#endif