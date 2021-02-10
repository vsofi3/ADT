#include "stringlist.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 50L

typedef struct sldata {          /* data for each instance */
    /* you must define the instance-specific fields for each StringList */
	long capacity;
	long size; 
	char **theArray; //array of strings
} SLData;
	
/* any helper functions needed by the methods */

static void sl_destroy(const StringList *sl) {
    SLData *sld = (SLData *)(sl->self);

    	//destroy elements in the array itself
	for(long i = 0; i < sl->size(sl); i++){
		free(sld->theArray[i]);
	}
    /* the body of the destroy() method */
    free(sld->theArray); //free the elements in the array
    free(sld);//free the StringList structure
    free((void *)sl); //free the dispatch table
}

static int sl_append(const StringList *sl, char *s) {
    SLData *sld = (SLData *)(sl->self);
    int status = (sld->capacity > sld->size);

    /* the body of the append() method - it must grow the capacity of
       the stringlist if you have run out of room */

    if(!status){ //char * is eight bytes
	size_t nbytes = 2 * sld->capacity * sizeof(char *);
	char **temp = (char **)realloc(sld->theArray, nbytes);
	if(temp != NULL){
		status = 1;
		sld->theArray = temp;
		sld->capacity *= 2;
	}
    }
    if(status){
	sld->theArray[sld->size++] = s; //add the string
    }
    return status;
}

static int sl_get(const StringList *sl, long index, char **sptr) { //char **sptr is the string element
    SLData *sld = (SLData *)sl->self;

    /* the body of the get() method */
  
    int status = (index >= 0L && index < sld->size);
    if(status){
	*sptr = sld->theArray[index];
    }
    return status;
}

static long sl_size(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;

    /* the body of the size() method */
    return sld->size; //just return the size part of self
}

static StringList template = {
    NULL, sl_destroy, sl_append, sl_get, sl_size
};

const StringList *StringList_create(long capacity) {/* use default if 0L */

    /* the body of the constructor */
	StringList *sl = (StringList *)malloc(sizeof(StringList));

	if(sl != NULL){
		SLData *sld = (SLData *)malloc(sizeof(SLData));
		if(sld != NULL){
			long cap = (capacity <= 0) ? DEFAULT_CAPACITY : capacity;
			char **array = (char **)malloc(cap * sizeof(long));
		
		if(array != NULL){
			sld->capacity = cap;
			sld->size = 0L;
			sld->theArray = array;
			*sl = template;
			sl->self = sld;
		}
		else{
			free(sld);
			free(sl);
			sl = NULL;
		}
	}
	else{
		free(sl);
		sl = NULL;
	}
		}
	return sl;
}

