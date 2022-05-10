/**
 * \file main/main.c
 *
 * \brief Main entry point for weightgraph.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <expat.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

#include "main_internal.h"

RCPR_IMPORT_allocator;
RCPR_IMPORT_rbtree;
RCPR_IMPORT_resource;

int main(int argc, char* argv[])
{
    status retval, release_retval;
    uint8_t* buffer;
    size_t size;
    weightgraph* graph;
    allocator* alloc;
    output_graph_file* out;
    rbtree_node* tmp;
    rbtree_node* nil;
    double moving_average;
    double average_array[10];
    int index = 0;

    /* verify that there is a command-line argument: the filename. */
    if (argc <= 1)
    {
        fprintf(stderr, "Error: expecting one argument -- the input file.\n");
        retval = 1;
        goto done;
    }

    /* attempt to create the allocator. */
    retval = malloc_allocator_create(&alloc);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Could not create allocator.\n");
        goto done;
    }

    /* attempt to read the input file into a buffer. */
    retval = main_read_file(&buffer, &size, argv[1]);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error reading input file.\n");
        goto cleanup_allocator;
    }

    /* parse the XML file into a tree of values and a set of initial values. */
    retval = main_parse_buffer(&graph, alloc, buffer, size);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_buffer;
    }

    /* start the moving average with the initial average. */
    moving_average = graph->initial_average;
    /* build the initial average array. */
    for (int i = 0; i < 10; ++i)
    {
        average_array[i] = moving_average;
    }

    /* create the output graph file, and write the initial values. */
    retval = output_graph_create(&out, alloc, "output.eps", moving_average);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_graph;
    }

    /* get the nil node for the entry tree. */
    nil = rbtree_nil_node(graph->entries);

    /* for each date, compute the new moving average, and update the graph. */
    tmp = rbtree_root_node(graph->entries);
    if (nil != tmp)
    {
        /* get the minimum node for the tree. */
        tmp = rbtree_minimum_node(graph->entries, tmp);

        /* while this node is not NULL, walk the tree. */
        while (nil != tmp)
        {
            /* get the entry. */
            weightgraph_entry* entry =
                (weightgraph_entry*)rbtree_node_value(graph->entries, tmp);

            /* compute the updated moving average. */
            average_array[index] = entry->weight;
            ++index;
            if (index >= 10)
            {
                index = 0;
            }
            moving_average = 0;
            for (int i = 0; i < 10; ++i)
            {
                moving_average += average_array[i] * 0.1;
            }

            /* plot this entry. */
            retval =
                output_graph_plot(
                    out, entry->date, entry->weight, moving_average);
            if (STATUS_SUCCESS != retval)
            {
                goto cleanup_file;
            }

            /* get the next node in the tree. */
            tmp = rbtree_successor_node(graph->entries, tmp);
        }
    }

    /* write the final data to the graph. */
    retval = output_graph_finalize(out);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_file;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_file;

cleanup_file:
    release_retval = resource_release(&out->hdr);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_graph:
    release_retval = resource_release(&graph->hdr);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_buffer:
    free(buffer);

cleanup_allocator:
    release_retval = resource_release(allocator_resource_handle(alloc));
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
