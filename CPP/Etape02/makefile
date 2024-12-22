Test02: Test2.cpp Event.o Time.o Timing.o
	g++ Test2.cpp Event.o Time.o Timing.o -o Test02

Event.o: Event.cpp Event.h
	g++ -c Event.cpp -o Event.o

Time.o: Time.cpp Time.h
	g++ -c Time.cpp -o Time.o

Timing.o: Timing.cpp Timing.h
	g++ -c Timing.cpp -o Timing.o

clean:
	rm -f *.o Test02
