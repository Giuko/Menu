#define _CRT_SECURE_NO_WARNINGS			//Only for VS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdarg.h>

#ifdef _WIN32
#define CLRSCR system("cls")			//A function to clear the screen (WINDOWS)
#endif
#include <conio.h>

#ifdef __unix__
#define CLRSCR system("clear")			//A function to clear the screen (UNIX)
#endif

#define DOWN 80							//Down arrow key code
#define UP 72							//Up arrow key code
#define RIGHT 77						//Right arrow key code
#define LEFT 75							//Left arrow key code
#define ESC 27							//Esc key code
#define ENTER 13						//Enter key code
#define LEN_SCREEN 36					//Lenght of screen
#define SOURCE_CODE "Origine.c"			//The name of the source code

#define MAX_OP 10						//Max number of operation

#define getch _getch					//Only for VS

typedef struct stringArray_s {
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

	for (i = 0; i < (LEN_SCREEN - len) / 2; ++i)
		printf(" ");
	printf("%s", title);

	printf("\n");
	for (i = 0; i < LEN_SCREEN; ++i)
		printf("*");
	printf("\n");
}

//This function print the string for the horizontal function
void horizontalPrint(char string[LEN_SCREEN], int op, int selectedOp) {
	if (op == selectedOp)
		printf("[  %s  ]", string);
	else
		printf("   %s   ", string);
}

//This function print the string for the vertical function
void verticalPrint(char string[LEN_SCREEN], int op, int selectedOp) {
	int len = strlen(string), i;
	for (i = 0; i < (LEN_SCREEN - len) / 2; ++i)
		printf(" ");
	if (op == selectedOp)
		printf("\b\b[ %s ]\n", string);
	else
		printf("%s\n", string);
}

//This function manages the arrow input for the menu selection
int horizontalArrowSelection(int keyCode, int selectedOp, int num_op) {
	if (keyCode == LEFT)
		if (selectedOp != 0)
			selectedOp -= 1;
	if (keyCode == RIGHT)
		if (selectedOp != num_op)
			selectedOp += 1;
	return selectedOp;
}

//This function manages the arrow input for the menu selection
int verticalArrowSelection(int keyCode, int selectedOp, int num_op) {
	if (keyCode == UP)
		if (selectedOp != 0)
			selectedOp -= 1;
	if (keyCode == DOWN)
		if (selectedOp != num_op)
			selectedOp += 1;
	return selectedOp;
}

//This function manages the input for the horizontal function
int horizontalInputKeyPress(int* selectedOp, int previousKeyCode, int num_op) {
	int keyCode = 0;
	int previousSelectedOp = *selectedOp;
	do {
		//This is true only if we are in the main menu
		keyCode = getch();
		if (keyCode == 224) {
			keyCode = getch();
			*selectedOp = horizontalArrowSelection(keyCode, *selectedOp, num_op);
		}
		if(keyCode == ENTER)
			return keyCode;
		
		if (previousSelectedOp == num_op && keyCode == RIGHT) {
			keyCode = 0;
		}
		if (previousSelectedOp == 0 && keyCode == LEFT)
			keyCode = 0;
	} while ((keyCode != RIGHT) && (keyCode != LEFT));
}

//This function manages the input for the vertical function
int verticalInputKeyPress(int* selectedOp, int previousKeyCode, int num_op) {
	int keyCode = 0;
	int previousSelectedOp = *selectedOp;
	do {
		//This is true only if we are in the main menu
		keyCode = getch();
		if (keyCode == 224) {
			keyCode = getch();
			*selectedOp = verticalArrowSelection(keyCode, *selectedOp, num_op);
		}
		if(keyCode == ENTER)
			return keyCode;
			
		if (previousSelectedOp == num_op && keyCode == DOWN) {
			keyCode = 0;
		}
		if (previousSelectedOp == 0 && keyCode == UP)
			keyCode = 0;
	} while ((keyCode != DOWN) && (keyCode != UP));
}

//The main horizontal function
int horizontalMenu(char title[LEN_SCREEN], const char *op, ...) {
	int i, num_op = 0;
	unsigned char c;
	FILE* fp;
	char buffer[LEN_SCREEN];
	stringArray_t operations[MAX_OP];
	
	//char* string;
	va_list args;

	va_start(args, op);
	
	while (op && num_op < MAX_OP) {
		puts(op);
		strcpy(operations[num_op].string, op);
		op = va_arg(args, char*);
		num_op++;
	}

	int selectedOp = 0;
	while(1) {
		c = 0;
		titlePrint(title);
		for (i = 0; i < num_op; i++) {
			horizontalPrint(operations[i].string, i, selectedOp);
		}
		c = horizontalInputKeyPress(&selectedOp, c, num_op - 1);

		if (c == ENTER) {
			return selectedOp;
		}
	}
}

//The main vertical function
int verticalMenu(char title[LEN_SCREEN], const char *op, ...) {
	int i, num_op = 0;
	unsigned char c;
	FILE* fp;
	char buffer[LEN_SCREEN];
	stringArray_t operations[MAX_OP];
	
	//char* string;
	va_list args;

	va_start(args, op);
	
	while (op && num_op < MAX_OP) {
		puts(op);
		strcpy(operations[num_op].string, op);
		op = va_arg(args, char*);
		num_op++;
	}

	int selectedOp = 0;
	while(1) {
		c = 0;
		titlePrint(title);
		for (i = 0; i < num_op; i++) {
			verticalPrint(operations[i].string, i, selectedOp);
		}
		c = verticalInputKeyPress(&selectedOp, c, num_op - 1);

		if (c == ENTER) {
			return selectedOp;
		}
	}
}

