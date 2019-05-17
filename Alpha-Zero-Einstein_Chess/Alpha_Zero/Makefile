final:main.o Einstein.o ClientSocket.o
	g++ -std=c++11 -o main main.o Einstein.o ClientSocket.o
main.o:main.cpp Einstein.cpp
	g++ -std=c++11 -c -o main.o main.cpp 
Einstein.o: Einstein.cpp Einstein.h
	g++ -std=c++11 -c -o Einstein.o Einstein.cpp
ClientSocket.o: ClientSocket.cpp ClientSocket.h Define.h
	g++ -std=c++11 -c -o ClientSocket.o ClientSocket.cpp
