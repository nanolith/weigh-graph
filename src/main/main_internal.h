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
 * \brief Create an output graph file pointer, and write the preamble.
 *
 * \param fp            Pointer to receive the file pointer.
 * \param filename      The name of the output file.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_create(FILE** fp, const char* filename);

/**
 * \brief Plot a weight on the graph.
 *
 * \param fp                Output file pointer.
 * \param date              The date for this entry.
 * \param weight            The weight for this entry.
 * \param moving_average    The moving average for this entry.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_plot(
    FILE* fp, const char* date, double weight, double moving_average);

/**
 * \brief Write the epilogue for the graph.
 *
 * \param fp                Output file pointer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_finalize(FILE* fp);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
