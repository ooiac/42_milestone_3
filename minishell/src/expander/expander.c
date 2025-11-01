/* ************************************************************************** */
/*   expander.c - Expansão de variáveis e remoção de quotes (pseudocódigo)    */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
ast_expand(node, env):
  if node == NULL: return OK
  if node é PIPE:
    expand(left); expand(right)
    return
  if node é CMD:
    para cada argv[i]:
      argv[i] = expand_word(argv[i], env)
    para cada redir:
      redir.target = expand_word(redir.target, env)  // exceto se veio de heredoc com no-quote

expand_word(word, env):
  resultado = ""
  modo = NORMAL
  i = 0
  while i < len(word):
    if '\'' e modo != DQUOTE: alterna SQUOTE (sem expansão dentro)
    else if '"' e modo != SQUOTE: alterna DQUOTE (expansão permitida)
    else if '$' e modo != SQUOTE:
      ler nome da variável ou '?'
      append valor (ou "")
    else append caractere
  retornar resultado
*/
