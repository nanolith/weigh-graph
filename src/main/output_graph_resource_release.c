/**
 * \file main/output_graph_resource_release.c
 *
 * \brief Release an output graph resource.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "main_internal.h"

RCPR_IMPORT_allocator;
RCPR_IMPORT_resource;

/**
 * \brief Release an output graph file resource.
 *
 * \param r         The resource to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status output_graph_resource_release(RCPR_SYM(resource)* r)
{
    output_graph_file* out = (output_graph_file*)r;

    /* cache allocator. */
    allocator* alloc = out->alloc;

    /* close file. */
    fclose(out->fp);

    /* reclaim memory. */
    return
        allocator_reclaim(alloc, out);
}
