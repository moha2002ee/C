
all: Gerant Client Serveur CreationBD Publicite Caddie AccesBD


maingerant.o: maingerant.cpp
	@echo "Compilation de maingerant.cpp..."
	@g++ -Wno-unused-parameter -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../Administrateur -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o maingerant.o maingerant.cpp

windowgerant.o: windowgerant.cpp
	@echo "Compilation de windowgerant.cpp..."
	@g++ -Wno-unused-parameter -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../Administrateur -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -I/usr/include/mysql -m64 -L/usr/lib64/mysql -o windowgerant.o windowgerant.cpp

moc_windowgerant.o: moc_windowgerant.cpp
	@echo "Compilation de moc_windowgerant.cpp..."
	@g++ -Wno-unused-parameter -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../Administrateur -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_windowgerant.o moc_windowgerant.cpp

Gerant: maingerant.o windowgerant.o moc_windowgerant.o
	@echo "Compilation de Gerant..."
	@g++ -Wno-unused-parameter -o Gerant maingerant.o windowgerant.o moc_windowgerant.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

mainclient.o: mainclient.cpp
	@echo "Compilation de mainclient.cpp..."
	@g++ -Wno-unused-parameter -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_DOSSIER_FINAL -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o mainclient.o mainclient.cpp

windowclient.o: windowclient.cpp
	@echo "Compilation de windowclient.cpp..."
	@g++ -Wno-unused-parameter -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_DOSSIER_FINAL -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o windowclient.o windowclient.cpp

moc_windowclient.o: moc_windowclient.cpp
	@echo "Compilation de moc_windowclient.cpp..."
	@g++ -Wno-unused-parameter -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_DOSSIER_FINAL -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_windowclient.o moc_windowclient.cpp

Client: mainclient.o windowclient.o moc_windowclient.o
	@echo "Compilation de Client..."
	@g++ -Wno-unused-parameter -o Client mainclient.o windowclient.o moc_windowclient.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread
FichierClient.o: FichierClient.cpp FichierClient.h
	@echo "Compilation de fichier client..."
	g++ -c FichierClient.cpp



# Serveur
Serveur: Serveur.cpp FichierClient.o
	@echo "Compilation de Serveur.cpp..."
	@g++ Serveur.cpp  FichierClient.o -o Serveur -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl




# Autres programmes
CreationBD: CreationBD.cpp
	@echo "Compilation de CreationBD.cpp..."
	@g++ -o CreationBD CreationBD.cpp -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

Publicite: Publicite.cpp
	@echo "Compilation de Publicite.cpp..."
	@g++ -o Publicite Publicite.cpp

Caddie: Caddie.cpp
	@echo "Compilation de Caddie.cpp..."
	@g++ -o Caddie Caddie.cpp -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

AccesBD: AccesBD.cpp
	@echo "Compilation de AccesBD.cpp..."
	@g++ -o AccesBD AccesBD.cpp -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

clean:
	@echo "Clean de tout..."
	@rm -f *.o Gerant Client Serveur CreationBD Publicite Caddie AccesBD
