/* ************************************************************************** */
/*   heredoc.c - Preparação de heredocs (pseudocódigo)                         */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
setup_heredocs_for_ast(root, env):
  percorrer nós CMD da AST:
    para cada redir do tipo HEREDOC:
      criar pipe ou arquivo temporário
      ler linhas até delimitador
        - se delimitador sem quotes: expandir $VAR durante leitura
        - se delimitador com quotes: não expandir
      escrever conteúdo no fd
      salvar fd para usar na execução
  lidar com SIGINT para cancelar heredoc (limpeza e status adequado)
*/
