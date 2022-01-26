/*
  Giuseppe Maganuco Francesco Vincenzo's property
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#ifdef _WIN32
	    #define CLRSCR system("cls")	//A function to clear the screen (WINDOWS)
#endif

#ifdef __unix__
	    #define CLRSCR system("clear")	//A function to clear the screen (UNIX)
#endif

#define DOWN 80					//Down arrow key code
#define UP 72					//Up arrow key code
#define ESC 27					//Esc key code
#define ENTER 13				//Enter key code
#define LEN_SCREEN 36			//Lenght of screen
#define SOURCE_CODE "Origine.c"	//The name of the source code
#define EXIT_CODE 300			//Code for close the program

//This function print the title formatted
void titlePrint(char title[LEN_SCREEN]) {
	int len = strlen(title), i;
	
	CLRSCR;
	
	printf("\n");
	for (i = 0; i < LEN_SCREEN; ++i)
		printf("*");
	printf("\n");
	
	for (i = 0; i < (LEN_SCREEN-len)/2; ++i)
		printf(" ");
	printf("%s", title);

	printf("\n");
	for (i = 0; i < LEN_SCREEN; ++i)
		printf("*");
	printf("\n");
}

//This function print the string centered
void centeredPrint(char title[LEN_SCREEN]) {
	int len = strlen(title), i;
	for (i = 0; i < (LEN_SCREEN - len) / 2; ++i)
		printf(" ");
	printf("%s", title);
}

//This function print a subscript
void subscriptInformation(){
	printf("\n\n(Press esc to return)\n");
}

//This function manages the arrow input for the menu selection
int arrowSelection(int keyCode, int selectedOp) {
	if (keyCode == UP)
		if (selectedOp != 0)
			selectedOp -= 1;
	if (keyCode == DOWN)
		if (selectedOp != 4)
			selectedOp += 1;
	return selectedOp;
}


//This function manages the input
int inputKeyPress(int *selectedOp, int previousKeyCode) {
	int keyCode = 0;
	int previousSelectedOp = *selectedOp;
	do {
		//This is true only if we are in the main menu
		if (previousKeyCode != ENTER) {
			keyCode = getch();
			if (keyCode == 224) {
				keyCode = getch();
				*selectedOp = arrowSelection(keyCode, *selectedOp);
			}
		}
		else {
			do {
				keyCode = getch();
				if (keyCode == ESC)
					keyCode = EXIT_CODE;
			} while (keyCode != EXIT_CODE);
		}
		if(previousSelectedOp == 4 && keyCode == DOWN){
			keyCode = 0;
		}
		if(previousSelectedOp == 0 && keyCode == UP)
			keyCode = 0;
	} while ((keyCode != DOWN) && (keyCode != UP) && (keyCode != ENTER) && (keyCode != EXIT_CODE));
	return keyCode;
}


//The main function
int main(void) {
	unsigned char c;
	FILE* fp;
	char buffer[LEN_SCREEN];
	int selectedOp = 0;
	 do{
		 c = 0;		 
		 titlePrint("Menu");
		 
		 if (selectedOp == 0)
			centeredPrint("[ Play ]\n"); 
			//centeredPrint("->Play  \n"); Version: 1.1
		 else
			 centeredPrint("Play\n");

		 if (selectedOp == 1)
			 centeredPrint("[ Instruction ]\n"); 
			 //centeredPrint("->Instruction  \n"); Version: 1.1
		 else
			 centeredPrint("Instruction\n");

		 if (selectedOp == 2)
			 centeredPrint("[ Credit ]\n");
			 //centeredPrint("->Credit  \n"); Version: 1.1
		 else
			 centeredPrint("Credit\n");

		 if (selectedOp == 3)
			 centeredPrint("[ Code ]\n");
		 //centeredPrint("->Exit  \n"); Version: 1.1
		 else
			 centeredPrint("Code\n"); 

		 if (selectedOp == 4)
			 centeredPrint("[ Exit ]\n");
		 //centeredPrint("->Exit  \n"); Version: 1.1
			 else
			 centeredPrint("Exit\n");

		 c = inputKeyPress(&selectedOp, c);

		 if (c == ENTER) {
			 switch (selectedOp)
			 {
			 case 0:	//PLAY
				 titlePrint("Play");

				 subscriptInformation();
				 break;
			 case 1:	//INSTRUCTION			 
				 titlePrint("Instruction");

				 subscriptInformation();
				 break;
			 case 2:	//CREDIT	 
				 titlePrint("Credit");

				 centeredPrint("The creator: ME\n");

				 subscriptInformation();
				 break;
			 case 3:	//THE CODE
				 titlePrint("THE CODE");

				 centeredPrint("YOU SHITTY THIS IS MY CODE");

				 subscriptInformation();

				 break;
			 case 4:	//EXIT
				 titlePrint("EXIT");
				 c = EXIT_CODE;
			 }

			 if (selectedOp != 4)
				 c = inputKeyPress(&selectedOp, c);
			 else
				 break;

			 if (c == EXIT_CODE)
				 c = 0;
		 }
	 } while (c != EXIT_CODE);
}
