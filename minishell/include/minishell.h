/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <team>                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 00:00:00 by team              #+#    #+#             */
/*   Updated: 2025/11/01 00:00:00 by team             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/*
PSEUDOCÓDIGO / ESCOPO GERAL

Objetivo:
  Implementar um shell mínimo inspirado no bash (sem bônus), com:
    - Prompt interativo com histórico (readline)
    - Lexing, parsing para AST
    - Expansões ($VAR, $?, remoção de quotes mantendo semântica)
    - Execução de comandos simples e pipelines com redireções (<, >, >>, <<)
    - Builtins: echo (-n), cd, pwd, export, unset, env, exit
    - Gestão de variáveis de ambiente
    - Sinais: Ctrl-C, Ctrl-\, Ctrl-D (EOF)

Loop principal (alto nível):
  while (true):
    instalar handlers de sinal próprios do prompt
    line = readline(prompt)
    se line == NULL: tratar EOF (exit com último status)
    se line vazia: continue
    tokens = lexer(line)
    se erro léxico: reportar e continue
    se !syntax_ok(tokens): reportar e continue
    ast = parse(tokens)
    se erro parse: reportar e continue
    ast = expand(ast, env)
    se erro expansão: reportar e continue
    status = execute(ast, env)
    atualizar $? com status
    limpar estruturas (tokens, ast)

Estruturas (conceitual):
  - t_env: lista ligada (name, value)
  - t_token: tipo (WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC, SQUOTE, DQUOTE, …), str
  - t_ast: comandos e nós de pipeline; cada comando tem argv[], redirs[], heredocs
  - t_redir: tipo e alvo (arquivo ou delimitador de heredoc)

Erros / edge cases:
  - quotes não fechadas -> erro de sintaxe
  - múltiplas redireções aninhadas
  - heredoc com sinais e expansão de variáveis conforme regra (sem expansão com quotes no delimitador)
  - variáveis não definidas -> expandem para string vazia
  - comandos não encontrados -> exit code 127

Integração:
  - parser/expander não chamam fork/exec; executor não faz parsing
  - builtins em processo pai quando necessário (cd, export, unset, exit)
  - status global atualizado via executor
*/

/* Observação: As funções e tipos abaixo são rascunhos e estão documentados
   apenas como comentários para orientar a implementação futura. */

/* includes do sistema (como comentário para referência)
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
*/

/* Encaminhamentos de tipos (comentados)
// typedef struct s_env    t_env;
// typedef struct s_token  t_token;
// typedef struct s_ast    t_ast;
*/

/* Protótipos (comentados)
// int  ms_run_loop(t_env **env);
// int  ms_execute_ast(t_ast *root, t_env **env);
*/

#endif /* MINISHELL_H */
