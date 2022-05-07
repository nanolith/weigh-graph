/**
 * \file weightgraph/weightgraph_entry_resource_release.c
 *
 * \brief Release a weightgraph entry resource.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>
#include <weightgraph/weightgraph.h>

RCPR_IMPORT_allocator;
RCPR_IMPORT_resource;

/**
 * \brief Release a weightgraph entry resource.
 *
 * \param r         The resource to be released.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status weightgraph_entry_resource_release(RCPR_SYM(resource)* r)
{
    weightgraph_entry* entry = (weightgraph_entry*)r;

    /* cache the allocator. */
    allocator* alloc = entry->alloc;

    /* clean up the date if set. */
    if (NULL != entry->date)
    {
        free(entry->date);
    }

    /* reclaim memory. */
    return
        allocator_reclaim(alloc, entry);
}
