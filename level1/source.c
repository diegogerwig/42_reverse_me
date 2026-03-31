#include <stdio.h>
#include <string.h>

int main(void)
{
	char user_input[100];
	char *secret = "__stack_check";

	printf("Please enter key: ");

	scanf("%s", user_input);

	if (strcmp(user_input, secret) == 0)
	{
		printf("Good job.\n");
	}
	else
	{
		printf("Nope.\n");
	}

	return 0;
}