/**
 * \file weightgraph/weightgraph_entry_compare.c
 *
 * \brief Compare two weightgraph entries.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>
#include <weightgraph/weightgraph.h>

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
    void* context, const void* lhs, const void* rhs)
{
    (void)context;

    int val = strcmp((const char*)lhs, (const char*)rhs);
    if (val == 0)
    {
        return RCPR_COMPARE_EQ;
    }
    else if (val < 0)
    {
        return RCPR_COMPARE_LT;
    }
    else
    {
        return RCPR_COMPARE_GT;
    }
}
