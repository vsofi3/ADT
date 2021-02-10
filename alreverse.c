#include "ADTs/arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]){
	char buf[BUFSIZ];
	long index;

	const ArrayList *al = ArrayList_create(0L, free);
	if (al == NULL){
		fprintf(stderr, "Can't create ArrayList\n");
		return EXIT_FAILURE;
	}
	while(fgets(buf, BUFSIZ, stdin) != NULL){
		char *target = strdup(buf);
		if(!al->add(al, target)){
			fprintf(stderr, "Can't append line to the ArrayList\n");
			al->destroy(al);
			return EXIT_FAILURE;
		}
	}

	for(index = al->size(al)-1; index >= 0L; index--){
		char *string;
		int result = al->get(al, index, (void **)&string);
		if(!result){
			fprintf(stderr, "Unable to get line");
			al->destroy(al);
			return EXIT_FAILURE;
		}
		else{
			printf("%s", string);
		}
	}

	al->destroy(al);
	return EXIT_SUCCESS;

}

