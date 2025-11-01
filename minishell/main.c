/* ************************************************************************** */
/*   main.c - esqueleto do loop principal (pseudocódigo)                       */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
int main(int argc, char **argv, char **envp)
{
	// (Nota: apenas guia; não é implementação real)
	// t_env *env = env_from_environ(envp);
	// int    last_status = 0;
	// setup_signals_prompt();
	// while (true) {
	//   char *line = readline("minishell$ ");
	//   if (line == NULL) { // EOF (Ctrl-D)
	//     write(1, "exit\n", 5);
	//     break;
	//   }
	//   if (is_blank_str(line)) { free(line); continue; }
	//   add_history(line);
	//   int lex_err=0, parse_err=0, exp_err=0;
	//   t_token *tks = lex_line(line, &lex_err);
	//   free(line);
	//   if (lex_err) { report_lex_error(); token_free_list(tks); continue; }
	//   if (!syntax_check(tks, NULL)) { syntax_error(); token_free_list(tks); continue; }
	//   t_ast *ast = parse_tokens(tks, &parse_err);
	//   token_free_list(tks);
	//   if (parse_err) { report_parse_error(); ast_free(ast); continue; }
	//   if (ast_expand(ast, env, &exp_err) != 0) { report_expand_error(); ast_free(ast); continue; }
	//   last_status = execute_ast(ast, &env);
	//   ast_free(ast);
	// }
	// env_free(env);
	// return last_status;
}
*/
