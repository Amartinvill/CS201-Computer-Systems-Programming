#include <vector.h>

bool vector_fma(struct doubleVector * a, const struct doubleVector * b, const struct doubleVector * c)
{
	//this will be use to limit the length of all vectors
	int length = a->length; //vec_legth(a);

	//initializing the vectors to 
	double * vec_a = a->data;
	double * vec_b = b->data; 
	double * vec_c = a->data;
	
//this would return false if the vectors had varying lenghts if not continue
	if(b->lenght != length || c->legth != length)
		return false;

//for loop in inline assamby;
	



return true;
}
