//
//  vector.c
//      a (mostly) generic implementation of a vector in C.
//      note: for the time being, this vector only grows. That's 
//      just because the code I needed it in didn't need to shrink.
//      however, shrinking/removing elements is pretty trivial, so I'll
//      implement that soon.
//
//  Created by Nick Jacob on 3/5/12.

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <string.h>
#include <assert.h>
#define INSERT 1
#define REMOVE -1
#define INIT_CAP 8
/************************** Generic Vector Implementation ******
 **************************************************************/

/* called when the vector needs to grow */
static void v_grow(vector *v){
    v->capac *= 2; // double 
    v->elems = realloc(v->elems,(v->capac*sizeof(void *)));
    assert(v->elems != NULL); // just in case!
}

/* v_init:
*  initializes vector
*/
void v_init(vector *v, vector_cmp cmp, free_elem fr){
    v->size = 0;
    v->capac = INIT_CAP;
    v->elems = malloc(sizeof(void *)*INIT_CAP);
    // vector methods
    v->free_elem = fr;
    v->cmp = cmp;
}

/* v_destroy:
*  Destroys the vector
*/
void v_destroy(vector *v){
    int i;
    for(i=0; i < v->size; i++){
        v->free_elem(GET(i));
    }
    free(v->elems); // free the allocated space
    free(v);
}

/* v_clone
 *  copies the vector to the specified pointer
 */
void v_clone(vector *v, vector *c){
    c->size = v->size;
    c->capac = v->capac;
    c->elems = realloc(c->elems,c->capac*sizeof(void *));
    memcpy(c->elems,v->elems,(c->size*sizeof(void *)));
}

/* v_insert:
 *  inserts an item into the vector
 */
void v_insert(vector *v, void *elem){
    if(!HAS_SPACE(v)){
        v_grow(v);
    }
    v->elems[INS] = elem;
    assert(v->elems[INS] == elem);
    v->size++;
}

/* v_get:
 *  returns the element at the given index
 */
void * v_get(vector *v, int i){
    if(IN_VECTOR(i)){
        return (GET(i)!=NULL) ? GET(i) : NULL;
    }
    return NULL;
}

/* v_insertat:
 *  inserts the element at the given index (irrespective of overwriting)
 */
void v_insertat(vector *v, void *e, int i){
    if(IN_VECTOR(i)){
        if(GET(i)!=NULL){
            v->free_elem(GET(i)); // free what was there before
        }

        v->elems[i] = e; // add the new one
    }
}


/* v_contains:
 *  does a O(n) scan for the element
 */
void * v_contains(vector *v, void *elem){
    int i;
    for(i=0; i < v->size; i++){
        if(v->cmp(GET(i),elem)==0){
            return GET(i);
        }
    }
    return NULL;
}

/* Returns the index of a given element (similar to contains) */
int v_indexof(vector *v, void *elem){
    int i;
    for(i=0; i < v->size; i++){
        if(v->cmp(GET(i),elem)==0){
            return i;
        }
    }
    return -1;
}

/* Returns the size of the vector */
int v_size(vector *v){
    return (v!=NULL) ? v->size : -1; 
}

/* Returns the capacity of the vector */
int v_capac(vector *v){
    return (v!=NULL) ? v->capac : -1;
}

/* debugging: print vector */
void v_print(vector *v){
    int i;
    for(i=0; i < v_size(v); i++){
        printf("[%d]: %s \n",i,(char *)v_get(v,i));
    }
}
