

main.out: main.cpp textgraphics.o imgcontainer.o
	g++ -std=c++11 main.cpp textgraphics.o imgcontainer.o -o main.out
textgraphics.o: textgraphics.cpp
	g++ -std=c++11 -c -o textgraphics.o textgraphics.cpp
imgcontainer.o: imgcontainer.cpp
	g++ -std=c++11 -c -o imgcontainer.o imgcontainer.cpp
