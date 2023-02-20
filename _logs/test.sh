> __all_valgrinds.log
cd ..
make
cd ./_logs
rm minishell
cp ../minishell ./

testing()
{
    local CMD="$1"
    STD=$(echo "$CMD" | valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=__ignore_leaks.txt --log-file=__valgrind-out.log ./minishell test)
    printf "\n################################################################################################################################################################################################################## \n\n CMD -> $CMD \n" > __valgrinds.log
    < __valgrind-out.log grep "==" | cat >> __valgrinds.log
    printf "\n CMD -> $CMD \n " >> __valgrinds.log

    sed -i '/blocks are still reachable/c\REACHABLE' __valgrinds.log
    sed -i '/embedded gdbserver/c\SUPPR' __valgrinds.log
    sed -i '/ THIS PROCESS USING /c\SUPPR' __valgrinds.log
    sed -i '/WARNING: new redirection conflicts with existing/c\SUPPR' __valgrinds.log
#    sed -i '/ Open file descriptor /c\OPEN' __valgrinds.log
#    sed -i '/ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)/c\SUPPR' __valgrinds.log
    sed -i '/REACHABLE/,/== $/d' __valgrinds.log
    sed -i '/SUPPR/,/== $/d' __valgrinds.log
#    sed -i '/OPEN/,/== $/d' __valgrinds.log

    cat __valgrinds.log >> __all_valgrinds.log
}

counter=0
while IFS= read -r line; do
  testing "$line"
done < minihell.txt

wait

cat __all_valgrinds.log | grep lost > __all_lost.log
cat __all_valgrinds.log | grep alid > __inv_read.log
cat __all_valgrinds.log | grep SIG > __SEGFAULT.log
