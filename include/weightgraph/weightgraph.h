/**
 * \file weightgraph/weightgraph.h
 *
 * \brief Declarations and definitions for the weightgraph utility.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <rcpr/allocator.h>
#include <rcpr/rbtree.h>
#include <rcpr/resource.h>
#include <rcpr/resource/protected.h>
#include <weightgraph/config.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Root of the weightgraph AST.
 */
typedef struct weightgraph weightgraph;

struct weightgraph
{
    RCPR_SYM(resource) hdr;
    RCPR_SYM(allocator)* alloc;
    RCPR_SYM(rbtree)* entries;
    double initial_average;
    bool error;
};

/**
 * \brief Weight graph entry.
 */
typedef struct weightgraph_entry weightgraph_entry;

struct weightgraph_entry
{
    RCPR_SYM(resource) hdr;
    RCPR_SYM(allocator)* alloc;
    char* date;
    double weight;
};

/**
 * \brief Create an empty weightgraph AST.
 *
 * \param graph         Pointer to receive the new weightgraph.
 * \param alloc         The allocator to use for this operation.
 * \param average       The initial moving average for this graph.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status weightgraph_create(
    weightgraph** graph, RCPR_SYM(allocator)* alloc, double average);

/**
 * \brief Create an entry node for the weight graph.
 *
 * \param node          Pointer to receive the new weightgraph node.
 * \param alloc         The allocator to use for this operation.
 * \param date          The date string.
 * \param weight        The weight for this entry.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status weightgraph_entry_create(
    weightgraph_entry** entry, RCPR_SYM(allocator)* alloc, const char* date,
    double weight);

/**
 * \brief Comparison function type for comparing two weightgraph entry nodes.
 *
 * \param context       Context data to be passed to the comparison function.
 * \param lhs           The left-hand side of the comparison.
 * \param rhs           The right-hand side of the comparison.
 *
 * \returns an integer value representing the comparison result.
 *      - RCPR_COMPARE_LT if \p lhs &lt; \p rhs.
 *      - RCPR_COMPARE_EQ if \p lhs == \p rhs.
 *      - RCPR_COMPARE_GT if \p lhs &gt; \p rhs.
 */
RCPR_SYM(rcpr_comparison_result) weightgraph_entry_compare(
    void* context, const void* lhs, const void* rhs);

/**
 * \brief Given a weightgraph entry resource, return the key.
 *
 * \param context       Context data to be passed to the accessor function.
 * \param r             The resource.
 *
 * \returns the key for the resource.
 */
const void* weightgraph_entry_key(
    void* context, const RCPR_SYM(resource)* r);

/**
 * \brief Release a weightgraph AST root resource.
 *
 * \param r         The resource to be released.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status weightgraph_resource_release(RCPR_SYM(resource)* r);

/**
 * \brief Release a weightgraph entry resource.
 *
 * \param r         The resource to be released.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status weightgraph_entry_resource_release(RCPR_SYM(resource)* r);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
