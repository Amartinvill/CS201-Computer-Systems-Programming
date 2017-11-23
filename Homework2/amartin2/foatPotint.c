#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//This function gets the value of the fractionint to obtain M 
float get_M(int frac_value ,int expo)
{
	float M = 1;
	float k = 0;
	k = frac_value/(pow(2, expo)); //figuring out what the value of the fraction is
	M = M + k; //were adding 1 plus the fractional value
	return M;
}

//The porpuse of this function is to obtain the value of the exponent
int  get_E(int mantissa, int K)
{
	//E  = Exponent - bias where the bieas is  2^(k-1)-1
	int E = 0;
	float bias = 0;
	int bias_exp = 0;
	bias_exp = K - 1;
	bias = (pow(2,bias_exp)) - 1; //pow is the same thing as using 2^(exp)
	E = mantissa - bias;
	return E;
}

int main(int argc,char * argv[])
{
	unsigned int hex = 0;
	
	int frac_bit_n = 0;
	int expo_bit_k = 0; 

	sscanf(argv[1],"%d",&frac_bit_n); //obtaining the integer value from the string of argv	
	sscanf(argv[2],"%d",&expo_bit_k); //obtainin the integer value from the string of argv
	
	//this is an error state that allows only 4 arguments
	if(argc!=4) 
	{
		printf("<./a.out><# of frac_bits><# of expo_bits><hex_to_convert>\n\n");
		fprintf(stderr, "Not enough arguments\n\n");
		
		exit(-1);
	}
	//if the second argument take a number ranging from 2 to 10 any other numbers will
	//resunt and an error message, then exiting out form the editor
	else if(frac_bit_n<2 || frac_bit_n>10)
	{
		fprintf(stderr, "Illigal number of fraction bits(%d). Shound be between 2 and 10\n\n",frac_bit_n);
		exit(-1);
	}
	//the third arguments takes an exponent number from 3 to 5 and anything else
	//will result in an error message, exiting out the editor.
	else if(expo_bit_k<3 ||expo_bit_k>5)
	{
		fprintf(stderr, "Illigal number of exponent bits(%d). Shound be between 3 and 5\n\n",expo_bit_k);
		exit(-1);
	}
	//taking a hexadecimal string to a unsigned interger 
	sscanf(argv[3],"%x",&hex);
	
	unsigned int frac, man;
	float M = 0;
	int E = 0;
	int S = 0;
	float  V = 0; // result
	
	//takes the factional bits and shifts left and then right to isolate the value.
	frac = hex << (32-frac_bit_n);
	frac = frac >> (32-frac_bit_n); 
	M = get_M(frac, frac_bit_n);
	
	//takes the exponent bits and shifts right the number of fractional bit to isolate
	//the number of bit for the exponent the shifts left to clear out whats infront the
	//the exponent value and then shift back to finalize it original value
	man = hex >> frac_bit_n;
	man = man << (32-expo_bit_k);
	man = man >> (32-expo_bit_k);
	E = get_E(man, expo_bit_k);
	
	//takes the signed bit number and isolates it but shifting the fractional number
	//to the right then shits the exponent bits to the right to isolate the signed 
	//bit and shits lesf to clear any bits infront it then shifting back to finaliize 
	//its original value.
	S = hex >> frac_bit_n;
	S = S >> expo_bit_k;
	S = (S << 31) >> 31;

	//using logical operations for testing purposes. if the temp results with all zeros
	// that means that the value was previously with all one's.
	unsigned int temp = man ^ 0xffffffff;
	temp= temp << (32 - expo_bit_k);
	temp = temp >>(32 -expo_bit_k);
	
	//in order to determined that if the exponent contains all zeros, we need to invert
	//the binary representation of the exponent so that when its XOR with all ones
	// assuming that the binary was all zeros and by inverting it became all one,
	// with the XOR we will obtatin a all zeros representation meaning that inface that
	//factional values was consist of all zeros. 
	unsigned int zeros = ~man;
	zeros  = zeros ^ 0xffffffff;
	zeros = zeros << (32 - expo_bit_k);
	zeros = zeros >> ( 32 - expo_bit_k);
	//zeros
	if(zeros== 0 && frac == 0)
	{
		printf("Zero\n\n");
	}	
	//this will be a dinormalized number
	else if(zeros == 0 && frac!= 0)
	{
		printf("denormalinez number\n\n");
	}
	//possitive and negative infiniy
	else if(temp == 0 && frac == 0)
	{
	//it will be negative infinity if the signed # is anything but 0
		if(S != 0)
		{
			printf("-inf\n\n");
		}
	//it will be negative infinity if the signed # is 0
		else
		{ 	
			printf("+inf\n\n");
		}
	}
	//This will be NaN because when the exponet is all one and the fractional bits are none zero.
	else if(temp == 0 && frac != 0)
	{
		printf("NaN\n\n");
	} 
	//else it will be a normalizex values
	else 
	{	
		V = pow(-1, S)*M*pow(2,E);
		printf("%f\n\n", V);
	}
	

	return 0;
}
