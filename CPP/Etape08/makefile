# Répertoire des fichiers source
CLASSE=./Classes/

# Commande de compilation
COMPIL=g++ -I$(CLASSE) -DDEBUG

# Nom des tests
NUMTEST_A=8a
NUMTEST_B=8b

# Noms des exécutables
EXEC_A=Test$(NUMTEST_A)
EXEC_B=Test$(NUMTEST_B)

# Règle par défaut (compilation des deux exécutables)
all: $(EXEC_A) $(EXEC_B)

# Compilation de Test8a
$(EXEC_A): Test$(NUMTEST_A).cpp Time.o Timing.o Event.o Schedulable.o Professor.o Group.o Classroom.o Exception.o TimeException.o TimingException.o XmlFileSerializerException.o Timetable.o
	@echo "Compilation de $(EXEC_A)"
	$(COMPIL) $^ -o $@

# Compilation de Test8b
$(EXEC_B): Test$(NUMTEST_B).cpp Time.o Timing.o Event.o Schedulable.o Professor.o Group.o Classroom.o Exception.o TimeException.o TimingException.o XmlFileSerializerException.o Timetable.o
	@echo "Compilation de $(EXEC_B)"
	$(COMPIL) $^ -o $@

# Règles pour les fichiers objets
Time.o: Time.cpp Time.h
	@echo "Compilation de Time"
	$(COMPIL) -c $< -o $@

Timing.o: Timing.cpp Timing.h
	@echo "Compilation de Timing"
	$(COMPIL) -c $< -o $@

Event.o: Event.cpp Event.h
	@echo "Compilation de Event"
	$(COMPIL) -c $< -o $@

Schedulable.o: Schedulable.cpp Schedulable.h
	@echo "Compilation de Schedulable"
	$(COMPIL) -c $< -o $@

Professor.o: Professor.cpp Professor.h
	@echo "Compilation de Professor"
	$(COMPIL) -c $< -o $@

Group.o: Group.cpp Group.h
	@echo "Compilation de Group"
	$(COMPIL) -c $< -o $@

Classroom.o: Classroom.cpp Classroom.h
	@echo "Compilation de Classroom"
	$(COMPIL) -c $< -o $@

Exception.o: Exception.cpp Exception.h
	@echo "Compilation de Exception"
	$(COMPIL) -c $< -o $@

TimeException.o: TimeException.cpp TimeException.h
	@echo "Compilation de TimeException"
	$(COMPIL) -c $< -o $@

TimingException.o: TimingException.cpp TimingException.h
	@echo "Compilation de TimingException"
	$(COMPIL) -c $< -o $@

XmlFileSerializerException.o: XmlFileSerializerException.cpp XmlFileSerializerException.h
	@echo "Compilation de XmlFileSerializerException"
	$(COMPIL) -c $< -o $@

Timetable.o: Timetable.cpp Timetable.h
	@echo "Compilation de Timetable"
	$(COMPIL) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	@echo "Suppression des fichiers objets et des exécutables"
	@rm -f *.o $(EXEC_A) $(EXEC_B)
