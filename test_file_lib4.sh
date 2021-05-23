#!/bin/bash
clear
echo "input the filename in this folder:"
read filename
file="${filename}.txt"
if [ ! -f "$file" ]; then
	echo "Can't not open the file named ${file}"
	exit
fi
ls -l ${file}
FILESIZE=$(stat -c%s "$file")
echo "size of the file: ${FILESIZE}"
time=0
not_change=0
changed=0
while :
do
	echo "test file's status ..."
	filesize1=$(stat -c%s "$file")
	if [ $FILESIZE == $filesize1 ];
	then
		echo "size not change"
		let "not_change++"
	else
		echo "changed new size: ${filesize1}"
		FILESIZE=${filesize1}
		let "changed++"
		not_change=0
	fi
	let "time++"
	if test $not_change -eq 10  
	then 
		echo "10 times not change"
		exit
	elif test $changed -eq 2 
	then
		echo "had changed 2 times"
		exit
	fi
	sleep 5
done

