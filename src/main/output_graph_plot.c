/**
 * \file main/output_graph_plot.c
 *
 * \brief Plot a weight on the graph.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "main_internal.h"

/**
 * \brief Plot a weight on the graph.
 *
 * \param out               Output file pointer.
 * \param date              The date for this entry.
 * \param weight            The weight for this entry.
 * \param moving_average    The moving average for this entry.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_plot(
    output_graph_file* out, const char* date, double weight,
    double moving_average)
{
    (void)date;
    (void)weight;

    /* we want to move to the height of the moving average. */
    fprintf(out->fp, "0 %f rmoveto\n", moving_average);

    return STATUS_SUCCESS;
}
