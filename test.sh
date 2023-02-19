#!/bin/bash
> output_ms.txt
> all_valgrinds.log
# Define the command you want to run
testing()
{
  local CMD="$1"

#	minishell_output=$(echo "$CMD" | ./minishell test)
#  minishell_exit_code=$?
  minishell_output=$(echo "$CMD" | valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=ignore_leaks.txt --log-file=valgrind-out.log ./minishell test
< valgrind-out.log grep "==" | cat > valgrind.log | grep -v "Welcome to" | grep -v "")
  # Write the exit code and output to the same file
#  echo "exit code: $minishell_exit_code" >> output_ms.txt
  echo "$minishell_output" >> output_ms.txt
  printf "\n" >> output_ms.txt
  cat valgrind.log >> all_valgrinds.log

}
while IFS= read -r line; do
  testing "$line"
done < minihell.txt

cat all_valgrinds.log | grep lost > all_lost.log
cat all_valgrinds.log | grep alid > inv_read.log
cat all_valgrinds.log | grep SIG > SEGFAULT.log
