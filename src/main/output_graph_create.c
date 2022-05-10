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
 * \param old_average   The previous average.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_create(
    output_graph_file** fp, RCPR_SYM(allocator)* alloc, const char* filename,
    double old_average)
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
    tmp->xskip = (1100.0 - 20.0) / 31.0;
    tmp->yscale = 1100.0 / 400.0;
    tmp->yoffset = 50.0;
    tmp->prevx = 50;
    tmp->prevy = old_average * tmp->yscale;

    /* open the output file for writing. */
    tmp->fp = fopen(filename, "w");
    if (NULL == tmp->fp)
    {
        retval = ERROR_OUTPUT_FILE_OPEN;
        goto cleanup_tmp;
    }

    /* front matter. */
    fprintf(tmp->fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(tmp->fp, "%%%%Creator: (weightgraph)\n");
    fprintf(tmp->fp, "%%%%Title: (weight-graph.eps)\n");
    fprintf(tmp->fp, "%%%%BoundingBox: 0 0 1200 1200\n");
    fprintf(tmp->fp, "%%%%DocumentData: Clean7Bit\n");
    fprintf(tmp->fp, "%%%%LanguageLevel: 1\n");
    fprintf(tmp->fp, "%%%%Pages: 1\n");
    fprintf(tmp->fp, "%%%%EndComments\n\n");
    fprintf(tmp->fp, "%%%%BeginDefaults\n");
    fprintf(tmp->fp, "%%%%PageOrientation: Portrait\n");
    fprintf(tmp->fp, "%%%%EndDefaults\n\n");
    fprintf(tmp->fp, "%%%%BeginProlog\n");
    fprintf(tmp->fp, "%%%%EndProlog\n");

    /* start page. */
    fprintf(tmp->fp, "%%%%Page: 1 1\n");
    fprintf(tmp->fp, "%%%%PageBoundingBox: 0 0 1200 1200\n");

    /* draw graph boundaries. */
    fprintf(tmp->fp, "newpath\n");
    fprintf(tmp->fp, "50 50 moveto\n");
    fprintf(tmp->fp, "0 1100 rlineto\n");
    fprintf(tmp->fp, "1100 0 rlineto\n");
    fprintf(tmp->fp, "0 -1100 rlineto\n");
    fprintf(tmp->fp, "-1100 0 rlineto\n");
    fprintf(tmp->fp, "closepath\n");
    fprintf(tmp->fp, "0 0 0 setrgbcolor\n");
    fprintf(tmp->fp, "stroke\n");

    /* create ticks on Y-axis. */
    for (int i = 5; i <= 400; i += 5)
    {
        fprintf(tmp->fp, "newpath\n");
        fprintf(
            tmp->fp, "50 %lf moveto\n",
            ((double)i) * tmp->yscale + tmp->yoffset);
        fprintf(tmp->fp, "5 0 rlineto\n");
        fprintf(tmp->fp, "closepath\n");
        fprintf(tmp->fp, "0 0 0 setrgbcolor\n");
        fprintf(tmp->fp, "stroke\n");

        if ((i % 10) == 0)
        {
            fprintf(tmp->fp, "/Courier-Bold findfont 15 scalefont setfont\n");
            fprintf(tmp->fp, "(%d) dup stringwidth pop\n", i);
            fprintf(tmp->fp, "45 exch sub\n");
            fprintf(
                tmp->fp, "%lf moveto show\n",
                ((double)i) * tmp->yscale + tmp->yoffset);
        }
    }

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
