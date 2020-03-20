#ifndef LABEL_PROPAGATION
#define LABEL_PROPAGATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../structs/adjarray.h"
#include "../structs/stats.h"

/*void computeLabelPropagation(adjlist *g, STATS *s){

    unsigned long i, u, n1, n2, ln1, ln2;
    unsigned long maximum, index;
    bool node_wtht_highest_freq=true;

    printf("Before calloc\n");
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
            printf("node number: %lu\n", i);
            printf("Before calloc\n");
            n_labels = calloc(g->n, sizeof(unsigned long));

            printf("Update neighbours count labels\n");
            for(u=g->cd[i]; u<g->cd[i+1]; ++u){
                n_labels[u] = n_labels[u] + 1;
            }

            // Find the maximum
            maximum = n_labels[0];
            index = 0;
            for(u=1; u<g->n; ++u){
                if(n_labels[u] > maximum){
                    printf("Replace max\n");
                    maximum = n_labels[u];
                    index = u;
                }
            }
            
            // Change the label of the current node if needed
            if(labels[i] != labels[index]){
                printf("Replace label of node %lu (%lu) by label of node %lu (%lu)\n", i, labels[i], index, labels[index]);
                printf("number of nodes: %lu\n", g->n);
                labels[i] = labels[index];
                node_wtht_highest_freq = true;
            }
            printf("Before free n_labels\n");
            free(n_labels);
            printf("After free n_labels\n");
        }
        printf("Labels set\n");
    }
};
*/
void computeLabelPropagation(adjlist *g, STATS *s){

    unsigned long i, j, k, u, v, temp, nb_viewed_labels, lab;
    unsigned long maximum, max_lab;
    bool node_wtht_highest_freq=true;

    unsigned long *labels = calloc(g->n, sizeof(unsigned long));
    unsigned long *order = calloc(g->n, sizeof(unsigned long)); // au début identité puis va etre suffled
    unsigned long *nb_labels = calloc(g->n, sizeof(unsigned long)); // permet de savoir quels labels ont déjà été vu dans chaque voisinage + de les compter

    // Assgin unique label to each node
    for(i=0; i<g->n; ++i){
        labels[i] = i;
        order[i] = i;
    }

    // Recherche du degré maximal
    unsigned long max_degree = 0;
    for (i=0; i<g->n; ++i){
        if (g->cd[i+1]-g->cd[i] > max_degree){
            max_degree = g->cd[i+1] - g->cd[i];
        }
    }
    unsigned long *viewed_label = calloc(max_degree, sizeof(unsigned long));

    while(node_wtht_highest_freq){
        
        // random shuffle (Fisher-Yates)
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

            // le noeud sélectionné:
            u = order[i];

            // on s'assure que le sommet ne soit pas isolé
            if (g->cd[u+1]!=g->cd[u]){ 

                // permet de ne pas rechercher l'occurance d'un même label plusieurs fois

                // on recherche le maximum dans le voisinage
                nb_viewed_labels = 0; // nombre de labels rencontrés
                j = g->cd[u];

                //printf("1");
                while (j<g->cd[u+1]){
                    v = g->adj[j];

                    if (nb_labels[labels[v]] == 0){ // il faut que le label ne soit pas déja vu
                        viewed_label[nb_viewed_labels] = labels[v]; // il faut qu'on sache quels labels sont dans le voisinage
                        ++ nb_viewed_labels;

                        // on cherche d'autres labels pareils
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

                    // On remet à zéro
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

    // On note le nombre de communautés
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