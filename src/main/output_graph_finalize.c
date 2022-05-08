/**
 * \file main/output_graph_finalize.c
 *
 * \brief Write the epilogue for the graph.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "main_internal.h"

/**
 * \brief Write the epilogue for the graph.
 *
 * \param fp                Output file pointer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_finalize(FILE* fp)
{
    fprintf(fp, "%%%%PageTrailer\n");
    fprintf(fp, "%%%%Trailer\n");
    fprintf(fp, "%%%%EOF\n");

    return STATUS_SUCCESS;
}
