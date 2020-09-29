#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
using namespace std;


typedef unsigned short ushort; 

#define h_size 3

class custom_allocator{
public:
	char* memory;
	const size_t size = 1024;
	custom_allocator();
	void *mem_alloc(size_t size);
	void mem_free(void *addr);
	void mem_dump();
};



custom_allocator::custom_allocator(){
	memory = (char*)malloc(size);
	bool* isEmpty = (bool*)(memory);
	*isEmpty = true;
	ushort* b_size = (ushort*)(memory+1);
	*b_size = this->size - h_size;
}



void block_state(bool tmp, ushort size){
	if(tmp){
		cout << endl << "Block is empty ";
	}
	else{
		cout << endl << "Block isn't empty ";
	}
	cout << endl << "Size in bytes: " << size;
}




void custom_allocator::mem_dump(){	
	cout << endl << "Memory DUMP";
	ushort tmp = 0;
	bool* isEmpty;
	ushort* b_size; 
	while(tmp < size){
		isEmpty = (bool*)(memory + tmp);
		b_size = (ushort*)(memory + tmp + 1);
		block_state(*isEmpty, *b_size);
		tmp = tmp + *b_size + h_size;
	}
}

void make_h(void *mem, ushort rem){
	bool* isEmpty = (bool*)(mem);
	*isEmpty = true;
	ushort* b_size = (ushort*)(mem + 1);
	*b_size = rem - h_size;
}

void *custom_allocator::mem_alloc(size_t size){
	if(size >= this->size-3){
		cout << endl << "Error: Memory allocation failed." << endl;
		return NULL;
	}
	bool* isEmpty;
	ushort* b_size; 
	ushort tmp = 0;
	ushort rem = 0;							 						//rem of the block
	while(tmp < this->size){
		isEmpty = (bool*)(memory + tmp);
		b_size = (ushort*)(memory + tmp + 1);
		if (*isEmpty && *b_size >= size + 3)
		{
			*isEmpty = false;
			rem = *b_size - size;
			*b_size = size;
			make_h((void*)(memory + tmp + size + h_size), rem);
			return (void*)(memory + tmp + h_size);
			break;
		}
		tmp = tmp + *b_size + h_size;
	}
	cout << endl << "Error: Memory allocation failed." << endl;
	return NULL;
}



void custom_allocator::mem_free(void* addr){
	bool *isEmpty = (bool*)(addr - h_size);
	*isEmpty = true;
}


int main(int argc, char const *argv[])
{
	custom_allocator ca;
	ca.mem_dump();
	int *ptr = (int*)ca.mem_alloc(sizeof(int));
	void *ptr2 = (ca.mem_alloc(2000));
	int *ptr3 = (int*)ca.mem_alloc(sizeof(int));
	ca.mem_dump();
	ca.mem_free((void*)ptr3);
	ca.mem_dump();
	return 0;
}