#!/bin/bash

for num_procs in 1 2 4 8 16 32 64
do
    echo "num_procs = $num_procs"
    if [ ! -f ~/mandel_omp/output/$@_$num_procs ]; then
        touch ~/mandel_omp/output/$@_$num_procs
        echo "num_procs = $num_procs" >> ~/mandel_omp/output/$@_$num_procs
    fi
    if [ -f ~/mandel_omp/output/$@_$num_procs ]; then
        MAX_REPEAT=$( expr $num_procs \* 2 \> 30 > /dev/null && expr 30 || expr $num_procs \* 2 )
        # echo $MAX_REPEAT
        # continue
        REPEAT=$( expr $MAX_REPEAT + 1 - $( wc -l < ~/mandel_omp/output/$@_$num_procs ) )
        echo Exec plan: $REPEAT
        for (( it=0; it<$REPEAT; it++ ))
        do

            NUM=`~/submission.sh OMP_NUM_THREADS=$num_procs OMP_DYNAMIC=false /work/grupo_e/$@`
            NUM=${NUM::-24}
            echo "Item $NUM"
            while [ ! -f ~/STDIN.o$NUM ]; do sleep 1; done

            cat ~/STDIN.o$NUM >> ~/mandel_omp/output/$@_$num_procs

        done
    fi
done