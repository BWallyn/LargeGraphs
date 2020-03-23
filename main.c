#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>

#include "structs/adjarray.c"
#include "structs/argparse.c"
#include "structs/sort.c"
#include "structs/stats.c"
#include "structs/min_heap.c"
#include "structs/fifo.c"
#include "structs/qsort_r.c"

#include "tp1/clusters.c"
#include "tp1/triangles.c"
#include "tp1/diameters.c"

#include "tp2/kcore.c"
#include "tp2/pagerank.c"

#include "tp3/label_propagation.c"
#include "tp3/gen_graph.c"
#include "tp3/louvain.c"
#include "tp3/louvain_partition.c"

int main(int argc,char** argv){

	//---------- CHARGEMENT DES OPTIONS
	OPTIONS options;
	load_options(&options, argc, argv);

	adjlist* g;
	time_t t1,t2;

	//---------- CHARGEMENT GRAPHE
	printf("\nDEBUT Lecture graphe\n");
	t1=time(NULL);

	printf("\tLecture du fichier %s\n",options.inputFile);
	g=readedgelist(options.inputFile);

	printf("\tNombre de sommets: %lu\n",g->n);
	printf("\tNombre d'aretes: %lu\n",g->e);

	printf("\tConstruction de la liste d'adjacence ...\n");
	mkadjlist(g);

	t2=time(NULL);
	printf("FIN Lecture graphe en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));


	STATS s;
	initSTATS(&s);
	//====================== PROJET 1 ======================

	if (options.project == 1){
		printf("\nDEBUT Calcul des clusters\n");
		t1 = time(NULL);
		findClusters(g, &s);
		t2 = time(NULL);
		printf("FIN Calcul des clusters en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

		printf("\nDEBUT Calcul du diametre\n");
		t1 = time(NULL);
		findDiameter(g, &s);
		t2 = time(NULL);
		printf("FIN Calcul du diametre en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

		printf("\nDEBUT Calcul des triangles\n");
		t1 = time(NULL);
		findTriangles(g, &s);
		t2 = time(NULL);
		printf("FIN Calcul des triangles en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	}

	//====================== PROJET 2 ======================
	if (options.project == 2){
		//printf("\nDEBUT Lecture nom pages\n");
		//printf("%s\n", getName(options.dicFile, 13832572));
		//printf("\nFIN Lecture nom pages\n");

		printf("\nDEBUT K core decomposition\n");
		t1 = time(NULL);
		computeKCore(g, &s, options.resultKCoreFile);
		t2 = time(NULL);
		printf("FIN K core decomposition en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

		printf("\nDEBUT Page Rank\n");
		t1 = time(NULL);
		computePageRank(g, &s, options.alpha, 30, options.resultPkFile);
		t2 = time(NULL);
		printf("FIN Page Rank en %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	}

	//====================== PROJET 3 ======================
	if (options.project == 3){
		unsigned long n_nodes=400;
		char* input="instances/generated/graph_1.txt";
		struct timeval stop, start;

		printf("\nBEGIN Generate graph\n");
		gettimeofday(&start, NULL);
		generate_graph(n_nodes, p, q, input);
		gettimeofday(&stop, NULL);
		printf("END Generate graph in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

		printf("\nBEGIN Label propagation\n");
		gettimeofday(&start, NULL);
		computeLabelPropagation(g, &s);
		gettimeofday(&stop, NULL);
		printf("END Label propagation in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

		// Louvain method for community detection in graphs
		printf("\nBEGIN Louvain method\n");
		gettimeofday(&start, NULL);
		louvain_method(g, &s);
		gettimeofday(&stop, NULL);
		printf("END Louvain method in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	}

	//------------ Afficchage statistiques
	showSTATS(&s, &options);

	//------------ LIBERATION GRAPHE
	free_adjlist(g);

	return 0;
}