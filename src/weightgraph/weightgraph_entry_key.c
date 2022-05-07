/**
 * \file weightgraph/weightgraph_entry_key.c
 *
 * \brief Get the key value for this weightgraph entry.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>
#include <weightgraph/weightgraph.h>

/**
 * \brief Given a weightgraph entry resource, return the key.
 *
 * \param context       Context data to be passed to the accessor function.
 * \param r             The resource.
 *
 * \returns the key for the resource.
 */
const void* weightgraph_entry_key(
    void* context, const RCPR_SYM(resource)* r)
{
    (void)context;
    weightgraph_entry* entry = (weightgraph_entry*)r;

    return entry->date;
}
