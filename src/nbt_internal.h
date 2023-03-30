#ifndef UWORLD_NBT_INTERNAL_H_INCLUDED
#define UWORLD_NBT_INTERNAL_H_INCLUDED

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
