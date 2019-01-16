#!/bin/bash

tmp=`tempfile`
build="./build"
prog="$build/nachos-userprog"
progfs="$build/nachos-FS"

case "$1" in
"1")
    echo "////////////////////////////////////////////////"
    echo "//                ENTREES/SORTIES             //"
    echo "////////////////////////////////////////////////"
    echo
    echo "Manipulation de caractères"
    echo "Affichage d'une chaine saisie par l'utilisateur GetChar & PutChar"
    $prog -x $build/cat 2> /dev/null
    echo
    echo
    echo "Manipulation d'entiers"
    echo "Somme de 4 entiers demandés à l'utilisateur"
    $prog -x $build/sum 2> /dev/null
    echo
    echo
;&
"2")
    echo "////////////////////////////////////////////////"
    echo "//                MULTITHREADING              //"
    echo "////////////////////////////////////////////////"
    echo
    echo "Producteur-consommateur avec les sémaphores utilisateur"
    $prog -rs 1 -x $build/producteur-consommateur &
    pid=$!
    sleep 0.02
    kill $pid
    read
    echo
;&
"3")
    echo "////////////////////////////////////////////////"
    echo "//                VIRTUAL MEMORY              //"
    echo "////////////////////////////////////////////////"
    echo
    echo ""
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

    read 
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
