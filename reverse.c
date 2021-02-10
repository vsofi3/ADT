#include "stringlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]){
	char buf[BUFSIZ];
	long index;


	const StringList *strls = StringList_create(0L);

	//if failure
	if(strls == NULL){
		fprintf(stderr, "Cannot create StringList");
		return EXIT_FAILURE; //terminate program
	}

	//while there is a next line
	while(fgets(buf, BUFSIZ,  stdin) != NULL){
		char *target;
	       	target = strdup(buf); //duplicate the line on the heap
		int status;
		status = strls->append(strls,target); //append the duplicate to the StringList, returns non-zero if success
		
		if(!status){
			fprintf(stderr, "Cannot append to the StringList\n");	
			strls->destroy(strls);
			return EXIT_FAILURE;
		}
		//free(target); //free duplicate from heap
	}
		 //returns long
		for(index = strls->size(strls)-1; index >= 0L; index--){
			//get string at index i
			char *string;
			int result = strls->get(strls,index,(char**)&string);
			if(!result){
				fprintf(stderr, "Unable to get line");
				strls->destroy(strls);
				return EXIT_FAILURE;
			}
			
			else{
				printf("%s",string); //STRING
		}
		}

	
	strls->destroy(strls);
	//DESTROY THE STRINGLIST
	return EXIT_SUCCESS;
}
