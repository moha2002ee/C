# Makefile for building Test05

# Target executable
TARGET = Test05

# Source files
SRCS = Test5.cpp Event.cpp Time.cpp Timing.cpp TimeException.cpp TimingException.cpp Exception.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Rule to build the target
$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET)

# Rule to compile Event.o
Event.o: Event.cpp Event.h
	g++ -c Event.cpp -o Event.o

# Rule to compile Time.o
Time.o: Time.cpp Time.h
	g++ -c Time.cpp -o Time.o

# Rule to compile Timing.o
Timing.o: Timing.cpp Timing.h
	g++ -c Timing.cpp -o Timing.o

# Rule to compile TimeException.o
TimeException.o: TimeException.cpp TimeException.h
	g++ -c TimeException.cpp -o TimeException.o

# Rule to compile TimingException.o
TimingException.o: TimingException.cpp TimingException.h
	g++ -c TimingException.cpp -o TimingException.o

# Rule to compile Exception.o
Exception.o: Exception.cpp Exception.h
	g++ -c Exception.cpp -o Exception.o

# Clean up
clean:
	rm -f *.o $(TARGET)
