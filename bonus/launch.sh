i=$1

if [ -f $i ]
then
    echo "./launch.sh [nb_players]"
elif [ $i -le 0 ]
then
    echo "nb_players must be positive"
else
    while [ $i -gt 0 ]
    do
	#	echo $i
        ./lemipc `pwd` $((RANDOM % 5 + 1)) &
	((i-=1))
	sleep 0.02
    done
    
fi
