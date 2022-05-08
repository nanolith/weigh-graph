/**
 * \file main/output_graph_create.c
 *
 * \brief Create an output graph file and write the preamble.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "main_internal.h"

/**
 * \brief Create an output graph file pointer, and write the preamble.
 *
 * \param fp            Pointer to receive the file pointer.
 * \param filename      The name of the output file.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_create(FILE** fp, const char* filename)
{
    /* stub for now. */
    (void)fp;
    (void)filename;

    return -1;
}
