#include "cnbt/nbt.h"
#include <stdio.h>

int main(void) {
	printf("%zu\n", sizeof(nbt_tag));

	struct nbt_compound *c = nbt_compound_create();

	nbt_unref(c);
	//struct nbt_compound *comp = nbt_compound_create();
	//nbt_compound_put_compound("sus", nbt_compound_create());
	return 0;
}
