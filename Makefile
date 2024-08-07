#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: Dron
	./Dron

Dron: obj obj/main.o obj/BrylaGeometryczna.o obj/Macierz.o obj/Wektor.o\
		  obj/lacze_do_gnuplota.o  obj/Dron.o obj/Prostopadloscian.o obj/Graniastoslup.o obj/Scena.o obj/Gora.o obj/Pagorek.o obj/Plaskowyz.o
	g++ -Wall -pedantic -std=c++0x -o Dron obj/main.o obj/Wektor.o\
              obj/Dron.o obj/Macierz.o obj/BrylaGeometryczna.o obj/lacze_do_gnuplota.o\
              obj/Prostopadloscian.o  obj/Graniastoslup.o  obj/Scena.o obj/Gora.o obj/Pagorek.o obj/Plaskowyz.o

obj:
	mkdir obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/BrylaGeometryczna.hh inc/Macierz.hh\
           inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/BrylaGeometryczna.o: src/BrylaGeometryczna.cpp inc/BrylaGeometryczna.hh\
         inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/BrylaGeometryczna.o src/BrylaGeometryczna.cpp

obj/Macierz.o: src/Macierz.cpp inc/Macierz.hh inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Macierz.o src/Macierz.cpp

obj/Wektor.o: src/Wektor.cpp inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor.o src/Wektor.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/Macierz.hh inc/Prostopadloscian.hh inc/Graniastoslup.hh inc/BrylaGeometryczna.hh inc/lacze_do_gnuplota.hh inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Dron.o src/Dron.cpp

obj/Gora.o: src/Gora.cpp inc/Gora.hh inc/BrylaGeometryczna.hh inc/Macierz.hh
	g++ -c ${CXXFLAGS} -o obj/Gora.o src/Gora.cpp

obj/Pagorek.o: src/Pagorek.cpp inc/Pagorek.hh inc/BrylaGeometryczna.hh inc/Macierz.hh
	g++ -c ${CXXFLAGS} -o obj/Pagorek.o src/Pagorek.cpp

obj/Plaskowyz.o: src/Plaskowyz.cpp inc/Plaskowyz.hh inc/BrylaGeometryczna.hh inc/Macierz.hh
	g++ -c ${CXXFLAGS} -o obj/Plaskowyz.o src/Plaskowyz.cpp
	
obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/BrylaGeometryczna.hh inc/Macierz.hh  inc/Wektor.hh
	g++ -c ${CXXFLAGS} -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/Graniastoslup.o: src/Graniastoslup.cpp inc/Graniastoslup.hh inc/BrylaGeometryczna.hh inc/Macierz.hh
	g++ -c ${CXXFLAGS} -o obj/Graniastoslup.o src/Graniastoslup.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/Scena.hh inc/Dron.hh inc/Macierz.hh inc/Prostopadloscian.hh inc/Graniastoslup.hh inc/BrylaGeometryczna.hh inc/lacze_do_gnuplota.hh inc/Wektor.hh inc/Gora.hh inc/Pagorek.hh inc/Plaskowyz.hh
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

clean:
	rm -f obj/*.o Dron
	rm -f dat/*.dat Dron
