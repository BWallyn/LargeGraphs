#ifndef ARGPARSE
#define ARGPARSE

#include "argparse.h"

void load_options(OPTIONS *options, int argc, char** argv){
    printf("\nDEBUT Lecture des options\n");
    int opt;
    options->project = 2;
    options->alpha = 0.15;
    char *str_alpha = "0.15";
    char *inputFile = "none";
    char *dicFile = "none";
    options->p = 0.4;
    options->q = 0.01;
    
    while((opt = getopt(argc, argv, ":a:f:p:d:q:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'd':
                printf("\tDictionnaire nom pages: %s\n", optarg);  
                dicFile = optarg;
                break;    
            case 'p':  
                printf("\tProjet: %s\n", optarg);  
                options->project = atoi(optarg);
                break;  
            case 'f':  
                inputFile = optarg; 
                break;  
            case 'a':  
                printf("\tAlpha: %s\n", optarg); 
                options->alpha = (double) strtod(optarg,NULL);
                str_alpha = optarg;
                break;  
            case 'q':  
                printf("\tq: %s\n", optarg); 
                options->q = (double) strtod(optarg,NULL);
                break;
            case ':':  
                printf("\tOption needs a value\n");  
                break;  
            case '?':  
                printf("\tUnknown option: %c\n", optopt); 
                break;  
        }  
    }

    // on construit les noms de fichier
    options->resultPkFile = (char *) malloc(1 + 17 + strlen(str_alpha) 
                                                + 1 + strlen(inputFile) );
    strcpy(options->resultPkFile, "results/pk_alpha=");
    strcat(options->resultPkFile, str_alpha);
    strcat(options->resultPkFile, "_");
    strcat(options->resultPkFile, inputFile);

    options->resultKCoreFile = (char *) malloc(1 + 14 + strlen(inputFile) );
    strcpy(options->resultKCoreFile, "results/kcore_");
    strcat(options->resultKCoreFile, inputFile);

    options->inputFile = (char *) malloc(1 + 10 + strlen(inputFile) );
    strcpy(options->inputFile, "instances/");
    strcat(options->inputFile, inputFile);

    printf("\tFichier d'entree: %s\n", options->inputFile); 
    printf("\tFichier de resultat PageRank: %s\n", options->resultPkFile); 
    printf("\tFichier de resultat KCore: %s\n", options->resultKCoreFile);

    printf("FIN Lecture des options\n");
};

#endif