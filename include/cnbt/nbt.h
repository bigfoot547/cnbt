/* This file is a part of the cnbt project.
 * See the bottom of the file for a copyright notice. */

#ifndef CNBT_NBT_H_INCLUDED
#define CNBT_NBT_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

typedef struct nbt_compound nbt_compound;
typedef struct nbt_list nbt_list;
typedef struct nbt_string nbt_string;
typedef struct nbt_byte_array nbt_byte_array;
typedef struct nbt_int_array nbt_int_array;
typedef struct nbt_long_array nbt_long_array;

typedef enum {
	NBT_TAG_END        = 0,
	NBT_TAG_BYTE       = 1,
	NBT_TAG_SHORT      = 2,
	NBT_TAG_INT        = 3,
	NBT_TAG_LONG       = 4,
	NBT_TAG_FLOAT      = 5,
	NBT_TAG_DOUBLE     = 6,
	NBT_TAG_BYTE_ARRAY = 7,
	NBT_TAG_STRING     = 8,
	NBT_TAG_LIST       = 9,
	NBT_TAG_COMPOUND   = 10,
	NBT_TAG_INT_ARRAY  = 11,
	NBT_TAG_LONG_ARRAY = 12
} nbt_type;

typedef int8_t nbt_byte;
typedef int16_t nbt_short;
typedef int32_t nbt_int;
typedef int64_t nbt_long;
typedef float nbt_float;
typedef double nbt_double;

#define nbt__mem_header_fields(_t) \
	uint32_t rc;                   \
	int32_t length;                \
	_t *data;

struct nbt__mem_header /* internal */ {
	nbt__mem_header_fields(void)
};

#define nbt__mem_access(_mem, _f) (((struct nbt__mem_header *)(_mem))->_f)
#define nbt__mem_length(_mem)     nbt__mem_access(_mem, length)
#define nbt__mem_data(_mem)       nbt__mem_access(_mem, data)
#define nbt__mem_data_t(_t, _mem) ((_t)nbt__mem_data(_mem))

#define nbt_byte_array_length(_ba) nbt__mem_length(_ba)
#define nbt_byte_array_data(_ba)   nbt__mem_data_t(nbt_byte *, _ba)

#define nbt_string_length(_s) nbt__mem_length(_s)
#define nbt_string_data(_s)   nbt__mem_data_t(char *, _s)

#define nbt_int_array_length(_ia) nbt__mem_length(_ia)
#define nbt_int_array_data(_ia)   nbt__mem_data_t(nbt_int *, _ia)

#define nbt_long_array_length(_la) nbt__mem_length(_la)
#define nbt_long_array_data(_la)   nbt__mem_data_t(nbt_long *, _la)

union nbt__tag_value /* internal name, use nbt_value instead */;

struct nbt__list_header /* internal */ {
	uint32_t rc;
	int32_t length;
	union nbt__tag_value *values;

	nbt_type type;
};

#define nbt__list_access(_l, _f) (((struct nbt__list_header *)(_l))->_f)
#define nbt_list_length(_l)      nbt__list_access(_l, length)
#define nbt_list_values(_l)      nbt__list_access(_l, values)
#define nbt_list_type(_l)        nbt__list_access(_l, type)

struct nbt__compound_header /* internal */ {
	uint32_t rc;
	uint32_t size;
};

#define nbt__compound_access(_c, _f) (((struct nbt__compound_header *)(_c))->_f)
#define nbt_compound_size(_c)        nbt__compound_access(_c, size)

typedef union nbt__tag_value /* internal name, use nbt_value instead */ {
	nbt_byte   t_byte;
	nbt_short  t_short;
	nbt_int    t_int;
	nbt_long   t_long;
	nbt_float  t_float;
	nbt_double t_double;

	nbt_byte_array *t_bytes;
	nbt_string     *t_string;
	nbt_list       *t_list;
	nbt_compound   *t_pcompound;
	nbt_int_array  *t_ints;
	nbt_long_array *t_longs;
} nbt_value;

typedef struct {
	int32_t namelen;
	char *name;
	nbt_value value;

	nbt_type type;
} nbt_tag;

/* creates an NBT compound and calls nbt_compound_ref on it */
nbt_compound *nbt_compound_create(void);
nbt_list *nbt_list_create(void);

/* makes a copy of data and creates an nbt_byte_array for it */
nbt_byte_array *nbt_copy_bytes(const nbt_byte *data, size_t length);
/* does NOT copy data (make sure it is on the heap) and creates an nbt_byte_array for it*/
nbt_byte_array *nbt_move_bytes(nbt_byte *data, size_t length);

/* if length is negative, strlen is used */
nbt_string *nbt_copy_string(const char *data, intmax_t length);
nbt_string *nbt_move_string(char *data, intmax_t length);

nbt_int_array *nbt_copy_ints(const nbt_int *data, size_t length);
nbt_int_array *nbt_move_ints(nbt_int *data, size_t length);

nbt_long_array *nbt_copy_longs(const nbt_long *data, size_t length);
nbt_long_array *nbt_move_longs(nbt_long *data, size_t length);

void nbt_ref(void *obj);
void nbt_unref(void *obj);

/* intended purpose: something like:
 *  nbt_string *s = nbt_ref_assign(nbt_compound_copy_string(c, "levelName", "among world", -1)); */
#define nbt_ref_assign(_o)   (nbt_ref(_o), _o)

void nbt_list_push(nbt_list *list, nbt_value value);
void nbt_list_push_all(nbt_list *list, nbt_value *values, size_t len);
void nbt_list_insert(nbt_list *list, nbt_value value, int32_t index);
void nbt_list_insert_all(nbt_list *list, nbt_value *values, size_t len, int32_t startidx);
void nbt_list_remove(nbt_list *list, int32_t index);
void nbt_list_clear(nbt_list *list);

