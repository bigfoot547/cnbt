#include "cnbt/nbt.h"
#include <stdio.h>

int main(void) {
	nbt_byte amog[] = {0, 1, 2, 3, 4};
	nbt_byte_array *arr1 = nbt_copy_bytes(amog, 5);
	nbt_byte_array *arr2 = nbt_move_bytes(amog, 5);

	for (int i = 0; i < nbt_byte_array_length(arr1); ++i) {
		printf("%hhd\n", nbt_byte_array_data(arr1)[i]);
	}

	printf("trap\n");

	nbt_unref(arr1);
	nbt_unref(arr2);
	return 0;
}
