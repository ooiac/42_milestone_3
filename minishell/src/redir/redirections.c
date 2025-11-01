/* ************************************************************************** */
/*   redirections.c - Aplicação de redireções (pseudocódigo)                   */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
apply_redirections(cmd):
  saved_stdin = dup(STDIN_FILENO)
  saved_stdout = dup(STDOUT_FILENO)
  for r in cmd.redirs:
    if r.type == '<':
      fd = open(r.target, O_RDONLY)
      dup2(fd, STDIN_FILENO); close(fd)
    if r.type == '>':
      fd = open(r.target, O_WRONLY|O_CREAT|O_TRUNC, 0644)
      dup2(fd, STDOUT_FILENO); close(fd)
    if r.type == '>>':
      fd = open(r.target, O_WRONLY|O_CREAT|O_APPEND, 0644)
      dup2(fd, STDOUT_FILENO); close(fd)
    if r.type == '<<':
      fd = obter_fd_heredoc_preparado(r)
      dup2(fd, STDIN_FILENO); close(fd)
  return saved_stdin, saved_stdout

restore_stdio(saved_stdin, saved_stdout):
  dup2(saved_stdin, STDIN_FILENO); close(saved_stdin)
  dup2(saved_stdout, STDOUT_FILENO); close(saved_stdout)
*/
