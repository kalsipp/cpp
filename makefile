

main.out: main.cpp textgraphics.o
	g++ -std=c++11 main.cpp textgraphics.o -o main.out
textgraphics.o: textgraphics.cpp
	g++ -std=c++11 -c -o textgraphics.o textgraphics.cpp
