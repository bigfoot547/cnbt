/* This file is a part of the cnbt project.
 * See the bottom of the file for a copyright notice. */

#include "cnbt/nbt.h"
#include "nbt_internal.h"

#include <stdlib.h>
#include <assert.h>

void nbt_ref(void *obj) {
	uint32_t *orc = obj;
	assert(*orc > 0);
	++(*orc);
}

void nbt_unref(void *obj) {
	uint32_t *orc = obj;
	assert(*orc > 0);

	if (--(*orc) == 0) {
		free(obj);
	}
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
