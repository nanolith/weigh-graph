/**
 * \file main/main_read_file.c
 *
 * \brief Stat and read a file.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "main_internal.h"

/**
 * \brief Stat and read the given file into a buffer.
 *
 * \param buffer        Pointer to receive the buffer.
 * \param buffer_size   Pointer to receive the buffer size.
 * \param filename      The name of the file to read.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
status main_read_file(
    uint8_t** buffer, size_t* buffer_size, const char* filename)
{
    status retval;
    struct stat st;
    size_t size;
    uint8_t* tmp;
    int fd;

    /* stat the file to get its size. */
    retval = stat(filename, &st);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_STAT_FAILED;
        goto done;
    }

    /* get the size. */
    size = st.st_size + 1;

    /* allocate enough memory to hold the contents. */
    tmp = (uint8_t*)malloc(size);
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* clear this memory. */
    memset(tmp, 0, size);

    /* open the file. */
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        retval = ERROR_OPEN_FAILED;
        goto cleanup_tmp;
    }

    /* read the file contents into the buffer. */
    ssize_t read_size = read(fd, tmp, size - 1);
    if (read_size != (ssize_t)(size - 1))
    {
        retval = ERROR_READ_FAILED;
        goto cleanup_tmp;
    }

    /* success.  Assign buffer. */
    *buffer = tmp;
    *buffer_size = size - 1;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    free(tmp);

done:
    return retval;
}
