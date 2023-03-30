/* This file is a part of the cnbt project.
 * See the bottom of the file for a copyright notice. */

#include "cnbt/nbt.h"
#include "nbt_internal.h"

#include <stddef.h> /* for null */
#include <stdlib.h>
#include <string.h>
#include <limits.h>

nbt_byte_array *nbt_copy_bytes(const nbt_byte *data, size_t length) {
    nbt_byte_array *arr;

    if (length > INT32_MAX) { /* INT_MAX is the max representable length for a byte array */
        return NULL;
    }

    arr = malloc(sizeof(nbt_byte_array) + length * sizeof(nbt_byte));
    if (!arr) {
        return NULL;
    }

    memset(arr, 0, sizeof(nbt_byte_array));

    arr->header.rc = 1;
    arr->header.length = length;
    arr->header.data = (nbt_byte *)(arr + 1);

    memcpy(arr->header.data, data, length * sizeof(nbt_byte));
    return arr;
}

nbt_byte_array *nbt_move_bytes(nbt_byte *data, size_t length) {
    nbt_byte_array *arr;

    if (length > INT32_MAX) {
        return NULL;
    }

    arr = malloc(sizeof(nbt_byte_array));
    if (!arr) {
        return NULL;
    }

    arr->header.rc = 1;
    arr->header.length = length;
    arr->header.data = data;

    return arr;
}

/* The MIT License (MIT)
 *
 * Copyright © 2023 bigfoot547 <bigfoot+cnbt@figboot.dev>
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE. */
