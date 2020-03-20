#ifndef STATS_DEF
#define STATS_DEF

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
	long int k_core_value;

	//tp3
	long int nb_communities;
} STATS;

void initSTATS(STATS *s);
void showSTATS(STATS *s, OPTIONS *options);

#endif