#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char input[24];
	char output[9];
	char tmp[4];
	int i, idx;
	char *secret= "delabere";

	printf("Please enter key: ");
	if (scanf("%23s", input) != 1)
	{
		puts("Nope.");
		exit(1);
	}

	if (input[0] != '0' || input[1] != '0')
	{
		puts("Nope.");
		exit(1);
	}

	memset(output, 0, 9); 
	output[0] = 'd';	  

	int position_read = 2;   
	int position_escritura = 1; 

	while (strlen(output) < 8 && position_read < (int)strlen(input))
	{
		tmp[0] = input[position_read];
		tmp[1] = input[position_read + 1];
		tmp[2] = input[position_read + 2];
		tmp[3] = '\0'; 

		int codigo_ascii = atoi(tmp);
		output[position_escritura] = (char)codigo_ascii;

		position_read += 3;	
		position_escritura += 1; 
	}

	if (strcmp(output, secret) == 0)
		puts("Good job.");
	else
	{
		puts("Nope.");
		exit(1);
	}

	return 0;
}