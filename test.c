#include "menu.h"
#include <stdio.h>
int main(void){
	int c1, c2;
	c1 = horizontalMenu("TITOLO", "0", "1", "2", "3", NULL);
	c2 = verticalMenu("TITOLO", "0", "1", "2","3", NULL);
	
	printf("Choice 1: %d\nChoice 2: %d", c1, c2);
}
