# allocator
Description
Implementation of the mechanics of a block-type general purpose allocator.
The block contains a field with a header, and a piece of memory that the allocator returns to the user.
The header is 3 bytes long and contains information about the length of the block and whether it is busy.
[HEADER isEmpty : 1 byte, block_size : 2 bytes] [DATA PART]

Algorithm description
PROTOTYPE:    void* mem_alloc(size_t size)

When the user calls a function mem_alloc the program walks through the memory that was allocated when the allocator was 
initialized, looking for an unallocated block of memory of a suitable length. If no such block was found, it returns a 
pointer to NULL.

PROTOTYPE:    void* mem_realloc(void* addr, size_t size)

The function checks if there is a block of memory of a suitable size, and if there is one, then the function transfers data there or 
part of it (if the size of the new block is smaller), if there is no such block, the function returns a pointer to the old block.

PROTOTYPE:    void mem_free(void* addr)

Changes the value of isEmpty on header in the block, whose address was specified in the parameters of the called function, to
an unoccupied one. After, it calls function marge.

PROTOTYPE:    void marge()

The function traverses the allocator memory area and joins adjacent free blocks.



USING

To use, you just need to connect the file with the code. Works the same as malloc from a header malloc.h.

DEMONSTRATION
All memory state outputs are made with the mem_dump function, which, basically, goes through 'our' heap and prints the states of all the existing blocks.
