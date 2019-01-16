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

case "$1" in
"1")
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
    echo "////////////////////////////////////////////////"
    echo "//                MULTITHREADING              //"
    echo "////////////////////////////////////////////////"
    echo
    read -e
    echo "Producteur-consommateur avec les sémaphores utilisateur"
    read -e
    echo "Code source :"
    cat $build/../test/producteur-consommateur.c
    echo "================================="
    read -e
    $prog -rs 1 -x $build/producteur-consommateur &
    pid=$!
    sleep 0.015
    kill $pid
    echo
    read -e
    echo
;&
"3")
    echo "////////////////////////////////////////////////"
    echo "//                VIRTUAL MEMORY              //"
    echo "////////////////////////////////////////////////"
    echo
    read -e
    echo "Processus qui appelle un programme externe pour le charger en memoire et l'executer"
    $prog -rs 1 -x $build/waitpid
    pid=$!
    sleep 0.02
    kill -2 $pid    # ne marche pas....
    echo
    read -e
    echo
;&
"4")
    echo "////////////////////////////////////////////////"
    echo "//             SYSTEME DE FICHIERS            //"
    echo "////////////////////////////////////////////////"
    echo "Restauration du systeme de fichiers"
    $progfs -f
    pid=$!
    kill -2 $pid

    read -e
    echo "Copie dans le répertoire / des fichiers necessaires au test"
    $progfs -cp $build/FS1 FS1
    pid=$!
    kill -2 $pid
    $progfs -cp $build/FS2 FS2
    pid=$!
    kill -2 $pid
    $progfs -cp $build/FS3 FS3
    pid=$!
    kill -2 $pid
;&
esac
