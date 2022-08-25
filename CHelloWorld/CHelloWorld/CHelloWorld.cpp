#include <stdio.h>

int main( void ) {
	int length = 0;
	int width = 0;
	int area = 0;

	printf("%s", "Enter the length: ");
	scanf("%d", &length);

	printf("%s", "Enter the width: ");
	scanf("%d", &width);

	area = length * width;

	printf("%s", "Length: ");
	printf("%d",length);
	printf("%s", " Width: ");
	printf("%d", width);
	printf("%s", " Area: ");
	printf("%d", area);

	int div = 0;
	div = length / width;
	printf("%s", " Length divided by width: ");
	printf("%d", div);

	return 0;
}