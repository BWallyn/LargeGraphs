#ifndef PAGERANK
#define PAGERANK

#include "../structs/stats.h"
#include "../structs/adjarray.h"

void computePageRank(adjlist* g, STATS *s, double alpha, int t, char* result_file){

	// Initialisation de P
	double *P_prev = calloc(g->n,sizeof(double));
	double *P_next = calloc(g->n, sizeof(double));
	unsigned long i, u;
	int l, p, k;
	double norm = 0.0;
	for (i=0; i<g->n; ++i){ P_prev[i] = 1.0/g->n; }

	// Itérations
	for (k=1; k<=t; ++k){

		for (i=0; i<g->e; ++i){
			if (g->outD[g->edges[i].s] > 0.1){
				P_next[g->edges[i].t] += P_prev[g->edges[i].s]/g->outD[g->edges[i].s];
			}
			else{
				P_next[g->edges[i].s] += P_prev[g->edges[i].t]/g->n;
			}
		}
		for (u=0; u<g->n; ++u){
			norm += P_next[u];

			// On rajoute une partie de l'identité
			P_next[u] = (1-alpha)*P_next[u]+alpha/g->n;
		}

		for (u=0; u<g->n; ++u){
			// On rescale
			P_next[u] += (1-norm)/g->n;
			
			// On passe à l'itérée suivante
			P_prev[u] = P_next[u];
			P_next[u] = 0.0;
		}
		norm = 0.0;
	}

	// On récupère les 5 meilleurs et 5 pires
	double *best_five_values = calloc(5, sizeof(double));
	double *worst_five_values = calloc(5,sizeof(double));
	for (p=0; p<5; ++p){ worst_five_values[p] = 1; }


	for (u=0; u<g->n; ++u){
		for (p=0; p<5; ++p){
			
			// si on a une amélioration dans les 5 meilleurs
			if (P_prev[u]>best_five_values[p]){

				//on décale tout
				for (l=4;l>p; --l){
					s->five_most_popular_pages[l] = s->five_most_popular_pages[l-1];
					best_five_values[l] = best_five_values[l-1];
				}
				s->five_most_popular_pages[p] = u;
				best_five_values[p] = P_prev[u];

				break;
			}

			// si on a une amélioration dans les 5 pires
			if (P_prev[u]<worst_five_values[p] && P_prev[u]>1.0/g->n+1e-5){

				//on décale tout
				for (l=4;l>p; --l){
					s->five_last_popular_pages[l] = s->five_last_popular_pages[l-1];
					worst_five_values[l] = worst_five_values[l-1];
				}
				s->five_last_popular_pages[p] = u;
				worst_five_values[p] = P_prev[u];

				break;
			}
		}
	}

	// on enregistre les résultats dans un fichier
	FILE * fp;
   	fp = fopen (result_file,"w");
   	for (u=0; u<g->n; ++u){
   		if (g->cd[u+1]!=g->cd[u]){
   			fprintf(fp, "%lu\t%.9f\t%d\t%d\n", u, P_prev[u], g->cd[u+1]-g->cd[u]-g->outD[u], g->outD[u]);
   		}
   	}
    fclose (fp);

	// on libère la mémoire
	free(P_next);
	free(P_prev);
};

#endif