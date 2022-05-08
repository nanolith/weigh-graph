/**
 * \file main/output_graph_create.c
 *
 * \brief Create an output graph file and write the preamble.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>

#include "main_internal.h"

RCPR_IMPORT_allocator;
RCPR_IMPORT_resource;

/**
 * \brief Create an output graph file, and write the preamble.
 *
 * \param fp            Pointer to receive the file pointer.
 * \param alloc         Allocator to use for this operation.
 * \param filename      The name of the output file.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_create(
    output_graph_file** fp, RCPR_SYM(allocator)* alloc, const char* filename)
{
    status retval, release_retval;
    output_graph_file* tmp;

    /* allocate memory for the output file. */
    retval = allocator_allocate(alloc, (void**)&tmp, sizeof(*tmp));
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* set initial values. */
    resource_init(&tmp->hdr, &output_graph_resource_release);
    tmp->alloc = alloc;

    /* open the output file for writing. */
    tmp->fp = fopen(filename, "w");
    if (NULL == tmp->fp)
    {
        retval = ERROR_OUTPUT_FILE_OPEN;
        goto cleanup_tmp;
    }

    fprintf(tmp->fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(tmp->fp, "%%%%Creator: (weightgraph)\n");
    fprintf(tmp->fp, "%%%%Title: (weight-graph.eps)\n");
    fprintf(tmp->fp, "%%%%BoundingBox: 0 0 800 600\n");
    fprintf(tmp->fp, "%%%%DocumentData: Clean7Bit\n");
    fprintf(tmp->fp, "%%%%LanguageLevel: 1\n");
    fprintf(tmp->fp, "%%%%Pages: 1\n");
    fprintf(tmp->fp, "%%%%EndComments\n\n");
    fprintf(tmp->fp, "%%%%BeginDefaults\n");
    fprintf(tmp->fp, "%%%%PageOrientation: Landscape\n");
    fprintf(tmp->fp, "%%%%EndDefaults\n\n");
    fprintf(tmp->fp, "%%%%BeginProlog\n");
    fprintf(tmp->fp, "%%%%EndProlog\n");
    fprintf(tmp->fp, "%%%%Page: 1 1\n");
    fprintf(tmp->fp, "%%%%PageBoundingBox: 0 0 800 600\n");

    /* success. */
    *fp = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    release_retval = resource_release(&tmp->hdr);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
