#include "lexer.h"
#include <stdio.h>

void print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("[%d: \"%s\"]\n", lst->type, lst->value);
		lst = lst->next;
	}
}

int main(void)
{
	const char *line = "echo 'Olá $USER' | cat >> out.txt";
	t_token *tokens = lexer_tokenize(line);
	print_tokens(tokens);
	token_clear(&tokens);
	return 0;
}
