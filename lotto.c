//Reyan Jaimon
//C15487408
//DT228-1
//Assignment 2

#include <stdio.h>
#include <stdlib.h>
#define SIZE 6        // Size of the array as only 6 numbers are entered.
#define MAXOUT 43     // For Frequency use when displaying the numbers.
#define ARRAYSIZE 500 // Storing the frequency, 500 should be enough.

/*Prototypes*/

//For Option 1
void userNumbersEnter(int*, int*);

//For Option 2
void lottoNumbersDisplay(int*);

//For Option 3
void lottoNumbersSort(int*);

//For Option 4
void lottoWinChk(int*, int*); 

//For Option 5
void frequencyNumberChk(int*, int*);

//For Option 6
void exitMenu();

//Ninja fix for entering the number twice.
int duplicateNumberHandle(int *user_lottonumber);

//Out of bound error fix
void outOfBoundsHandle();

int main(void)
{
	//Main Variables.
	int start; // Used to select from the menu.
	int loop = 0; // To display the menu over and over.
	
	//User error checking select 1 before selecting other options.
	int selectOnefirst = 0;
	
	//Where the user numbers are stored.
	int user_lottonumber[SIZE];
	
	//The winning numbers.
	int winning_numbers[SIZE] = {1,3,5,7,9,11};
	
	//Frequency array storage
	int frequencyChecker[ARRAYSIZE] = {0};
	
	//The loop for the main to be displayed over and over
	//Until the program ends.
	do
	{
		//Printing out the menu. With a nice boarder around it.

		printf("\n***************************************************************************************************************");
		printf("\n* 1. - Enter your numbers in to play.                                                                         *");                                                                                       
		printf("\n* 2. - Display the numbers you enters.                                                                        *");
		printf("\n* 3. - Sort your numbers in an increasing order.                                                              *");
		printf("\n*      (This is mandatory, it will sort the numbers you entered in an increasing order.)                      *");
		printf("\n* 4. - See if you won the lotto!                                                                              *");
		printf("\n* 5. - Display the frequency of the numbers. (Record of times a number has been selected.)                    *");
		printf("\n* 6. - Exit the Lotto Game.                                                                                   *");	
		printf("\n***************************************************************************************************************\n\n");
		
		//Letting the user know to press 1 before pressing 2-5.
		printf("You must complete option 1 from the menu before moving on.");
		
		printf("\n\nPlease select from the menu: ");
		
		//Entering from the menu.
		scanf("%d", &start);
		
		fpurge(stdin); //Clears the buffer of given stream.
		
		//Making sure the user can only select the options from 1-6 from the menu.
		if(start > 6)
		{
			outOfBoundsHandle();
		}
		
		//Calling the function to allow the user to enter the numbers.
		if(start == 1)
		{
			userNumbersEnter(user_lottonumber,frequencyChecker);
			selectOnefirst++;
		}
		
		//Calling the function to show the user entered numbers.
		if(start == 2 && selectOnefirst == 1)
		{			
			lottoNumbersDisplay(user_lottonumber);
		}
	
		//Calling the function to sort the numbers in an increasing order.
		if(start == 3 && selectOnefirst == 1)
		{
			lottoNumbersSort(user_lottonumber);
		}
		
		//Calling the function to see if the user won the lotto.
		if(start == 4 && selectOnefirst == 1)
		{
			lottoWinChk(user_lottonumber,winning_numbers);
		}
		
		//Calling the function to see the frequency of numbers
		if(start == 5 && selectOnefirst == 1)
		{
			frequencyNumberChk(user_lottonumber, frequencyChecker);
			selectOnefirst--;
		}
		
		//Calling the function to exit the program.
		if(start == 6)
		{
			exitMenu();
		}

	}
	while (loop == 0);
	
}

/*Implementing Functions*/

//Getting the users numbers
void userNumbersEnter(int* user_lottonumber, int* frequencyChecker)
{
	//Declaring the Variables.
	int number_checker = 1;
	
	//Resetting the Array to 0.
	for(int i = 0; i < SIZE; i++)
	{
		*(user_lottonumber + i) =0;
	}
	
	//Displaying to the user the information.
	printf("Welcome to the Lotto Game! Time to pick your numbers.\n");
	
	printf("Note: You must pick from 1-42\n\n"); //Telling the user to pick from 1-42.
	
	for(int i = 0; i < SIZE; i++) 
	{
		do
		{ 
			number_checker = 1;
			
			//Telling the user to enter in their 6 numbers.
			printf("\nPlease enter your %d numbers in: ",SIZE);
			scanf("%d", user_lottonumber + i);
			
			fpurge(stdin); //Clears the buffer of given stream.
			
			//Error checking.
			if(duplicateNumberHandle(user_lottonumber) || (!(*(user_lottonumber + i) > 0 && *(user_lottonumber + i) < 43) )) 
			{
				number_checker = 0;
				printf("\nThe number you have selected is either already selected or invalid.\n");
				printf("\nPlease select a number between 1-42 also don't select the same number again.\n");
			}
			
			//Calculating the Frequency.
			if(number_checker == 1) 
			{
				//Checking the numbers entered on against the numbers on the frequencyChecker.
				*(frequencyChecker + *(user_lottonumber + i)) = *(frequencyChecker + *(user_lottonumber + i)) + 1;
			}
			
		}
		 
	    while(!number_checker); //While not 0 run the code.
	
	}
	
}

