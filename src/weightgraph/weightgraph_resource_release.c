/**
 * \file weightgraph/weightgraph_resource_release.c
 *
 * \brief Release a weightgraph AST instance.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>
#include <weightgraph/weightgraph.h>

RCPR_IMPORT_allocator;
RCPR_IMPORT_rbtree;
RCPR_IMPORT_resource;

/**
 * \brief Release a weightgraph AST root resource.
 *
 * \param r         The resource to be released.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status weightgraph_resource_release(RCPR_SYM(resource)* r)
{
    status rbtree_release_retval = STATUS_SUCCESS;
    status reclaim_retval = STATUS_SUCCESS;
    weightgraph* graph = (weightgraph*)r;

    /* cache allocator. */
    allocator* alloc = graph->alloc;

    /* release the rbtree if initialized. */
    if (NULL != graph->entries)
    {
        rbtree_release_retval =
            resource_release(rbtree_resource_handle(graph->entries));
    }

    /* reclaim memory. */
    reclaim_retval = allocator_reclaim(alloc, graph);

    /* decode response. */
    if (STATUS_SUCCESS != rbtree_release_retval)
    {
        return rbtree_release_retval;
    }
    else
    {
        return reclaim_retval;
    }
}
