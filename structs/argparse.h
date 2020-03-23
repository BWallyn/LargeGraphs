#ifndef ARGPARSE_DEF
#define ARGPARSE_DEF

typedef struct
{
    char* inputFile;
    char* dicFile;
    int project;
    double alpha;
    char* resultPkFile;
    char* resultKCoreFile;
    double p;
    double q;
} OPTIONS;

void load_options(OPTIONS *options, int argc, char** argv);

#endif