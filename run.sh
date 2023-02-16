#!/bin/bash
make
valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=ignore_leaks.txt --log-file=valgrind-out.log ./ms.out debug
< valgrind-out.log grep "==" | cat > valgrind.log
#valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=ignore_leaks.txt --log-file=valgrind-out.txt ./minishell
