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

    /* start a new path. */
    fprintf(out->fp, "newpath\n");

    /* start at the previous x and y values. */
    fprintf(out->fp, "%lf %lf moveto\n", out->prevx, out->prevy + out->yoffset);

    /* draw a line to the new position. */
    fprintf(
        out->fp, "%lf %lf lineto\n", out->xskip + out->prevx,
        moving_average * out->yscale + out->yoffset);

    /* finish the line. */
    fprintf(out->fp, "closepath\n");
    fprintf(out->fp, "0 0 0 setrgbcolor\n");
    fprintf(out->fp, "stroke\n");

    /* if the weight is less than the average, draw a sinker. */
    if (weight < moving_average)
    {
        /* start a new path. */
        fprintf(out->fp, "newpath\n");

        /* start at the moving average location. */
        fprintf(
            out->fp, "%lf %lf moveto\n", out->xskip + out->prevx,
            moving_average * out->yscale + out->yoffset);

        /* draw a line to the weight. */
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx,
            weight * out->yscale + out->yoffset);

        /* finish the line in blue for a sinker. */
        fprintf(out->fp, "closepath\n");
        fprintf(out->fp, "0 0 1 setrgbcolor\n");
        fprintf(out->fp, "stroke\n");

        /* a sinker triangle points down and is centered on the weight. */
        fprintf(out->fp, "newpath\n");
        fprintf(
            out->fp, "%lf %lf moveto\n", out->xskip + out->prevx - 4.0,
            weight * out->yscale + 4.0 + out->yoffset);
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx + 4.0,
            weight * out->yscale + 4.0 + out->yoffset);
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx,
            weight * out->yscale - 4.0 + out->yoffset);
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx - 4.0,
            weight * out->yscale + 4.0 + out->yoffset);
        fprintf(out->fp, "closepath\n");
        fprintf(out->fp, "0 0 1 setrgbcolor\n");
        fprintf(out->fp, "fill\n");

        /* print the moving average. */
        fprintf(out->fp, "0 0 0 setrgbcolor\n");
        fprintf(out->fp, "/Courier findfont 8 scalefont setfont\n");
        fprintf(out->fp, "(%3.1lf) dup stringwidth pop\n", moving_average);
        fprintf(
            out->fp, "2 div %lf exch sub %lf moveto show\n",
            out->xskip + out->prevx,
            moving_average * out->yscale + out->yoffset + 15.0);

        /* print the weight. */
        fprintf(out->fp, "0 0 1 setrgbcolor\n");
        fprintf(out->fp, "/Courier findfont 8 scalefont setfont\n");
        fprintf(out->fp, "(%3.1lf) dup stringwidth pop\n", weight);
        fprintf(
            out->fp, "2 div %lf exch sub %lf moveto show\n",
            out->xskip + out->prevx,
            weight * out->yscale + out->yoffset - 15.0);
    }
    /* otherwise, draw a floater. */
    else
    {
        /* start a new path. */
        fprintf(out->fp, "newpath\n");

        /* start at the moving average location. */
        fprintf(
            out->fp, "%lf %lf moveto\n", out->xskip + out->prevx,
            moving_average * out->yscale + out->yoffset);

        /* draw a line to the weight. */
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx,
            weight * out->yscale + out->yoffset);

        /* finish the line in red for a floater. */
        fprintf(out->fp, "closepath\n");
        fprintf(out->fp, "1 0 0 setrgbcolor\n");
        fprintf(out->fp, "stroke\n");

        /* a floater triangle points up and is centered on the weight. */
        fprintf(out->fp, "newpath\n");
        fprintf(
            out->fp, "%lf %lf moveto\n", out->xskip + out->prevx - 4.0,
            weight * out->yscale - 4.0 + out->yoffset);
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx + 4.0,
            weight * out->yscale - 4.0 + out->yoffset);
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx,
            weight * out->yscale + 4.0 + out->yoffset);
        fprintf(
            out->fp, "%lf %lf lineto\n", out->xskip + out->prevx - 4.0,
            weight * out->yscale - 4.0 + out->yoffset);
        fprintf(out->fp, "closepath\n");
        fprintf(out->fp, "1 0 0 setrgbcolor\n");
        fprintf(out->fp, "fill\n");

        /* print the moving average. */
        fprintf(out->fp, "0 0 0 setrgbcolor\n");
        fprintf(out->fp, "/Courier findfont 8 scalefont setfont\n");
        fprintf(out->fp, "(%3.1lf) dup stringwidth pop\n", moving_average);
        fprintf(
            out->fp, "2 div %lf exch sub %lf moveto show\n",
            out->xskip + out->prevx,
            moving_average * out->yscale + out->yoffset - 15.0);

        /* print the weight. */
        fprintf(out->fp, "1 0 0 setrgbcolor\n");
        fprintf(out->fp, "/Courier findfont 8 scalefont setfont\n");
        fprintf(out->fp, "(%3.1lf) dup stringwidth pop\n", weight);
        fprintf(
            out->fp, "2 div %lf exch sub %lf moveto show\n",
            out->xskip + out->prevx,
            weight * out->yscale + out->yoffset + 15.0);
    }

    /* draw a circle where the plot point is. */
    fprintf(out->fp, "newpath\n");
    fprintf(
        out->fp, "%lf %lf 5 0 360 arc closepath\n", out->xskip + out->prevx,
        moving_average * out->yscale + out->yoffset);
    fprintf(out->fp, "0 0 0 setrgbcolor\n");
    fprintf(out->fp, "fill\n");

    /* add the date to the bottom. */
    fprintf(out->fp, "/Courier-Bold findfont 15 scalefont setfont\n");
    fprintf(out->fp, "(%s) dup stringwidth pop\n", date);
    fprintf(out->fp, "45 exch sub\n");
    fprintf(
        out->fp, "%lf exch moveto gsave 90 rotate show grestore\n",
        out->xskip + out->prevx);

    /* adjust the x and y values. */
    out->prevx += out->xskip;
    out->prevy = moving_average * out->yscale;

    return STATUS_SUCCESS;
}
