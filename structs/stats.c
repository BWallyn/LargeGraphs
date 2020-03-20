#ifndef STATS_F
#define STATS_F

#include "stats.h"

void initSTATS(STATS* s){
	s->diameter = 0;
	s->entry_max_size_cluster = 0;
	s->max_size_cluster = 0;
	s->ratio_max_size_cluster = 0;
	s->nb_triangles = 0;
	
	s->five_most_popular_pages = calloc(5,sizeof(unsigned long));
	s->five_last_popular_pages = calloc(5,sizeof(unsigned long));

	s->k_core_value = 0;

	s->nb_communities = 0;
}

void showSTATS(STATS* s, OPTIONS* options){
	printf("\n----------- STATISTIQUES ------------\n");

	if (options->project == 1){
		printf("Taille plus grand cluster: %d\n", s->max_size_cluster);
		printf("Ratio plus grand cluster: %.5f\n", s->ratio_max_size_cluster);
		printf("Plus grand diametre trouve: %d\n", s->diameter);
		printf("Nombre de triangles: %d\n", s->nb_triangles);
	}

	if (options->project == 2){
		int p;
		for (p=0; p<5; ++p){
			printf("Page la plus vue n%d:\t%lu\n", p+1, s->five_most_popular_pages[p]);
		}
		printf("\n");
		for (p=4; p>=0; --p){
			printf("Page la moins vue n%d:\t%lu\n", p+1, s->five_last_popular_pages[p]);
		}

		printf("\nk-core value du graph : %d\n", s->k_core_value);

	}

	if (options->project == 3){
		printf("Nombre de communautes: %d\n", s->nb_communities);
	}
	
	printf("-------------------------------------\n");
}

#endif