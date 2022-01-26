/*
  Giuseppe Maganuco Francesco Vincenzo's property
*/
#define _CRT_SECURE_NO_WARNINGS			//Only for VB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdarg.h>

#ifdef _WIN32
	    #define CLRSCR system("cls")	//A function to clear the screen (WINDOWS)
#endif

#ifdef __unix__
	    #define CLRSCR system("clear")	//A function to clear the screen (UNIX)
#endif

#define DOWN 80							//Down arrow key code
#define UP 72							//Up arrow key code
#define ESC 27							//Esc key code
#define ENTER 13						//Enter key code
#define LEN_SCREEN 36					//Lenght of screen
#define SOURCE_CODE "Origine.c"			//The name of the source code
#define EXIT_CODE 300					//Code for close the program
		
#define MAX_OP 5						//Max number of operation

typedef struct stringArray_s{
	char string[LEN_SCREEN];
}stringArray_t;

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
void centeredPrint(char string[LEN_SCREEN], int op, int selectedOp) {
	int len = strlen(string), i;
	for (i = 0; i < (LEN_SCREEN - len) / 2; ++i)
		printf(" ");
	if (op == selectedOp)
		printf("\b\b[ %s ]\n", string);
	else
		printf("%s\n", string);
}

//This function print a subscript
void subscriptInformation(){
	printf("\n\n(Press esc to return)\n");
}

//This function manages the arrow input for the menu selection
int arrowSelection(int keyCode, int selectedOp, int num_op) {
	if (keyCode == UP)
		if (selectedOp != 0)
			selectedOp -= 1;
	if (keyCode == DOWN)
		if (selectedOp != num_op)
			selectedOp += 1;
	return selectedOp;
}

//This function manages the input
int inputKeyPress(int *selectedOp, int previousKeyCode, int num_op) {
	int keyCode = 0;
	int previousSelectedOp = *selectedOp;
	do {
		//This is true only if we are in the main menu
		if (previousKeyCode != ENTER) {
			keyCode = getch();
			if (keyCode == 224) {
				keyCode = getch();
				*selectedOp = arrowSelection(keyCode, *selectedOp, num_op);
			}
		}
		else {
			do {
				keyCode = getch();
				if (keyCode == ESC)
					keyCode = EXIT_CODE;
			} while (keyCode != EXIT_CODE);
		}
		if(previousSelectedOp == num_op && keyCode == DOWN){
			keyCode = 0;
		}
		if(previousSelectedOp == 0 && keyCode == UP)
			keyCode = 0;
	} while ((keyCode != DOWN) && (keyCode != UP) && (keyCode != ENTER) && (keyCode != EXIT_CODE));
	return keyCode;
}

//The main function
int menu(char title[LEN_SCREEN], char op0[LEN_SCREEN], char op1[LEN_SCREEN], 
char op2[LEN_SCREEN], char op3[LEN_SCREEN], char op4[LEN_SCREEN]) {
	int i, num_op = 0;
	unsigned char c;
	FILE* fp;
	char buffer[LEN_SCREEN];
	stringArray_t operations[MAX_OP];
	char string[LEN_SCREEN];
	
	strcpy(operations[0].string, op0);
	strcpy(operations[1].string, op1);
	strcpy(operations[2].string, op2);
	strcpy(operations[3].string, op3);
	strcpy(operations[4].string, op4);
	for (i = 0; i < MAX_OP; ++i)
		if(operations[i].string[0] != '\0'){
			num_op++;		
		}else
			break;
	int selectedOp = 0;
	do{
		c = 0;		 
		titlePrint(title);
		for(i = 0; i < num_op; i++){
			centeredPrint(operations[i].string, i, selectedOp); 
		}
		 c = inputKeyPress(&selectedOp, c, num_op-1);

		 if (c == ENTER) {
			return selectedOp;
		 }
	 } while (c != EXIT_CODE);
}
