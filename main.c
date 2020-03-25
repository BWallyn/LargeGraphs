#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
//#include <time.h>
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
	struct timeval stop, start;

	//---------- GENERATION GRAPH
	if (options.project == 3){
		printf("\nBEGIN Generate graph\n");
		if (options.benchmark == 'h'){
			double p=0.4;
			double q=0.01;
			char* input="instances\\graph_1.txt";
			unsigned long n_nodes=400;

			printf("\tOptions: p = %lf and q = %lf\n", p, q);
			gettimeofday(&start, NULL);
			generate_graph(n_nodes, p, q, input);
		}
	
		else if (options.benchmark == 'l') {
			// Génération d'un graph avec la routine LFR
			char cmdbuf[100];
			long int LFR_nb_nodes = 50000;
			char *LFR_file_name = "instances\\LFR_graph";
			printf("\tOptions LFR: N = %d\n", LFR_nb_nodes);
			snprintf(cmdbuf, sizeof(cmdbuf), "lfr.exe -N %d -name \"%s_%d\" -on 0 -k 6 -maxk 80 -muw 0 -minc 100 -maxc 100", 
												LFR_nb_nodes, LFR_file_name, LFR_nb_nodes);
			int retcode = system(cmdbuf);
			printf("\tCode de sortie LFR: %d\n", retcode);
		}

		gettimeofday(&stop, NULL);
		printf("END Generate graph in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	}

	//---------- CHARGEMENT GRAPHE
	printf("\nBEGIN Read graph\n");
	gettimeofday(&start, NULL);

	printf("\tRead file %s\n",options.inputFile);
	g=readedgelist(options.inputFile);

	printf("\tNumber of nodes: %lu\n",g->n);
	printf("\tNumber of edges: %lu\n",g->e);

	printf("\tBuilding the adjacency list ...\n");
	mkadjlist(g);

	gettimeofday(&stop, NULL);
	printf("END Read graph in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);


	STATS s;
	initSTATS(&s);
	//====================== PROJET 1 ======================

	if (options.project == 1){
		printf("\nBEGIN Compute clusters\n");
		gettimeofday(&start, NULL);
		findClusters(g, &s);
		gettimeofday(&stop, NULL);
		printf("END Compute clusters in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

		printf("\nBEGIN Compute diameter\n");
		gettimeofday(&start, NULL);
		findDiameter(g, &s);
		gettimeofday(&stop, NULL);
		printf("END Compute diameter in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

		printf("\nBEGIN Compute triangles\n");
		gettimeofday(&start, NULL);
		findTriangles(g, &s);
		gettimeofday(&stop, NULL);
		printf("END Compute triangles in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	}

	//====================== PROJET 2 ======================
	if (options.project == 2){
		//printf("\nDEBUT Lecture nom pages\n");
		//printf("%s\n", getName(options.dicFile, 13832572));
		//printf("\nFIN Lecture nom pages\n");

		printf("\nBEGIN K core decomposition\n");
		gettimeofday(&start, NULL);
		computeKCore(g, &s, options.resultKCoreFile);
		gettimeofday(&stop, NULL);
		printf("END K core decomposition in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

		printf("\nBEGIN Page Rank\n");
		gettimeofday(&start, NULL);
		computePageRank(g, &s, options.alpha, 30, options.resultPkFile);
		gettimeofday(&stop, NULL);
		printf("END Page Rank in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

	}

	//====================== PROJET 3 ======================
	if (options.project == 3){
		// Label propagation method for community detection in graphs
		printf("\nBEGIN Label propagation\n");
		gettimeofday(&start, NULL);
		computeLabelPropagation(g, &s, options.resultLabelFile);
		gettimeofday(&stop, NULL);
		printf("END Label propagation in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

		// Louvain method for community detection in graphs
		printf("\nBEGIN Louvain method\n");
		gettimeofday(&start, NULL);
		louvain_method(g, &s, options.resultLouvainFile);
		gettimeofday(&stop, NULL);
		printf("END Louvain method in %lu us\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	}

	//------------ Afficchage statistiques
	showSTATS(&s, &options);

	//------------ LIBERATION GRAPHE
	free_adjlist(g);

	return 0;
}