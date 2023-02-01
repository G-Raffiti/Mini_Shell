#!/bin/bash
valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=valgrind_ignore_leaks.txt --log-file=valgrind-out.txt ./mini_shell;
<valgrind-out.txt grep "==" | cat > valgrind.log