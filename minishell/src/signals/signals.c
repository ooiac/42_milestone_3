/* ************************************************************************** */
/*   signals.c - Configuração de sinais (pseudocódigo)                         */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
setup_signals_prompt():
  SIGINT -> interrompe linha atual (readline), imprime nova linha, status=130
  SIGQUIT -> ignorar

setup_signals_exec():
  SIGINT -> default (propaga para processos filhos)
  SIGQUIT -> default

setup_signals_heredoc():
  SIGINT -> abortar heredoc e retornar erro
*/
