/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Simon Gomizelj, 2014
 */

#include "memblock.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>

int memblock_open_fd(struct memblock_t *memblock, int fd)
{
    struct stat st;
    fstat(fd, &st);

    *memblock = (struct memblock_t){
        .len = st.st_size,
        .mem = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED | MAP_POPULATE, fd, 0)
    };

    madvise(memblock->mem, memblock->len, MADV_WILLNEED | MADV_SEQUENTIAL);
    return memblock->mem == MAP_FAILED ? -errno : 0;
}

int memblock_open_file(struct memblock_t *memblock, const char *filename)
{
    int ret = 0, fd = open(filename, O_RDONLY);
    if (fd < 0)
        return -errno;

    ret = memblock_open_fd(memblock, fd);
    close(fd);
    return ret;
}

int memblock_close(struct memblock_t *memblock)
{
    if (memblock->mem != MAP_FAILED)
        return munmap(memblock->mem, memblock->len);
    return 0;
}
