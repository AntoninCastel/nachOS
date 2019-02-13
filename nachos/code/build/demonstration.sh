#!/bin/bash

tmp=`tempfile`
build="./"
prog="$build/nachos-userprog"
progfs="$build/nachos-FS"

#   Tu copies les lignes suivantes pour l'affichage du code   
#
#    echo "Code source :"
#    cat $build/../test/cat.c
#    echo "================================="

make clean
make
case "$1" in
"1")
    clear
    echo "////////////////////////////////////////////////"
    echo "//                ENTREES/SORTIES             //"
    echo "////////////////////////////////////////////////"
    echo
    echo "Manipulation de caractères"
    read -e
    echo "Affichage d'une chaine saisie par l'utilisateur GetChar & PutChar"
    read -e
    echo "Code source :"
    cat $build/../test/cat.c
    echo "================================="
    $prog -x $build/cat 2> /dev/null
    echo
    echo
    echo "Manipulation d'entiers"
    read -e
    echo "Somme de 4 entiers demandés à l'utilisateur"
    read -e
    echo "Code source :"
    cat $build/../test/sum.c
    echo "================================="
    $prog -x $build/sum 2> /dev/null
    echo
    read -e
    echo
;&
"2")
    clear
    echo "////////////////////////////////////////////////"
    echo "//                MULTITHREADING              //"
    echo "////////////////////////////////////////////////"
    echo
    read -e
    echo "Producteur-consommateur avec les sémaphores utilisateur"
    read -e
    echo "Code source :"
    cat $build/../test/producteur-consommateur.c
    echo -n "================================="
    read -e
    $prog -rs 1 -x $build/producteur-consommateur &
    pid=$!
    echo
    sleep 3
    kill -2 $pid
    read -e
    echo
    echo "Création de threads en cascade qui sont tous attendus par le thread initial"
    read -e
    echo "Code source :"
    cat $build/../test/thread_arborescence.c
    echo -n "================================="
    read -e
    $prog -rs 1 -x $build/thread_arborescence &
    read -e
    echo
    echo "Création de threads en cascade qui attendent leur fils"
    read -e
    echo "Code source :"
    cat $build/../test/thread_cascade.c
    echo -n "================================="
    read -e
    $prog -rs 1 -x $build/thread_cascade &
    read -e
    echo

;&
"3")
    clear
    echo "////////////////////////////////////////////////"
    echo "//                VIRTUAL MEMORY              //"
    echo "////////////////////////////////////////////////"
    echo
    read -e
    echo "Processus qui appelle un programme externe pour le charger en memoire et l'executer"
    read -e
    echo "Code source :"
    echo "Programme principal:"
    cat $build/../test/waitpid.c
    echo "progA.c:"
    cat $build/../test/progA.c
    echo -n "================================="
    read -e
    $prog -rs 1 -x $build/waitpid
    pid=$!
    sleep 1
    #kill -2 $pid
    echo
    read -e
    echo
    echo "Processus qui appelle deux programmes pour les exécuter"
    read -e
    echo "Code source :"
    echo "Programme principal:"
    cat $build/../test/fork2.c
    echo "PutCharA.c:"
    cat $build/../test/PutCharA.c
    echo "PutCharB.c:"
    cat $build/../test/PutCharB.c
    echo -n "================================="
    read -e
    $prog -rs 1 -x $build/fork2
    sleep 1
    #kill -2 $pid
;&
esac
