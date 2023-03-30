/* This file is a part of the cnbt project.
 * See the bottom of the file for a copyright notice. */

#ifndef CNBT_NBT_INTERNAL_H_INCLUDED
#define CNBT_NBT_INTERNAL_H_INCLUDED

#include "cnbt/nbt.h"

struct nbt__byte_array_header {
	nbt__mem_header_fields(nbt_byte)
};

struct nbt_byte_array {
	struct nbt__byte_array_header header;
};

struct nbt__string_header {
	nbt__mem_header_fields(char)
};

struct nbt_string {
	struct nbt__string_header header;
};

struct nbt__int_array_header {
	nbt__mem_header_fields(nbt_int);
};

struct nbt_int_array {
	struct nbt__int_array_header header;
};

struct nbt__long_array_header {
	nbt__mem_header_fields(nbt_long);
};

struct nbt_long_array {
	struct nbt__long_array_header header;
};

struct nbt_list {
	struct nbt__list_header header;
	uint32_t capacity;
};

struct nbt_compound {
	struct nbt__compound_header header;
};

#endif

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