//Displaying the user entered numbers.
void lottoNumbersDisplay(int *user_lottonumber)
{	
	printf("Here are the numbers that you have selected: \n");
	
	for(int i = 0; i < SIZE; i++)
	{
		printf("%d ",*(user_lottonumber+i));
	}
	
}//End main2()

//Organising the User Lotto numbers.
void lottoNumbersSort(int *user_lottonumber)
{
	//Declaring the Variables.
	int place;
    
    //Sorting using Bubble Sort.
	for(int n = 0; n < SIZE; n++)
	{
		for(int m = n; m < SIZE; m++)
		{
			if(*(user_lottonumber+n) > *(user_lottonumber+m)) //Sorting in an ascending order. 
			{
				place = *(user_lottonumber+n);
				*(user_lottonumber+n) = *(user_lottonumber+m);
				*(user_lottonumber+m) = place;
				
			}
			
		}
		
	}
	
	//Displaying the ordered numbers.
	printf("Here are your numbers ordered: \n");
	
	for(int n = 0; n < SIZE; n++)
	{
		printf("%d ", *(user_lottonumber+n) );
	}
	
}

//Seeing if the user won
void lottoWinChk(int *user_lottonumber, int *winning_numbers)
{
	//Declaring the Variables.
	int matchedNumbers = 0;
	int bonusNum = 42; //Setting the bonus number.
	int bonusCount = 0;
     
    //The counter that checks if the user matches the winning numbers.
	for(int i = 0; i < SIZE; i++)
	{
		for(int c = 0; c < SIZE; c++)
		{
			if(*(user_lottonumber+i) == *(winning_numbers+c))
			{
				matchedNumbers++; //Incrementing.
			}
		}
	}
	
	//The counter that checks if the user has the bonus number
	for(int i = 0; i < SIZE; i++)
	{
		if(*(user_lottonumber) == bonusNum)
		{
			matchedNumbers++; //Incrementing.
		}
	}

    //If 6 numbers match the user wins this.
	if(matchedNumbers == 6)
	{
		printf("Congratulations, You have won the Jackpot!");
	}
	
	//If 5 numbers and the bonus matches, the user wins this.
	if(matchedNumbers == 5 && bonusCount == 1)
	{
		printf("Congratulations, You have won a Car!");
	}
	
	//If 5 numbers match the user wins this.
	if(matchedNumbers == 5)
	{
		printf("Congratulations, You have won a Holiday!");
	}
	
	//If 4 numbers and the bonus matches, the user wins this.
	if(matchedNumbers == 4 && bonusCount == 1)
	{
		printf("Congratulations, You have won a Weekend Away!");
	}
	
	//If 4 numbers match the user wins this.
	if(matchedNumbers == 4)
	{
		printf("Congratulations, You have won a Night Out!");
	}
	
	//If 3 numbers and the bonus matches,c the user wins this.
	if(matchedNumbers == 3 && bonusCount == 1)
	{
		printf("Congratulations, You have won a Cinema Ticket!");
	}
	
	//If the none of the numbers the user entered match, the user doesn't win anything.
	if(matchedNumbers <= 2 || (matchedNumbers == 3 && !bonusCount))
	{
		printf("Hard luck, you have not won anything.");
	}

}

//Frequency of numbers.
void frequencyNumberChk(int *user_lottonumber, int *frequencyChecker)
{	
	//Prints the frequency of each element.
	for(int i = 0; i < MAXOUT; i++)  
	{  
		if(*(frequencyChecker+i) != 0)  
		{  
			printf("Number %d has been selected %d times.\n", i, *(frequencyChecker+i) );  
		}  
	}
	
}

//Exiting the program
void exitMenu()
{
	//Displaying an exit message.
	printf("\nYou have chosen to exit the program. Thanks for playing the Lotto Game!\n");
	
	//Terminating the code.
	exit(0);
	
}

//Error Checking making sure the user doesn't enter the same number in again.
int duplicateNumberHandle(int *user_lottonumber)
{	
    for (int adding = 0; adding < SIZE; adding++) 
    {
		for (int atk = adding + 1; atk < SIZE; atk++) 
		{
			//Checks if the array has any duplicates.
			if (*(user_lottonumber + adding) == *(user_lottonumber + atk) && *(user_lottonumber + atk) != 0) 
			{
				return(1); //If there is a duplicate then return 1.
				
			}
			
		}
		
	}
	
	return(0); //If there is no duplicate return 0.
	
}

//Out of bound error fixer
//
void outOfBoundsHandle()
{
	//Showing the user the problem, in this case if the user doesn't select
	//between 1-6 from the menu then this will show up.
	printf("Invalid Option, please select again and read the instructions carefully!");
	printf("\n-->You are now going to be shown the menu again, please select appropriately.<--\n");
	
}