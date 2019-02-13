# Description 
NachOS est un système d'exploitation minimal à but d'apprentissage.  
Il est composé d'une base de code déjà fonctionnelle mais peu fournie, cette dernière ne permet par exemple pas l'utilisation de plusieurs Threads, la mémoire est gérée d'une façon très basique et ne permet d'exécuter qu'un processus simulatanement et il n'existe pas de système de fichiers.  
Le but de ce projet est de rendre ce système simulé plus efficace.  
Ce dernier est simulé dans un terminal pour des raisons de simplicité de debug, en revanche, il s'agit bien d'un OS à part entière, le système simule tout les élements d'une véritable machine physique.  
En particulier, le simulateur du processeur de nachOS est un processeur ***MIPS***, les programmes utilisateurs doivent donc être compilés pour ce jeu d'instructions. 

# Utilisation 
Le script README.Debian du répertoire **nachos** permet d'installer un *Cross-Compiler* ***MIPS*** pour permettre d'exécuter nachOS (l'exécuter deux fois, en root).  
La commande ***make*** compilera toutes les cibles utiles à l'exécution.  
Dans le répertoire **build**, on peut utiliser **./nachos-FS** pour lancer nachOS, mais cela ne fera rien.  
Quelques exemples d'utilisation :  
- **./nachos-FS -f** va supprimer le contenu du système de fichiers de nachOS.  
- **./nachos-FS -l** va afficher le contenu du répertoire courant.  
- **./nachos-FS -x userprog** va exécuter le programme *userprog*, qui doit être present dans le répertoire courant de nachOS.  
- **./nachos-FS -cd directory** permet de se déplacer dans l'arborescence (avec certains noms spéciaux, comme ".", ".." ou "/" qui ont la même signification que sous linux.  
- **./nachos-FS -mkdir directory** va créer un nouveau répertoire dans le répertoire courant de nachOS
- **./nachos-FS -cp file1 file2** va copier le contenu de *file1* (fichier **linux**) dans le *file2* (fichier **nachOS**)

# Fonctionnalités ajoutées
Liste non-exhaustive des fonctionnalités ajoutées à **nachOS**:
- Nous avons commencé par créer les ***I/O*** basiques pour que l'OS puisse communiquer avec le monde exterieur.  
- Nous avons ajouté la possibilité de créer simultanement plusieurs Threads noyaux, et plusieurs Threads utilisateurs.  
- Pour ça, nous avons créé des structures de synchronisation pour les programmes utilisateurs.
- Nous avons implementé une gestion plus efficace de la mémoire (mémoire virtuelle et pagination), pour pouvoir permettre l'exécution simultanée de plusieurs programmes utilisateurs.  
- Nous avons implementé un système de fichiers, permettant d'avoir une arborescence de repertoire et de l'utiliser. 
- Nous avons créé plusieurs bibliothèques utilisateurs permettant d'utiliser le système de fichier.  
