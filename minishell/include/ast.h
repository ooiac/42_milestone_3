/* ************************************************************************** */
/*   ast.h - nós da AST (comentado)                                            */
/* ************************************************************************** */

#ifndef AST_H
#define AST_H

/*
Nós esperados:
  - Nó comando: argv[], redirs[]
  - Nó pipeline: left | right

// typedef struct s_redir {
//   int   type;       // <, >, >>, <<
//   char *target;     // arquivo ou delimitador do heredoc
// } t_redir;

// typedef struct s_cmd {
//   char   **argv;
//   t_redir *redirs;  // array ou lista
// } t_cmd;

// typedef struct s_ast {
//   int          kind;     // CMD ou PIPE
//   t_cmd        cmd;      // válido se kind==CMD
//   struct s_ast *left;    // válido se kind==PIPE
//   struct s_ast *right;   // válido se kind==PIPE
// } t_ast;

Operações (notas):
  - ast_from_tokens(tokens)
  - ast_free(tree)
*/

#endif /* AST_H */
