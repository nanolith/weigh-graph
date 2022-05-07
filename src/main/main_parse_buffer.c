/**
 * \file main/main_parse_buffer.c
 *
 * \brief Parse an XML file in a buffer.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <expat.h>
#include <string.h>

#include "main_internal.h"

RCPR_IMPORT_rbtree;
RCPR_IMPORT_resource;

/* forward decls. */
static void main_parse_start(
    void* data, const char* element, const char** attr);
static void main_parse_end(
    void* data, const char* element);
static void main_parse_beginning_averages(
    weightgraph* graph, const char** attr);
static void main_parse_log(
    weightgraph* graph, const char** attr);

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
    const uint8_t* buffer, size_t buffer_size)
{
    status retval, release_retval;
    weightgraph* tmp;
    XML_Parser parser;
    bool free_weightgraph = true;

    /* create the initial AST. */
    retval = weightgraph_create(&tmp, alloc, 0.0);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* create the parser. */
    parser = XML_ParserCreate(NULL);
    if (NULL == parser)
    {
        retval = ERROR_PARSER_CREATE;
        goto cleanup_weightgraph;
    }

    /* set the user data to our weight graph instance. */
    XML_SetUserData(parser, tmp);
    XML_SetElementHandler(parser, &main_parse_start, &main_parse_end);

    /* parse the document. */
    if (XML_STATUS_OK !=
        XML_Parse(parser, (const char*)buffer, buffer_size, XML_TRUE))
    {
        retval = ERROR_XML_PARSE;
        goto cleanup_parser;
    }

    /* success. Return the AST to the caller. */
    *graph = tmp;
    free_weightgraph = false;
    retval = STATUS_SUCCESS;
    goto cleanup_parser;

cleanup_parser:
    XML_ParserFree(parser);

cleanup_weightgraph:
    if (free_weightgraph)
    {
        release_retval = resource_release(&tmp->hdr);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}

/**
 * \brief Parse a start element.
 *
 * \param data          Opaque pointer to the weightgraph AST.
 * \param element       The element name.
 * \param attr          The attribute array.
 */
static void main_parse_start(
    void* data, const char* element, const char** attr)
{
    weightgraph* graph = (weightgraph*)data;

    /* is this the beginning averages element? */
    if (!strcmp(element, "beginning-averages"))
    {
        /* parse this element. */
        main_parse_beginning_averages(graph, attr);
    }
    else if (!strcmp(element, "log"))
    {
        /* parse this element. */
        main_parse_log(graph, attr);
    }
    else if (!strcmp(element, "weight-log"))
    {
        /* ignore the weight-log outer tag. */
    }
    else
    {
        /* otherwise, indicate an error. */
        graph->error = true;
    }
}

/**
 * \brief Parse an end element.
 *
 * \param data          Opaque pointer to the weightgraph AST.
 * \param element       The element name.
 */
static void main_parse_end(
    void* data, const char* element)
{
    /* ignore an end attribute. */
    (void)data;
    (void)element;
}

/**
 * \brief Parse a beginning averages element.
 *
 * \param graph         The weightgraph AST.
 * \param attrs         The element attributes.
 */
static void main_parse_beginning_averages(
    weightgraph* graph, const char** attr)
{
    status retval;
    const char* date = NULL;
    const char* weight = NULL;
    weightgraph_entry* entry;

    /* loop through the attributes. */
    for (int i = 0; 0 != attr[i]; i += 2)
    {
        if (strcmp(attr[i], "date"))
        {
            date = attr[i + 1];
        }
        else if (strcmp(attr[i], "weight"))
        {
            weight = attr[i + 1];
        }
    }

    /* verify that both fields are set. */
    if (NULL == date || NULL == weight)
    {
        graph->error = true;
        goto done;
    }

    /* create a new entry. */
    retval =
        weightgraph_entry_create(&entry, graph->alloc, date, atof(weight));
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* add this entry to the graph. */
    retval = rbtree_insert(graph->entries, &entry->hdr);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_entry;
    }

    /* success. */
    goto done;

cleanup_entry:
    resource_release(&entry->hdr);

done:
    return;
}

/**
 * \brief Parse a log element.
 *
 * \param graph         The weightgraph AST.
 * \param attrs         The element attributes.
 */
static void main_parse_log(
    weightgraph* graph, const char** attr)
{
    /* loop through the attributes. */
    for (int i = 0; 0 != attr[i]; i += 2)
    {
        if (strcmp(attr[i], "moving-average"))
        {
            graph->initial_average = atof(attr[i + 1]);
        }
    }
}
