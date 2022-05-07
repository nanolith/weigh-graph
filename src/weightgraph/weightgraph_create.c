/**
 * \file weightgraph/weightgraph_create.c
 *
 * \brief Create an empty weightgraph AST.
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
    weightgraph** graph, RCPR_SYM(allocator)* alloc, double average)
{
    status retval, release_retval;
    weightgraph* tmp;

    /* allocate memory for this AST instance. */
    retval = allocator_allocate(alloc, (void**)&tmp, sizeof(*tmp));
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* set initial values. */
    tmp->alloc = alloc;
    tmp->initial_average = average;

    /* initialize the resource. */
    resource_init(&tmp->hdr, &weightgraph_resource_release);

    /* initialize the rbtree instance. */
    retval =
        rbtree_create(
            &tmp->entries, alloc, &weightgraph_entry_compare,
            &weightgraph_entry_key, NULL);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    *graph = tmp;
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
