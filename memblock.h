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

#pragma once

#include <stddef.h>

struct memblock_t {
    char *mem;
    size_t len;
};

int memblock_open_fd(struct memblock_t *memblock, int fd);
int memblock_open_file(struct memblock_t *memblock, const char *filename);
int memblock_close(struct memblock_t *memblock);
