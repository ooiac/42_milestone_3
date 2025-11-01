# Minishell (42) — Scaffold

Este repositório contém apenas a estrutura e pseudocódigo/comentários para guiar a implementação do Minishell (sem bônus).

Diretórios principais:
- `include/` — headers comentados com interfaces e contratos
- `src/lexer`, `src/parser`, `src/expander`, `src/heredoc` — parsing e expansão
- `src/executor`, `src/redir`, `src/builtins`, `src/env` — execução, redireções, builtins, ambiente
- `src/signals`, `src/utils`, `src/ast` — sinais, utilitários e AST

Makefile atual não compila (apenas imprime mensagem) até que as funções sejam implementadas.

Divisão de trabalho sugerida: ver `WORK_SPLIT.txt`.
