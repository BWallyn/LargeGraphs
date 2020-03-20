#ifndef LABEL_PROPAGATION
#define LABEL_PROPAGATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../structs/adjarray.h"
#include "../structs/stats.h"


void computeLabelPropagation(adjlist *g, STATS *s){

    unsigned long i, j, k, u, v, temp, nb_viewed_labels, lab;
    unsigned long maximum, max_lab;
    bool node_wtht_highest_freq=true;

    unsigned long *labels = calloc(g->n, sizeof(unsigned long));
    unsigned long *order = calloc(g->n, sizeof(unsigned long)); // first identity then shuffled
    unsigned long *nb_labels = calloc(g->n, sizeof(unsigned long)); // permet de savoir quels labels ont déjà été vu dans chaque voisinage + de les compter

    // Assign unique label to each node
    for(i=0; i<g->n; ++i){
        labels[i] = i;
        order[i] = i;
    }

    // Search max degree
    unsigned long max_degree = 0;
    for (i=0; i<g->n; ++i){
        if (g->cd[i+1]-g->cd[i] > max_degree){
            max_degree = g->cd[i+1] - g->cd[i];
        }
    }
    unsigned long *viewed_label = calloc(max_degree, sizeof(unsigned long));

    while(node_wtht_highest_freq){
        
        // Random shuffle (Fisher-Yates)
        for(i=0; i<g->n-1; ++i){
            j = i + rand()%(g->n-i);
            temp = order[i];
            order[i] = order[j];
            order[j] = temp;
        }

        // Suppose that we did not change any label
        node_wtht_highest_freq = false;
        // Set the label with the highest frequency among the neighbours
        for(i=0; i<g->n; ++i){

            // node selected
            u = order[i];

            // check that it is not an isolated node
            if (g->cd[u+1]!=g->cd[u]){ 
                // Avoid to look for the same label several times

                // Look for the max in the neighbourhood
                // Number of labels seen
                nb_viewed_labels = 0;
                j = g->cd[u];

                //printf("1");
                while (j<g->cd[u+1]){
                    v = g->adj[j];

                    if (nb_labels[labels[v]] == 0){ // Need a label not already seen
                        viewed_label[nb_viewed_labels] = labels[v]; // check that labels are neighbours
                        ++ nb_viewed_labels;

                        // Look for same labels
                        for (k=j; k<g->cd[u+1]; ++k){
                            if (labels[g->adj[k]] == labels[v]){
                                ++ nb_labels[labels[v]];
                            }
                        }
                    }
                    ++j;
                }
                maximum = 0;
                for (k=0; k<nb_viewed_labels; ++k){
                    lab = viewed_label[k];
                    if (maximum < nb_labels[lab]){
                        maximum = nb_labels[lab];
                        max_lab = lab;
                    }

                    // Reset counters
                    nb_labels[lab] = 0;
                    viewed_label[k] = 0;
                }

                // Change the label of the current node if needed
                if(labels[u] != max_lab){
                    labels[u] = max_lab;
                    node_wtht_highest_freq = true;
                }
            }
        }
    }

    // Number of communities
    mergeSort(labels, 0, g->n-1);
    s->nb_communities = 1;
    for (i=0; i<g->n-1; ++i){
        //printf("%lu ", labels[i]);
        if (labels[i]<labels[i+1]){
            ++ s->nb_communities;
        }
    }
}


#endif