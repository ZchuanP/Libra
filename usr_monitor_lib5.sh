#!/bin/bash
if [ $# -eq 1 ]
then
	input_user=$1
        echo "you will monitor [${input_user}]"
	user=$(who -q)
	user=${user%#*}
	users=($user)
	echo 
	echo "Current user list is:"
	echo "${users[0]} ${users[1]}"
	echo
	flag=0
	until [ $flag -eq 1 ]
	do
		user=$(who -q)
	        user=${user%#*}
	        users=($user) 
		for each in ${users[@]}
		do
			if [ $each = ${input_user} ]
			then
				let "flag++"
			fi
		done
		if [ $flag -eq 0 ]
                then
                        echo "Waiting user [${input_user} ...]"
                        sleep 5
                fi

	done
	echo "${input_user} is log on"
else
	echo "Usage: usr_monitor  username"
fi
