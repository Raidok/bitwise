#!/bin/bash
# a shell script which copiles a file with gcc and if no errors exist, it commits it to git with the output gotten from running the code
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
 a=$(gcc jagaja.c 2>&1)
 if [ -z "$a" ]
 then
  b=$(./a.out 2>&1)
  echo $b$2
  c=$(git commit -a -m "$b$2" 2>&1)
  echo " --- GIT TEATAB --- "
  echo $c
 else
  echo " --- KOMPILEERUMINE EBAÕNNESTUS ---"
  echo $a
 fi
else
 echo "File not found"
fi
