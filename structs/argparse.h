#ifndef ARGPARSE_DEF
#define ARGPARSE_DEF

typedef struct
{
    char* inputFile;
    int project;

    //tp2
    double alpha;
    char* resultPkFile;
    char* resultKCoreFile;

    //tp3
    double q;
    char benchmark;
    char* resultLouvainFile;
    char* resultLabelFile;
} OPTIONS;

void load_options(OPTIONS *options, int argc, char** argv);

#endif