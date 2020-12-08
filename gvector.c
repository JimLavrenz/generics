#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE 2

typedef struct vector{
	int vector_length;
	int vector_loc;
	int elem_size;
	int last_double_index;
	void *vector;
} Vector;

void new_vector(Vector *vp, int elem_size){

	assert(elem_size>0);
	vp->elem_size = elem_size;
	vp->vector_length = INIT_SIZE;
	vp->vector_loc = 0;
	vp->last_double_index = 0;
	
	vp->vector = (char *) malloc(INIT_SIZE * elem_size);
	assert(vp->vector != NULL);

	printf("Created new vector\n");

}

void add_elem(Vector *vp, void *elem_addr){

	if(vp->vector_loc == vp->vector_length){
		vp->vector_length *= 2;
		vp->last_double_index = vp->vector_loc;
		vp->vector = realloc(vp->vector, vp->vector_length * vp->elem_size);
		assert(vp->vector != NULL);
	}
	memcpy((char *) vp->vector+vp->vector_loc*vp->elem_size, elem_addr, vp->elem_size);
	printf("adding value at location %d within %d byte array\n", vp->vector_loc, vp->vector_length);
	vp->vector_loc++;
}

void remove_elem(Vector *vp){

	if((vp->vector_loc == vp->last_double_index) && (vp->vector_loc != 0 )){
		vp->vector = realloc(vp->vector, vp->last_double_index * vp->elem_size);
		assert(vp->vector != NULL);
		vp->vector_length = vp->last_double_index;
	}
	
	if(vp->vector_loc > 0){	
		printf("Removing element\n");
		vp->vector_loc--;
	}
	else
		printf("Nothing to remove...at beginning of vector.\n");
			
}
		
void print_vector(Vector *vp){

	printf("Vector data is: \n");

	for (int i = 0; i < vp->vector_loc; i++){
		//assume it's an int for now--hence casting to int *!
		printf("%d\n", *( (int *)((char *) vp->vector+i*vp->elem_size)));
	}
}

void del_vector(Vector *vp){

	free(vp->vector);

}

int main(){

	Vector v;
	new_vector(&v, sizeof(int));

	for (int i = 0; i < 20; i++){
		add_elem(&v, &i);
	}
	for (int i = 0; i < 10; i++)
		remove_elem(&v);
	
	for (int i = 0; i < 10; i++){
		add_elem(&v, &i);
	}

	print_vector(&v);
	del_vector(&v);

}
