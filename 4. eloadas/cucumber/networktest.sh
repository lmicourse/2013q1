while true; do    
	ping -c 1 8.8.8.8 > /dev/null 2> /dev/null  # ping and discard output
	if [ $? -eq 0 ]; then  # check the exit code
		echo network is up > status.txt # display the output
	else
		echo network is down > status.txt
	fi
done
