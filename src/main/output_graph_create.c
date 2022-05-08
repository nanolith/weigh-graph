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
    status retval;

    /* open the output file for writing. */
    *fp = fopen(filename, "w");
    if (NULL == *fp)
    {
        retval = ERROR_OUTPUT_FILE_OPEN;
        goto done;
    }

    fprintf(*fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(*fp, "%%%%Creator: (weightgraph)\n");
    fprintf(*fp, "%%%%Title: (weight-graph.eps)\n");
    fprintf(*fp, "%%%%BoundingBox: 0 0 800 600\n");
    fprintf(*fp, "%%%%DocumentData: Clean7Bit\n");
    fprintf(*fp, "%%%%LanguageLevel: 1\n");
    fprintf(*fp, "%%%%Pages: 1\n");
    fprintf(*fp, "%%%%EndComments\n\n");
    fprintf(*fp, "%%%%BeginDefaults\n");
    fprintf(*fp, "%%%%PageOrientation: Landscape\n");
    fprintf(*fp, "%%%%EndDefaults\n\n");
    fprintf(*fp, "%%%%BeginProlog\n");
    fprintf(*fp, "%%%%EndProlog\n");
    fprintf(*fp, "%%%%Page: 1 1\n");
    fprintf(*fp, "%%%%PageBoundingBox: 0 0 800 600\n");

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
