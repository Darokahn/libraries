// funcbuf_t: a static object that each function acquires exactly once and persists for the whole program. It contains a pointer to a malloc-acquired heap allocation, an active flag, and any extra data necessary to make the rest of the functions work. Its constructor dedicates it as either recursive-allowed or recursive-prohibited. Its constructor also takes a base size to which the allocation is always padded, preventing the necessity for reallocation in the average case.
//
// funcbuf_t* funcbuf(bool, int size): allocates a memory region that can accommodate both a `funcbuf_t` and an object of the size provided, after providing enough padding to align it to the maximum.
//
// acquire(funcbuf_t*, int size): takes pointer to funcbuf and an int argument that resizes the allocation. Marks the funcbuf as active, resizes it, and returns the first globally-aligned address in the allocation after the funcbuf itself. it is always an error (resize obviously accommodates this offset). If the active flag was already set and the function allows recursion, fail using the error handling method. There is an advanced funcbuf constructor that allows passing an error handling method. The default method, which is itself configurable and overridable, prints a message to stderr and exits with an error code.
//
// release(funcbuf_t*): marks a funcbuf as inactive and reallocates it to the minimum size. Does any bookkeeping necessary to undo calls to increase.
//
// increase(funcbuf_t*, int): increases the allocation to have a free block of the requested size and returns the base usable address of the new partition. The implementation may instead create a new allocation and do the necessary bookkeeping to free it when necessary.
//
// decrease(funcbuf_t*): undoes the effect of the most recent increase call. The basic non-recursive case only needs the funcbuf and acquire functions, while the recursive case pays a little complexity to get the same efficiency and safety. If you dont use proper discipline, call 1 wont fail but call 2 will.
