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

You are 3 different circuits that you can try: a
basic one, a sort of circle and a more complex one.
Try them all by clicking on "change track".

Finally, you can end the training and start a new one
by clicking the "reset" button.


	---- Makefile commands -----

make : creates the .o and the executable.

make clean : deletes all the .o files.

make remove : deletes every created file, including
the executable.

make run : launches the program.

make valgrind : launches the program with a valgrind
analysis.


	---- Folder's organisation -----

/bin : Contains the executable.

/data : Contains all the data, genome files(.gen),
track files (.track), sprites (car, buttons).

/lib: Contains the SDL2.0 library, used for graphics.

/obj: Contains all the .o files.

/src: Contains the source files,.c and .h .

/doc: Contains the Doxygen documentation.









