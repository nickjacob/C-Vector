//
//  vector.h
//		a generic vector implementation.
//		takes a comparator (for _contains) and a freeing method (so vectors can destroy the elements they contain)
//		This vector only grows, and doesn't support removal yet. I'll implement it soon.

#ifndef Pathfinder_vector_h
#define Pathfinder_vector_h
// macros
#define IN_VECTOR(i) (((int)i) >= 0 && (i) < (v)->capac) // is the index in bounds?
#define HAS_SPACE(v) (((v)->size+1) <= (v)->capac) // will adding one exceed capac?
#define GET(i) ((v)->elems[i]) // return element at i 
#define INS ((v)->size) // always insert at the end

typedef int (*vector_cmp)(void *, void *); // comparator function
typedef void (*free_elem)(void *);

typedef struct vector_internal {
	int size, capac;
	free_elem free_elem; 
	vector_cmp cmp; // comparator function
	void **elems; // array of void pointers
}vector; 

/**** Vector Methods ***/
vector new_vector(vector_cmp cmp);

// construct/destroy
void v_init(vector *v,vector_cmp cmp, free_elem free);
void v_destroy(vector *v);
void v_clone(vector *v, vector *c);

// data access
void v_insert(vector *v, void *elem);
void * v_get(vector *v, int i);
void * v_contains(vector *v, void *item);
void v_insertat(vector *v,void *e, int i);
// accessors
int v_indexof(vector *v, void *elem);
int v_size(vector *v);
int v_capac(vector *v);

// debugging
void v_print(vector *v);
#endif
