#!/bin/bash
# file.sh: a sample shell script to demonstrate the concept of Bash shell functions
# define usage function
usage(){
	echo "Usage: $0 filename"
	exit 1
}
 
# define is_file_exits function
# $f -> store argument passed to the script
is_file_exits(){
	local f="$1"
	[[ -f "$f" ]] && return 0 || return 1
}
# invoke  usage
# call usage() function if filename not supplied
[[ $# -eq 0 ]] && usage
 
# Invoke is_file_exits
if ( is_file_exits "$1" )
then
 echo "File found"
 a=$(gcc jagaja.c 2>&1)
 if [ -z "$a" ]
 then
  b=$(git commit -m "$2" 2>&1)
  echo "GIT TEATAB:"
  echo $b
  ./a.out
 else
  echo "KOMPILEERUMINE EBAÕNNESTUS:"
  echo $a
 fi
else
 echo "File not found"
fi
