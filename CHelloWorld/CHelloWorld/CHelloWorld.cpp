#include <stdio.h>
bool boolean(int x, int y);

int main( void ) {
	//variables
	int length, width, area, div = 0;


	//get data
	printf("%s", "Enter the length: ");
	scanf("%d", &length);

	printf("%s", "Enter the width: ");
	scanf("%d", &width);

	area = length * width;
	div = length / width;

	//output data
	printf("%s","Length: ");
	printf("%d", length);

	printf("%s", " Width: ");
	printf("%d", width);

	printf("%s", " Area: ");
	printf("%d", area);

	printf("%s", " Length divided by width: ");
	printf("%d", div);

	if (length != width) {
		printf(" \n %d is not equal to %d", length, width);
	}
	else printf(" \n %d is equal to %d", length, width);
	
	for (int i = 0; i < 10; i++) {
		printf("this is working \n");
	}
	int n = 0;
	while (n < 10) {
		printf("this is also working\n");
		n++;
	}

	int x = boolean(1, 4);
	printf("%d", x);
	return 0;
}//end of main

bool boolean(int x, int y) {
	if (x < y)return 1;
	else return 0;
}