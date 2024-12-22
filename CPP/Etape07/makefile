# Nom de l'exécutable
TARGET = Test07

# Fichiers objets nécessaires
OBJECTS = Test7.o Event.o Time.o Timing.o Exception.o TimeException.o TimingException.o Classroom.o Schedulable.o XmlFileSerializerException.o

# Compilateur et flags
CC = g++
CFLAGS = -Wall -std=c++11

# Règle pour créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Règles pour la création des fichiers objets
Test7.o: Test7.cpp
	$(CC) $(CFLAGS) -c Test7.cpp

Event.o: Event.cpp Event.h
	$(CC) $(CFLAGS) -c Event.cpp

Time.o: Time.cpp Time.h
	$(CC) $(CFLAGS) -c Time.cpp

Timing.o: Timing.cpp Timing.h
	$(CC) $(CFLAGS) -c Timing.cpp

Exception.o: Exception.cpp Exception.h
	$(CC) $(CFLAGS) -c Exception.cpp

TimeException.o: TimeException.cpp TimeException.h
	$(CC) $(CFLAGS) -c TimeException.cpp

TimingException.o: TimingException.cpp TimingException.h
	$(CC) $(CFLAGS) -c TimingException.cpp

Classroom.o: Classroom.cpp Classroom.h
	$(CC) $(CFLAGS) -c Classroom.cpp

Schedulable.o: Schedulable.cpp Schedulable.h
	$(CC) $(CFLAGS) -c Schedulable.cpp

XmlFileSerializerException.o: XmlFileSerializerException.cpp XmlFileSerializerException.h
	$(CC) $(CFLAGS) -c XmlFileSerializerException.cpp

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(TARGET)
