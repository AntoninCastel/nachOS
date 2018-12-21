#!/bin/bash
#nachos_thread.sh

#Le but de ce script est tester les threads nachos 
#avec des préemption différentes.
#Entrer en parametre le programme de test (sans ".c")

if [ ! -z "$1" ]; then
	for i in `seq 1 10`;
	do
		echo
		echo "/////////// TEST $i ////////////"
	    build/nachos-userprog -rs $i -x build/$1
	done
fi