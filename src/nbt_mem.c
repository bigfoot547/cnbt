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
