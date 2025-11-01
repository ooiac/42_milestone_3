/* ************************************************************************** */
/*   lexer.c - Lexer: transforma linha em tokens (pseudocódigo)               */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
lex_line(line):
  init tokens = NULL
  i = 0
  while i < len(line):
    pular espaços
    se fim: break
    se começa com operador (|, <, >):
      detectar >> ou <<
      criar token operador
      avançar
      continue
    else:
      ler palavra até espaço ou operador, respeitando quotes
        - se quote simples: copiar até próxima ' (erro se não fechar)
        - se quote dupla: copiar até próxima " (erro se não fechar)
      criar token TK_WORD com conteúdo bruto (com quotes)
  retornar lista de tokens ou erro
*/
