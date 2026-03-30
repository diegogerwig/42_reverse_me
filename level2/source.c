#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char input[24];
	char output[9];
	char tmp[4];
	int i, idx;

	printf("Please enter key: ");
	if (scanf("%23s", input) != 1)
	{
		puts("Nope.");
		exit(1);
	}

	if (input[1] != '0' || input[0] != '0')
	{
		puts("Nope.");
		exit(1);
	}

	memset(output, 0, 9);
	output[0] = 'd';
	i = 2;
	idx = 1;

	while (strlen(output) < 8 && i < (int)strlen(input))
	{
		tmp[0] = input[i];
		tmp[1] = input[i + 1];
		tmp[2] = input[i + 2];
		tmp[3] = '\0';
		output[idx] = (char)atoi(tmp);
		i += 3;
		idx += 1;
	}

	if (strcmp(output, "delabere") == 0)
		puts("Good job.");
	else
	{
		puts("Nope.");
		exit(1);
	}

	return 0;
}