# Compilation de l'exécutable UNIX_Exercice2
UNIX_Exercice2: main.o mywindow.o moc_mywindow.o FichierUtilisateur.o
		g++ -o UNIX_Exercice2 main.o mywindow.o moc_mywindow.o FichierUtilisateur.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

# Compilation du fichier main.o
main.o: main.cpp
		g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

# Compilation du fichier mywindow.o
mywindow.o: mywindow.cpp
		g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o mywindow.o mywindow.cpp

# Compilation du fichier moc_mywindow.o
moc_mywindow.o: moc_mywindow.cpp
		g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_mywindow.o moc_mywindow.cpp

# Compilation du fichier FichierUtilisateur.o
FichierUtilisateur.o: FichierUtilisateur.cpp
		g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++ -o FichierUtilisateur.o FichierUtilisateur.cpp

# Nettoyage des fichiers objets et de l'exécutable
clean:
		rm -f *.o UNIX_Exercice2
