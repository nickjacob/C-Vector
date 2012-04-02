# C-Vector
### A Generic Vector Implementation in C

## Status
Currently, the vector only **grows**, and elements cannot be removed. I'll implement shrinking/removal when I get a chance.

## Usage
Example for a vector of strings:

	vector *new_vector = malloc(sizeof(vector));
	v_init(new_vector, (vector_cmp)strcmp, (free_elem)free);

	/* my_str is a char* -- a string */
	v_insert(new_vector,my_str);

	int size = v_size(new_vector);

	v_destroy(new_vector); // also frees the vector ptr itself

### Comparator
A comparator function only *needs* to test equality, but can also show greater/less than as does strcmp or any standard library comparator. It should take two pointers of the type being stored in that vector:

	int my_comparator(obj_type *a, obj_type *b){
		if(a->val == b->val) return 0; // equality
		else return -1; // unequal
	}

### free_elem / Free Function
	
	void my_free_func(obj_type *to_free){
		free(to_free->data)
		free(to_free);
	}
