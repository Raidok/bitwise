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
if ( is_file_exits "$1" ) # if the file (argument 1) didn't exist
then
 a=$(gcc jagaja.c 2>&1) # 2>&1 catches both, STDOUT and STDERR
 if [ -z "$a" ]	# check if the variable is set, returns true for an empty string too
 then
  b=$(./a.out) # runs the compiled code
  c=$(git commit -a -m "$b
$2" 2>&1) # commits with output message followed by argument 2 from the command line
  echo " --- GIT TEATAB --- "
  echo $c # git output
 else
  echo " --- KOMPILEERUMINE EBAÕNNESTUS ---"
  echo $a #if the compilaton failed, it outputs all
 fi
else
 echo "File not found"
fi
