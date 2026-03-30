#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nope(void)
{
	puts("Nope.");
	exit(1);
}

void good_job(void)
{
	puts("Good job.");
}

int main(void)
{
	char input[31];
	char output[9];
	char tmp[4];
	int i, idx;

	printf("Please enter key: ");
	if (scanf("%23s", input) != 1)
	{
		nope();
	}

	if (input[1] != '2' || input[0] != '4')
	{
		nope();
	}

	fflush(stdin);
	memset(output, 0, 9);
	output[0] = '*';
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

	output[idx] = '\0';

	if (strcmp(output, "********") == 0)
	{
		good_job();
	}
	else
	{
		nope();
	}

	return 0;
}