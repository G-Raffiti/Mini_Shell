#!/bin/bash
> output_ms.txt
> all_valgrinds.log
cd ..
make
cd _logs
cp ../minishell ./

# Define the command you want to run
testing()
{
  local CMD="$1"

#	minishell_output=$(echo "$CMD" | ./minishell test)
#  minishell_exit_code=$?
VAR=$(echo "$CMD" | valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=ignore_leaks.txt --log-file=valgrind-out.log ./minishell test
< valgrind-out.log grep "==" | cat > valgrind.log | grep -v "Welcome to" | grep -v "")
  # Write the exit code and output to the same file
#  echo "exit code: $minishell_exit_code" >> output_ms.txt
 echo "$CMD" >> all_valgrinds.log
  cat valgrind.log >> all_valgrinds.log
 echo "$CMD" >> all_valgrinds.log
 echo "" >> all_valgrinds.log

}

counter=0
while IFS= read -r line; do
  testing "$line" &
    # Increment the process counter
    ((counter++))

    # If we have reached the maximum number of processes, wait for them to finish
    if [ $counter -eq 4 ]; then
      wait
      # Reset the counter
      counter=0
    fi
done < minihell.txt

wait

counter=0
while IFS= read -r line; do
  testing "$line" &
    # Increment the process counter
    ((counter++))

    # If we have reached the maximum number of processes, wait for them to finish
    if [ $counter -eq 4 ]; then
      wait
      # Reset the counter
      counter=0
    fi
done < minihell2.txt

wait

counter=0
while IFS= read -r line; do
  testing "$line" &
    # Increment the process counter
    ((counter++))

    # If we have reached the maximum number of processes, wait for them to finish
    if [ $counter -eq 4 ]; then
      wait
      # Reset the counter
      counter=0
    fi
done < minihell3.txt

wait


wait
cat all_valgrinds.log | grep lost > all_lost.log
cat all_valgrinds.log | grep alid > inv_read.log
cat all_valgrinds.log | grep SIG > SEGFAULT.log
