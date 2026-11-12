/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2016-2026, David Kebo Houngninou
 *
 * FILENAME: tutorial1.c
 * Overview: BDD tutorial
 * AUTHOR: David Kebo Houngninou
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include "cudd.h"

/**
 * Print a dd summmary
 * pr = 0 : prints nothing
 * pr = 1 : prints counts of nodes and minterms
 * pr = 2 : prints counts + disjoint sum of product
 * pr = 3 : prints counts + list of nodes
 * pr > 3 : prints counts + disjoint sum of product + list of nodes
 * @param the dd node
 */
void print_dd (DdManager *gbm, DdNode	*dd, int n, int pr )
{
    printf("DdManager nodes: %ld | ", Cudd_ReadNodeCount(gbm)); /*Reports the number of live nodes in BDDs and ADDs*/
    printf("DdManager vars: %d | ", Cudd_ReadSize(gbm) ); /*Returns the number of BDD variables in existance*/
    printf("DdManager reorderings: %d | ", Cudd_ReadReorderings(gbm) ); /*Returns the number of times reordering has occurred*/
    printf("DdManager memory: %ld \n", Cudd_ReadMemoryInUse(gbm) ); /*Returns the memory in use by the manager measured in bytes*/
    Cudd_PrintDebug(gbm, dd, n, pr);	// Prints to the standard output a DD and its statistics: number of nodes, number of leaves, number of minterms.
}


/**
 * Writes a dot file representing the argument DDs
 * @param the node object
 */
void write_dd (DdManager *gbm, DdNode	*dd, char* filename)
{
    FILE *outfile; // output file pointer for .dot file
    outfile = fopen(filename,"w");
    DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
    ddnodearray[0] = dd;
    Cudd_DumpDot(gbm, 1, ddnodearray, NULL, NULL, outfile);	// dump the function to .dot file
    free(ddnodearray);
    fclose (outfile); // close the file */
}

// This program creates a single BDD variable
int main (int argc, char *argv[])
{
    (void)argc; /* unused: kept to match the original 2016 signature */
    (void)argv;

    DdManager *gbm;	/* Global BDD manager. */
    char filename[30];

    /* Create the output directory for the .dot file if it does not
     * already exist (ported for CUDD 3.0.0: the 2016 version assumed
     * ./bdd already existed). */
    if (mkdir("bdd", 0755) != 0 && errno != EEXIST) {
        perror("mkdir(\"bdd\")");
        return 1;
    }

    gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
    DdNode *bdd = Cudd_bddNewVar(gbm); /*Creat a new BDD variable*/
    Cudd_Ref(bdd); /*Increases the reference count of a node*/
    DdNode *add = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
    Cudd_Ref(add); /*The ADD is a new node and needs its own reference*/
    Cudd_RecursiveDeref(gbm, bdd); /*The BDD is no longer needed once converted*/
    print_dd (gbm, add, 2,4);	/*Print the dd to standard output*/
    sprintf(filename, "./bdd/tutorial1.dot"); /*Write .dot filename to a string*/
    write_dd(gbm, add, filename);  /*Write the resulting cascade dd to a file*/
    Cudd_RecursiveDeref(gbm, add); /*Release the ADD before quitting the manager*/

    /* Ported for CUDD 3.0.0: verify that nothing is leaked before
     * shutting the manager down. */
    if (Cudd_CheckZeroRef(gbm) > 0) {
        fprintf(stderr, "tutorial1: %d node(s) still referenced at exit\n",
                Cudd_CheckZeroRef(gbm));
    }
    Cudd_Quit(gbm);
    return 0;
}
