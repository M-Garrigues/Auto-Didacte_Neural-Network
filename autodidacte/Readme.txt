****************************************************
******************  AUTO-DIDACTE  ******************
****************************************************


=== ENGLISH ========================================


 	----- Description ----

A LIF7 project realised by Valentin GRANDJEAN,
Florian BEGONIN and Mathieu GARRIGUES. (2016)

This project is an Artificial Intelligence
experience that features a self-learning 2D car 
that must grasp and assimilate the concept of 
driving in a 2D environment. It is made in C, and
uses SDL2.0 as graphic library.

It uses the Artificial Neural Network technology,
trained by a Genetic Algorithm.


	---- How does it work? ----

The application automatically runs a simulation
where a car is on a circuit. The car has 5 sensors
(the blue lines) wich permits it to "see" the border
of the circuit. During the whole simulation, the 
Artificial Neural Network (ANN) "inside" the car 
decides wich action - acceleration, deceleration, turn 
right,turn left,do nothing - to do in function of the
sensors and the speed.

These decisions are always improving thanks to the 
Genetic algorithm. The simulation is done on 
"generations": every generation is a group of 20-30
individual cars with a slightly different ANN.
Once every member of a generation is simulated, the
one that goes the further/faster is selected, and used
to breed the next generation. This way, every
generation is equal or better than the previous one.

After some generations, the ANN is evolved enough
to make the car drive through the whole circuit,
accelerating on straight lines, and decelerating
before turns.



	---- How do I use it? ----

- If you use Linux or OS X: open a console in the
main folder,and just type : 
"make && make run".
If it doesn't work, make sure you have the 
build-essential package installed by typing: 
"sudo apt-get install build-essential".

- If you use Windows, just launch the exe in /bin,
and enjoy!


This application is very easy to use as you have 
nothing to worry about. You can observe the training
in progress, or accelerate it by clicking on 
"fast computing". While this button is On, there will
be no display of the current simulation, but the
training will be way faster. You can see the progress
of the simulation with the Fitness: the higher this 
number is, the better the car.

You can also see the best simulation ever done yet by
clicking the "see best" button. It stops the training 
to show you the simulation of the best ANN so far.
Click on "resume" to go back to the training.

There are 3 different circuits that you can try: a
basic one, a sort of circle and a more complex one.
Try them all by clicking on "change track".

Finally, you can end the training and start a new one
by clicking the "reset" button.


	---- Makefile commands -----

make : Creates the .o and the executable.

make clean : Deletes all the .o files.

make remove : Deletes every created file, including
the executable.

make run : Launches the program.

make valgrind : Launches the program with a valgrind
analysis.


	---- Folder's organisation -----

/bin : Contains the executable.

/data : Contains all the data, genome files(.gen),
track files (.track), sprites (car, buttons).

/lib: Contains the SDL2.0 library, used for graphics.

/obj: Contains all the .o files.

/src: Contains the source files,.c and .h .

/doc: Contains the Doxygen documentation.



=== FRANCAIS =======================================


----- Description ----

Projet de LIF7 réalisé par Valentin GRANDJEAN,
Florian BEGONIN et Mathieu GARRIGUES. (2016)

Ce projet est une expérience d'intelligence 
artificielle. Elle utilise une voiture 2D en 
auto-apprentissage, qui doit comprendre et 
assimiler le principe de la conduite dans un 
environnement en 2D.

Le code source est écrit en C, et utilise SDL2.0
en tant que librairie graphique.
Il utilise le principe des Réseaux de Neurones
Artificiels (ANN), entrainés avec un algorithme
Génétique.


	---- Comment cela fonctionne-t-il? ----

Cette application génère automatiquement une 
simulation qui montre une voiture sur un circuit.
La voiture a 5 capteurs (les lignes bleues) qui
lui permettent de "voir" les bords du circuit.
Pendant toute la simulation, l'ANN "à l'intérieur"
de la voiture décide quelle action réaliser - entre
accélérer, freiner, tourner à gauche, tourner à
droite, ne rien faire - en fonction des capteurs et
de la vitesse.

Ces décisions s'améliorent continuellement grace à
l'algorithme Génétique. La simulation est découpée
en "générations": chaque génération est un groupe 
de 20-30 voitures différentes gérées chacunes par un
ANN légèrement différent. Une fois que tous les 
membres d'une génération ont étés simulés, le
meilleur d'entre eux (le plus rapide, celui qui va
le plus loin) est sélectionné, et utilisé pour créer
la génération suivante.
Ainsi, chaque génération est aussi bonne ou meilleure
que la précédente.

Après plusieurs générations, l'ANN utilisé est
suffisamment évolué pour qu'une voiture parcoure
le circuit entier, en accélérant dans les lignes 
droites et en ralentissant aux virages.



	---- Comment l'utiliser? ----

- Si vous utilisez Linux ou OS X: ouvrez la console
dans le fichier principal, et tapez simplement:
"make && make run".
Si cela ne marche pas, vérifiez que le package
build-essential est bien installé en tapant:
"sudo apt-get install build-essential".

- Si vous utilisez Windows, lancez simplement
l'exe se trouvant dans /bin, et profitez!


Cette application est très simple à utiliser, car
vous n'avez pas à vous occuper des détails. Vous 
pouvez observer l'entraînement en cours, ou
l'accélérer grandement en cliquant sur "fast 
computing". Tant que ce bouton sera actif,
l'affichage ne sera pas actualisé, mais 
l'entraînement ira bien plus vite. Vous pouvez voir
les progrès faits grace au Fitness: plus ce chiffre
est élevé, meilleure est la voiture.

Vous pouvez également voir la meilleure simulation
faite jusqu'ici en cliquant sur le bouton "see best".
Il arrêtera l'entraînement pour vous montrer la
simulation du meilleur ANN utilisé à ce point de 
l'entraînement.
Cliquez sur "resume" pour retourner à la normale.

Il y a 3 circuits différents que vous pouvez
essayer: un circuit basique, une sorte de cercle
et un dernier, plus complexe.
Essayez les tous en cliquant sur "change track"!

Enfin, vous pouvez arrêter la simulation et en
commencer une nouvelle en cliquant sur "reset".



	---- Commandes du Makefile -----

make : Crée les .o et l'exécutable.

make clean : Supprime tous les .O .

make remove : Supprime tous les fichiers créés,
y compris l'exécutable.

make run : Lance le programme.

make valgrind : Lance le programme, avec en 
complément une analyse Valgrind.


	---- Organisation du dossier -----

/bin : Contient l'exécutable.

/data : Contient toutes les données, comme
les fichiers genome (.gen), les fichiers de
circuit (.track), les sprites (voiture, 
boutons), ...

/lib : Contient la librairie SDL2.0, utilisée
pour l'affichage.

/obj : Contient tous les fichiers .o .

/src : Contient les fichiers sources, .c et .h .

/doc : Contient la documentation Doxygen.




