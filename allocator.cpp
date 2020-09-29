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
	void mem_dump();
};

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
	
	ushort tmp = 0;
	bool* isEmpty;
	ushort* b_size; 
	while(tmp < size){
		isEmpty = (bool*)(memory + tmp);
		*isEmpty = true;
		b_size = (ushort*)(memory + tmp + 1);
		*b_size = this->size - h_size;
		block_state(*isEmpty, *b_size);
		tmp = *b_size + h_size;
	}
}

custom_allocator::custom_allocator(){
	memory = (char*)malloc(size);
	bool* isEmpty = (bool*)(memory);
	*isEmpty = true;
	ushort* b_size = (ushort*)(memory+1);
	*b_size = this->size - h_size;
}


int main(int argc, char const *argv[])
{
	custom_allocator ca;
	ca.mem_dump();
	return 0;
}