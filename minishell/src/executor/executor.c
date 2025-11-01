/* ************************************************************************** */
/*   executor.c - Executor da AST (pseudocódigo)                               */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
execute_ast(node, env):
  if node é PIPE:
    criar pipe()
    pid_left = fork()
    if pid_left == 0:
      setup_signals_exec()
      dup2(pipe[1], STDOUT_FILENO)
      close(pipe[0]); close(pipe[1])
      execute_ast(node.left, env) // tail chama comando
      _exit(status)
    pid_right = fork()
    if pid_right == 0:
      setup_signals_exec()
      dup2(pipe[0], STDIN_FILENO)
      close(pipe[0]); close(pipe[1])
      execute_ast(node.right, env)
      _exit(status)
    close ambos fds
    wait ambos; combinar status (retornar último)
  else if node é CMD:
    se builtin que precisa rodar no pai (cd, export, unset, exit) e sem pipeline:
      apply_redirections()
      run_builtin(argv, env)
      restore stdio
      return status
    senao:
      pid = fork()
      if pid == 0:
        setup_signals_exec()
        apply_redirections(); setup_heredocs_se_existirem()
        se is_builtin(argv[0]): run_builtin e _exit(status)
        else: resolver PATH e execve(argv, envp)
        em caso de falha: imprimir erro e _exit(código)
      wait pid; retornar status
*/
