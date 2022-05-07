/**
 * \file weightgraph/weightgraph_entry_create.c
 *
 * \brief Create a weightgraph entry.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>
#include <weightgraph/weightgraph.h>

RCPR_IMPORT_allocator;
RCPR_IMPORT_resource;

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
    double weight)
{
    status retval, release_retval;
    weightgraph_entry* tmp;

    /* allocate a weightgraph entry. */
    retval = allocator_allocate(alloc, (void**)&tmp, sizeof(*tmp));
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* clear it out and set values. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->alloc = alloc;
    tmp->weight = weight;

    /* initialize resource. */
    resource_init(&tmp->hdr, &weightgraph_entry_resource_release);

    /* copy the date. */
    tmp->date = strdup(date);
    if (NULL == tmp->date)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* success. */
    *entry = tmp;
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
