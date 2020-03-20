#ifndef LABEL_PROPAGATION
#define LABEL_PROPAGATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../structs/adjarray.h"
#include "../structs/stats.h"

void computeLabelPropagation(adjlist *g, STATS *s){

    unsigned long i, u, n1, n2, ln1, ln2;
    unsigned long maximum, index, index_label;
    bool node_wtht_highest_freq=true;

    unsigned long *labels = calloc(g->n, sizeof(unsigned long));
    unsigned long *n_labels  = calloc(g->n, sizeof(unsigned long));
    
    // Assgin unique label to each node
    for(i=0; i<g->n; ++i) labels[i] = i;

    while(node_wtht_highest_freq){
        
        // random shuffle
        for(u=0; u<g->n; ++u){
            //srand(time(NULL));
            n1 = rand()%g->n;
            n2 = rand()%g->n;
            //printf("\n n1: %lu", n1);
            //printf("\n n2: %lu", n2);
            ln1 = labels[n1];
            ln2 = labels[n2];
            labels[n2] = ln1;
            labels[n1] = ln2;
        }

        // Suppose that we did not change any label
        node_wtht_highest_freq = false;
        // Set the label with the highest frequency among the neighbours
        for(i=0; i<g->n; ++i){
            n_labels = calloc(g->n, sizeof(unsigned long));

            for(u=g->cd[i]; u<g->cd[i+1]; ++u){
                index_label = labels[g->adj[u]];
                n_labels[index_label] = n_labels[index_label] + 1;
            }

            // Find the maximum
            maximum = n_labels[0];
            index = 0;
            for(u=1; u<g->n; ++u){
                if(n_labels[u] > maximum){
                    printf("Update max by node %lu\n", u);
                    maximum = n_labels[u];
                    index = u;
                }
            }
            
            // Change the label of the current node if needed
            if(labels[i] != labels[index]){
                printf("Replace label of node %lu (%lu) by label of node %lu (%lu)\n", i, labels[i], index, labels[index]);
                labels[i] = labels[index];
                node_wtht_highest_freq = true;
            }
            free(n_labels);
        }
    }
    printf("\n");
    for(i=0; i<g->n; ++i) printf("%lu ", labels[i]);
};

#endif