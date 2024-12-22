# Compilation et édition de liens
Test4: Test4.cpp    Schedulable.o Professor.o Group.o Classroom.o
	g++ Test4.cpp    Schedulable.o Professor.o Group.o Classroom.o -o Test4


Schedulable.o: Schedulable.cpp Schedulable.h
	g++ -c Schedulable.cpp -o Schedulable.o

Professor.o: Professor.cpp Professor.h
	g++ -c Professor.cpp -o Professor.o

Group.o: Group.cpp Group.h
	g++ -c Group.cpp -o Group.o

Classroom.o: Classroom.cpp Classroom.h
	g++ -c Classroom.cpp -o Classroom.o

# Cible de nettoyage
clean:
	rm -f *.o Test4
