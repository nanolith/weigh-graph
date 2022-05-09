/**
 * \file main/main_internal.h
 *
 * \brief Helpers for the main program.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <stdio.h>
#include <weightgraph/status_codes.h>
#include <weightgraph/weightgraph.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Stat and read the given file into a buffer.
 *
 * \param buffer        Pointer to receive the buffer.
 * \param buffer_size   Pointer to receive the buffer size.
 * \param filename      The name of the file to read.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status main_read_file(
    uint8_t** buffer, size_t* buffer_size, const char* filename);

/**
 * \brief Parse the given buffer, creating a weightgraph AST.
 *
 * \param graph         Pointer to receive the AST.
 * \param alloc         The allocator to use.
 * \param buffer        The buffer to parse.
 * \param buffer_size   The size of the buffer to parse.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status main_parse_buffer(
    weightgraph** graph, RCPR_SYM(allocator)* alloc,
    const uint8_t* buffer, size_t buffer_size);

/**
 * \brief An output graph file.
 */
typedef struct output_graph_file output_graph_file;

struct output_graph_file
{
    RCPR_SYM(resource) hdr;
    RCPR_SYM(allocator)* alloc;
    FILE* fp;
    /* the skip per x plot. */
    double xskip;
    /* how much to scale the weight. */
    double yscale;
    /* how much to add to the weight to correct the graph to zero. */
    double yoffset;
    double prevx;
    double prevy;
};

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
    double old_average);

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
    double moving_average);

/**
 * \brief Write the epilogue for the graph.
 *
 * \param out               Output file pointer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_finalize(output_graph_file* out);

/**
 * \brief Release an output graph file resource.
 *
 * \param r         The resource to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_resource_release(RCPR_SYM(resource)* r);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
