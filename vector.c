#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE 2

typedef struct vector{
	int vector_length;
	int vector_loc;
	int last_double_index;
	int *vector;
} Vector;

int new_vector(Vector *vp){

	vp->vector_length = INIT_SIZE;
	vp->vector_loc = 0;
	vp->last_double_index = 0;
	vp->vector = (int *) malloc(INIT_SIZE * sizeof(int));
	assert(vp->vector != NULL);
}

void add_elem(Vector *vp, int i){

	if(vp->vector_loc == vp->vector_length){
		vp->vector_length *= 2;
		vp->last_double_index = vp->vector_loc;
		vp->vector = (int *) realloc(vp->vector, vp->vector_length * sizeof(int));
		assert(vp->vector != NULL);
	}
	vp->vector[vp->vector_loc] = i;
	printf("adding value ... %d at location %d within %d byte array\n", i, vp->vector_loc, vp->vector_length);
	vp->vector_loc++;
}

void remove_elem(Vector *vp, int i){

	if((vp->vector_loc == vp->last_double_index) && (vp->vector_loc != 0 )){
		vp->vector = (int *) realloc(vp->vector, vp->last_double_index * sizeof(int));
		assert(vp->vector != NULL);
		vp->vector_length = vp->last_double_index;
	}

	if(vp->vector_loc > 0){	
		printf("Removing ... %d\n", vp->vector[vp->vector_loc - 1]);
		vp->vector_loc--;
	}
	else
		printf("Nothing to remove...at beginning of vector.\n");
			
}
		
void print_vector(Vector *vp){

	printf("Vector data is: \n");

	for (int i = 0; i < vp->vector_loc; i++){
		printf("%d\n", vp->vector[i]);
	}
}

void del_vector(Vector *vp){

	free(vp->vector);

}

int main(){

	Vector v;
	new_vector(&v);

	for (int i = 0; i < 20; i++)
		add_elem(&v, i);

	for (int i = 0; i < 10; i++)
		remove_elem(&v, i);
	
	for (int i = 0; i < 10; i++)
		add_elem(&v, i);

	print_vector(&v);
	del_vector(&v);

}
