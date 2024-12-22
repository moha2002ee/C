# Variables
CC = gcc
CFLAGS = -Wall -g
LIBS =
OBJS = LibSer.o HandleTCPClient.o LibSerHV.o

# Cibles principales
all: TCPEchoServer TCPEchoClient admin

# Cibles pour les fichiers objets
LibSer.o: LibSer.c LibSer.h
	echo "Compilation de LibSer.o"
	$(CC) $(CFLAGS) -c LibSer.c

HandleTCPClient.o: HandleTCPClient.c HandleTCPClient.h
	echo "Compilation de HandleTCPClient.o"
	$(CC) $(CFLAGS) -c HandleTCPClient.c

LibSerHV.o: LibSerHV.c LibSerHV.h data.h
	echo "Compilation de LibSerHV.o"
	$(CC) $(CFLAGS) -c LibSerHV.c

# Cibles pour les exécutables
TCPEchoServer: TCPEchoServer.c HandleTCPClient.o LibSer.o LibSerHV.o
	echo "Compilation de TCPEchoServer"
	$(CC) $(CFLAGS) -o TCPEchoServer TCPEchoServer.c HandleTCPClient.o LibSer.o LibSerHV.o

TCPEchoClient: TCPEchoClient.c
	echo "Compilation de TCPEchoClient"
	$(CC) $(CFLAGS) -o TCPEchoClient TCPEchoClient.c 

admin: admin.c LibSerHV.o LibSer.o
	echo "Compilation de admin"
	$(CC) $(CFLAGS) -o admin admin.c LibSerHV.o LibSer.o

# Nettoyage
clean:
	rm -f *.o TCPEchoServer TCPEchoClient admin
