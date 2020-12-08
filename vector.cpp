#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using namespace std;

const int INIT_SIZE = 2;

class Vector{

	public:
		Vector(){
			vectorLength = INIT_SIZE;
			vectorLoc = 0;
			lastDoubleIndex = 0;
			vector = new int[INIT_SIZE];
			assert(vector != NULL);
		}

		void add(int i){
			if(vectorLoc == vectorLength){
				vectorLength *= 2;
				lastDoubleIndex = vectorLoc;
				vector = (int *) realloc(vector, vectorLength * sizeof(int));
				assert(vector != NULL);
			}
			vector[vectorLoc] = i;
			cout << "adding value ... " << i << " at location " << vectorLoc << " within " << vectorLength << " byte array" << endl;
			vectorLoc++;
		}

		void remove(){
			if((vectorLoc == lastDoubleIndex) && (vectorLoc != 0 )){
					vector = (int *) realloc(vector, lastDoubleIndex * sizeof(int));
					assert(vector != NULL);
					vectorLength = lastDoubleIndex;
			}

			if(vectorLoc > 0)
			{	
				cout << "Removing ... " << vector[vectorLoc-1] << endl;
				vectorLoc--;
			}
			else
				cout << "Nothing to remove...at beginning of vector." << endl;
			
		}
		
		void printVector(){
			cout << "Vector data is: " << endl;
			for (int i = 0; i < vectorLoc; i++){
				cout << vector[i];
				cout << endl;
			}
		}

		~Vector(){
			delete vector;
		}

	private:
		int vectorLength;
		int vectorLoc;
		int lastDoubleIndex;
		int *vector;

};

int main(){

	Vector v;

	for (int i = 0; i < 20; i++)
		v.add(i);

	for (int i = 0; i < 10; i++)
		v.remove();
	
	for (int i = 0; i < 10; i++)
		v.add(i);

	v.printVector();

}