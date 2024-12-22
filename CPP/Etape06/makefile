# Cible par défaut
all: Test6

# Création de l'exécutable Test6
Test6: Test6.cpp Timing.o Time.o TimeException.o TimingException.o Event.o Exception.o Classroom.o Schedulable.o
	g++ Test6.cpp Timing.o Time.o TimeException.o TimingException.o Event.o Exception.o Classroom.o Schedulable.o -o Test6

# Compilation des fichiers objets
Time.o: Time.cpp
	g++ Time.cpp -c

TimeException.o: TimeException.cpp
	g++ TimeException.cpp -c

Timing.o: Timing.cpp
	g++ Timing.cpp -c

TimingException.o: TimingException.cpp
	g++ TimingException.cpp -c

Event.o: Event.cpp
	g++ Event.cpp -c

Exception.o: Exception.cpp
	g++ Exception.cpp -c

Classroom.o: Classroom.cpp
	g++ Classroom.cpp -c

Schedulable.o: Schedulable.cpp
	g++ Schedulable.cpp -c

# Nettoyage des fichiers objets
clean:
	rm -f *.o Test6 *.xml