nbt_type nbt_compound_type(nbt_compound *compound, const char *name);
nbt_type nbt_compound_type2(nbt_compound *compound, const char *name, int32_t len);
nbt_value nbt_compound_get(nbt_compound *compound, const char *name, nbt_type *type);
nbt_value nbt_compound_get2(nbt_compound *compound, const char *name, int32_t len, nbt_type *type);

/* variadic arguments: expects one object of the specified nbt_type */
void nbt_compound_put(nbt_compound *compound, const char *name, nbt_type type, ...);
void nbt_compound_put2(nbt_compound *compound, const char *name, int32_t len, nbt_type type, ...);

void nbt_compound_put_byte(nbt_compound *compound, const char *name, nbt_byte bytev);
void nbt_compound_put_byte2(nbt_compound *compound, const char *name, int32_t len, nbt_byte bytev);

void nbt_compound_put_short(nbt_compound *compound, const char *name, nbt_short shortv);
void nbt_compound_put_short2(nbt_compound *compound, const char *name, int32_t len, nbt_short shortv);

void nbt_compound_put_int(nbt_compound *compound, const char *name, nbt_int intv);
void nbt_compound_put_int2(nbt_compound *compound, const char *name, int32_t len, nbt_int intv);

void nbt_compound_put_long(nbt_compound *compound, const char *name, nbt_long longv);
void nbt_compound_put_long2(nbt_compound *compound, const char *name, int32_t len, nbt_long longv);

void nbt_compound_put_float(nbt_compound *compound, const char *name, nbt_float floatv);
void nbt_compound_put_float2(nbt_compound *compound, const char *name, int32_t len, nbt_float floatv);

void nbt_compound_put_double(nbt_compound *compound, const char *name, nbt_double doublev);
void nbt_compound_put_double2(nbt_compound *compound, const char *name, int32_t len, nbt_double doublev);

void nbt_compound_put_list(nbt_compound *compound, const char *name, nbt_list *list);
void nbt_compound_put_list2(nbt_compound *compound, const char *name, int32_t len, nbt_list *list);

void nbt_compound_put_compound(nbt_compound *compound, const char *name, nbt_compound *obj);
void nbt_compound_put_compound2(nbt_compound *compound, const char *name, int32_t len, nbt_compound *obj);

/* NOTE: return values are not ref'd. Call nbt_ref on them if you want to keep them. */
nbt_byte_array *nbt_compound_put_byte_array(nbt_compound *compound, const char *name, nbt_byte_array *bytes);
nbt_byte_array *nbt_compound_put_byte_array2(nbt_compound *compound, const char *name, int32_t nlen, nbt_byte_array *bytes);
nbt_byte_array *nbt_compound_copy_byte_array(nbt_compound *compound, const char *name, const nbt_byte *data, size_t dlen);
nbt_byte_array *nbt_compound_copy_byte_array2(nbt_compound *compound, const char *name, int32_t nlen, const nbt_byte *data, size_t dlen);
nbt_byte_array *nbt_compound_move_byte_array(nbt_compound *compound, const char *name, nbt_byte *data, size_t dlen);
nbt_byte_array *nbt_compound_move_byte_array2(nbt_compound *compound, const char *name, int32_t nlen, nbt_byte *data, size_t dlen);

/* if length is negative, strlen is used to determine length */
nbt_string *nbt_compound_put_string(nbt_compound *compound, const char *name, nbt_string *str);
nbt_string *nbt_compound_put_string2(nbt_compound *compound, const char *name, int32_t nlen, nbt_string *str);
nbt_string *nbt_compound_copy_string(nbt_compound *compound, const char *name, const char *data, intmax_t dlen);
nbt_string *nbt_compound_copy_string2(nbt_compound *compound, const char *name, int32_t nlen, const char *data, intmax_t dlen);
nbt_string *nbt_compound_move_string(nbt_compound *compound, const char *name, char *data, intmax_t dlen);
nbt_string *nbt_compound_move_string2(nbt_compound *compound, const char *name, int32_t nlen, char *data, intmax_t dlen);

nbt_int_array *nbt_compound_put_int_array(nbt_compound *compound, const char *name, nbt_int_array *ints);
nbt_int_array *nbt_compound_put_int_array2(nbt_compound *compound, const char *name, int32_t nlen, nbt_int_array *ints);
nbt_int_array *nbt_compound_copy_int_array(nbt_compound *compound, const char *name, const nbt_int *data, size_t dlen);
nbt_int_array *nbt_compound_copy_int_array2(nbt_compound *compound, const char *name, int32_t nlen, const nbt_int *data, size_t dlen);
nbt_int_array *nbt_compound_move_int_array(nbt_compound *compound, const char *name, nbt_int *data, size_t dlen);
nbt_int_array *nbt_compound_move_int_array2(nbt_compound *compound, const char *name, int32_t nlen, nbt_int *data, size_t dlen);

nbt_long_array *nbt_compound_put_long_array(nbt_compound *compound, const char *name, nbt_long_array *longs);
nbt_long_array *nbt_compound_put_long_array2(nbt_compound *compound, const char *name, int32_t nlen, nbt_long_array *longs);
nbt_long_array *nbt_compound_copy_long_array(nbt_compound *compound, const char *name, const nbt_long *data, size_t dlen);
nbt_long_array *nbt_compound_copy_long_array2(nbt_compound *compound, const char *name, int32_t nlen, const nbt_long *data, size_t dlen);
nbt_long_array *nbt_compound_move_long_array(nbt_compound *compound, const char *name, nbt_long *data, size_t dlen);
nbt_long_array *nbt_compound_move_long_array2(nbt_compound *compound, const char *name, int32_t nlen, nbt_long *data, size_t dlen);

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
