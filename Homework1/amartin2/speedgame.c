#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#define MAXSIZE 9
#define WORDMAXSIZE 10

//Using typedef in order to define a type bool function which returns either true or false.
typedef  enum {false, true} bool; 

//The porpuse of this program is to make a game that measures the speed of how fast the user can type.


/*Using a bool function that takes a word from the user and compares with the one in the array and 
returns true if they match or false if the word is not the same.*/

bool is_it_amatch(char word_inlist[], char match[])
{
	if(strncmp(word_inlist,match,WORDMAXSIZE)==0)
	return true;
	else
	return false;
}

int main()
{
	char words[MAXSIZE][WORDMAXSIZE]={"The","quick","brown","fox","jumps","over","the","lazy","dog"}; 

	printf("Type the following words:\n");
	char word_guessed[WORDMAXSIZE];
	
	struct timeval  starttime, endtime, totaltime;
		
	int i;
	
	//Using gettimeofday to seed in time in which the user start tiping to initialize the time.
	gettimeofday(&starttime, NULL);
	
	srand(starttime.tv_usec);//%8
	
	//in order for the program to ramdomly display each word without displaying it twice I needed a 
	//forloop that could display each word in desending order.
	for(i =MAXSIZE-1; i>=0; --i)
	{
		int x;
		bool correct;
		do
		{
			//These if else statements are used to produce a ramdon permutation in which each word is only
			//displayed once.
			if(i!=0)  x = rand()%i+1;
			else x = 0;
		
			//Displaying the word as is ramdomly selected and asking the used to type that word
			printf("Word # %d %s:", 9-i,words[x]);
			scanf("%s", word_guessed);

			//in order to not have problems at compile time and not change the value of the bool function
			//i need to create a bool veriable that would contained that variable to test for errors 
			correct = is_it_amatch(words[x],word_guessed);

			//if the words did not match and correct was false it would return an error statement
			//else if the word did match then to prevent the ramdom permutation to generate the word twice
			//i need to swap/copy the word rand selected and copying it into the last word in the array.
			//that way when the forloop decreased by one from the top dow, i then could store the used word
			//into that space of the array that way the range of the modulous would and never touch it.
			if(!correct)
				printf("Incorrect, try again\n");
			else
			{
				strncpy(words[x],words[i],strlen(words[i])+1);

			}
		}
			while(!correct);
	}
	
	//Using gettimeofday seeing in the time in which the for loop end to obtain an end time.
	gettimeofday(&endtime, NULL);

	//while using timersub i needed to get the total time that the user took to type all the word so i used times 
	//we used for in gettimeofday. I subtracted the starting time form the ending time in order to get a total time
	timersub(&endtime,&starttime,&totaltime);
	
	printf("Your total time was: %ld sec\n", totaltime.tv_sec);
  return 0;
}
