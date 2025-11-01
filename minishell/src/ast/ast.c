/* ************************************************************************** */
/*   ast.c - utilidades da AST (pseudocódigo)                                  */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
ast_free(node):
  if node == NULL: return
  if node.kind == PIPE: ast_free(node.left); ast_free(node.right)
  if node.kind == CMD: free argv e redirs
  free(node)
*/
