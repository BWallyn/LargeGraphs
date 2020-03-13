typedef struct 
{
	// tp1
	unsigned long diameter;
	unsigned long entry_max_size_cluster;
	unsigned long max_size_cluster;
	double ratio_max_size_cluster;
	unsigned long nb_triangles;

	// tp2
	unsigned long *five_most_popular_pages;
	unsigned long *five_last_popular_pages;
} STATS;

void initSTATS(STATS *s){
	s->diameter = 0;
	s->entry_max_size_cluster = 0;
	s->max_size_cluster = 0;
	s->ratio_max_size_cluster = 0;
	s->nb_triangles = 0;
	
	s->five_most_popular_pages = malloc(5*sizeof(unsigned long));
	s->five_last_popular_pages = malloc(5*sizeof(unsigned long));
}

void showSTATS(STATS *s, OPTIONS *options){
	printf("\n----------- STATISTIQUES ------------\n");

	if (options->project == '1'){
		printf("Taille plus grand cluster: %d\n", s->max_size_cluster);
		printf("Ratio plus grand cluster: %.5f\n", s->ratio_max_size_cluster);
		printf("Plus grand diametre trouve: %d\n", s->diameter);
		printf("Nombre de triangles: %d\n", s->nb_triangles);
	}

	if (options->project == '2'){
		int p;
		for (p=0; p<5; ++p){
			printf("Page la plus vue n%d:\t%lu\n", p+1, s->five_most_popular_pages[p]);
		}
		printf("\n");
		for (p=4; p>=0; --p){
			printf("Page la moins vue n%d:\t%lu\n", p+1, s->five_last_popular_pages[p]);
		}
	}
	
	printf("-------------------------------------\n");
}