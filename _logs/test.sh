
> all_valgrinds.log

testing()
{
    local CMD="$1"
    VAR="##################################################################################################################################################################################################################"
    VAR+=$(echo"")
    VAR+=$(echo"$CMD")
    STD=$(echo "$CMD" | valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=ignore_leaks.txt --log-file=valgrind-out.log ./minishell test)
    VAR+=$(< valgrind-out.log grep "==" | cat)
    VAR+=$(echo"$CMD")
    VAR+=$(echo"")
    echo "$VAR" > valgrinds.log
    sed -i '/blocks are still reachable/c\REACHABLE' valgrinds.log
    sed -i '/== $/c\END' valgrinds.log
    sed -i '/REACHABLE/,/END/d' valgrinds.log
    sed -i 's/END$/-/g' valgrinds.log

    cat valgrinds.log >> all_valgrinds.log
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

cat all_valgrinds.log | grep lost > all_lost.log
cat all_valgrinds.log | grep alid > inv_read.log
cat all_valgrinds.log | grep SIG > SEGFAULT.log
