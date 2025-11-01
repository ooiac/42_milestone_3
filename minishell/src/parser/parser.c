/* ************************************************************************** */
/*   parser.c - Parser: tokens -> AST (pseudocódigo)                           */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
parse_tokens(tokens):
  if tokens começam/terminam com PIPE -> erro sintaxe
  dividir pela menor precedência (|)
  se há PIPE:
    left = parse_tokens(tokens antes do primeiro |)
    right = parse_tokens(tokens depois do primeiro |)
    return AST_PIPE(left, right)
  senão:
    construir nó comando:
      argv = []
      redirs = []
      percorrer tokens:
        se token é redir (<, >, >>, <<):
          pegar próximo token WORD como alvo (erro se faltar)
          adicionar em redirs
        else if token é WORD:
          argv.push(token.value)
      se argv vazio e tem redirs -> comando vazio permitido? (definir regra)
      return AST_CMD(argv, redirs)
*/
