#!/usr/bin/bash

alpha=abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz
ALPHA=ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ

if [ "$1" = "?" ];
then
	echo -e "\nThe command generates the specified number of copies of the file.\nCopy names are created by adding the next letter/digit to the name of source file, starting with specified letter/digit.\n\ncreate_copies [FILENAME] [NUMBER] [ENUMERATION]\n"
	exit
fi

fname=$1
if [ -z $fname ]
then
	echo 'Error: Parameter [FILENAME] was not entered.'
	echo "Try 'create_copies ?'"
	exit
fi
name=${fname%.*}
ext=${fname##*.}

n=$2
if [ -z $n ]
then
	n=1
fi

enum=$3
if [ -z $enum ]
then
	enum=1
fi

case $enum in
	[a-z])
		for (( i=0; i < $n; ++i)) do
			cp $fname $name$enum.$ext
			enum=$(echo $enum | tr "${alpha:0:26}" "${alpha:1:26}")
		done
		;;
	[A-Z])
		for (( i=0; i < $n; ++i)) do
			cp $fname $name$enum.$ext
			enum=$(echo $enum | tr "${ALPHA:0:26}" "${ALPHA:1:26}")
		done
		;;
	*)
		for (( i=0; i < $n; ++i)) do
			cp $fname $name$enum.$ext
			enum=$(($enum + 1))
		done
		;;
esac
