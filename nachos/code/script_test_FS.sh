#!/bin/bash
cd build
case "$1" in
"1")
	echo "**************************************"
	echo "***** Test système de fichiers *******"
	echo "**************************************"
	echo "Formatage du système de fichier"
	./nachos-FS -f &
	sleep 2
	kill -2 $!
	read -n 1

	echo "***************************************************"
	echo "*****Création de répertoire avec nom invalide******"
	echo "***************************************************"
	read -n 1

	echo "./nachos-FS -mkdir .. "
	sleep 2
	./nachos-FS -mkdir .. &
	sleep 2
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	echo "./nachos-FS -mkdir / "
	sleep 2
	./nachos-FS -mkdir / &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	clear

	echo "*************************************************"
	echo "*****Création de répertoire avec nom valide******"
	echo "*************************************************"
	read -n 1

	echo "./nachos-FS -mkdir reptest "
	./nachos-FS -mkdir reptest &
	sleep 3
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	echo "./nachos-FS -cd reptest"
	./nachos-FS -cd reptest &
	sleep 2
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	echo "./nachos-FS -mkdir sousrep"
	./nachos-FS -mkdir sousrep &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -cp test_FS test_FS"
	sleep 2
	./nachos-FS -cp test_FS test_FS &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	echo "./nachos-FS -cd .."
	sleep 1
	./nachos-FS -cd .. &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1



	clear
	echo "******************************************"
	echo "**************** Contraintes *************"
	echo "******************************************"
	read -n 1
	echo "=> Création d'une entrée avec un nom existant "
	read -n 1
	echo "./nachos-FS -mkdir reptest "
	./nachos-FS -mkdir reptest &
	sleep 2
	kill -2 $!
	read -n 1


	echo "=> changement de répertoire sur une entrée inexistante"
	echo "./nachos-FS -cd inexistant"
	sleep 2
	./nachos-FS -cd inexistant &
	sleep 1
	kill -2 $!
	read -n 1

	echo "=> cd sur une entrée qui n'est pas un répertoire"

	echo "./nachos-FS -cp test_FS test_FS"
	sleep 2
	./nachos-FS -cp test_FS test_FS &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	echo "./nachos-FS -cd test_FS"
	sleep 1
	./nachos-FS -cd test_FS &
	sleep 1
	kill -2 $!
	read -n 1

	echo " "
	echo "=> Création de plus de 10 entrées"
	read -n 1

	echo "./nachos-FS -mkdir reptest2 "
	sleep 2
	./nachos-FS -mkdir reptest2 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest3 "
	sleep 2
	./nachos-FS -mkdir reptest3 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest4 "
	sleep 2
	./nachos-FS -mkdir reptest4 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest5 "
	sleep 2
	./nachos-FS -mkdir reptest5 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest6 "
	sleep 2
	./nachos-FS -mkdir reptest6 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest7 "
	sleep 2
	./nachos-FS -mkdir reptest7 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest8 "
	sleep 2
	./nachos-FS -mkdir reptest8 &
	sleep 1
	kill -2 $!

	echo "./nachos-FS -mkdir reptest9 "
	sleep 2
	./nachos-FS -mkdir reptest9 &
	sleep 1
	kill -2 $!
	read -n 1
	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1

	echo "./nachos-FS -mkdir reptest10 "
	sleep 2
	./nachos-FS -mkdir reptest10 &
	sleep 1
	kill -2 $!

	read -n 1
	clear
	echo "******************************************"
	echo "**************** Contraintes *************"
	echo "******************************************"
	echo "=> Suppression d'un répertoire "
	read -n 1
	echo "./nachos-FS -r reptest2"
	read -n 1
	./nachos-FS -r reptest2 &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -r reptest"
	read -n 1
	./nachos-FS -r reptest &
	sleep 1
	kill -2 $!
	read -n 1

	echo "./nachos-FS -l"
	./nachos-FS -l &
	read -n 1
;&
"2")
	clear
	echo "**************************************"
	echo "***** Table des fichiers ouverts *****"
	echo "**************************************"
	echo "=> Ouverture deux fois du même fichier"
	read -n 1	
	echo "Formatage du système de fichier"
	./nachos-FS -f &
	sleep 2
	kill -2 $!

	echo "Copie des fichiers depuis linux vers nachos"
	./nachos-FS -cp bi_open bi_open &
	sleep 2
	kill -2 $!
	echo "Terminé"
	read -n 1

	cat ../test/bi_open.c 
	echo "**************************************"
	echo "Execution du programme"
	read -n 1
	./nachos-FS -x bi_open &
	read -n 1
	
	clear
	echo "**************************************"
	echo "***** Table des fichiers ouverts *****"
	echo "**************************************"
	echo "=> Ecriture et Lecture dans un même fichier"
	read -n 1
	echo "Formatage du système de fichier"
	./nachos-FS -f &
	sleep 2
	kill -2 $!

	echo "Copie des fichiers pour le test"
	./nachos-FS -cp test_FS_write test_w &
	sleep 2
	kill -2 $!
	./nachos-FS -cp test_FS_read test_r &
	sleep 2
	kill -2 $!
	echo "Terminé"
	read -n 1

	cat ../test/test_FS_write.c
	read -n 1
	cat ../test/test_FS_read.c
	read -n 1	

	./nachos-FS -x test_w 
	read -n 1
	./nachos-FS -x test_r 
	read -n 1





;&
esac