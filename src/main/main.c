/**
 * \file main/main.c
 *
 * \brief Main entry point for weightgraph.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <expat.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

#include "main_internal.h"

RCPR_IMPORT_allocator;

int main(int argc, char* argv[])
{
    /* attempt to read the input file into a buffer. */
    /* parse the XML file into a tree of values and a set of initial values. */
    /* for each date, compute the new moving average, and update the graph. */

    (void)argc;
    (void)argv;

    printf("Feature not yet implemented.\n");

    return 1;
}
