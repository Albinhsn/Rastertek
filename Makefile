
client: applicationclass.o inputclass.o main.o openglclass.o systemclass.o cameraclass.o colorshadersclass.o modelclass.o
	g++ -o client cameraclass.o modelclass.o colorshadersclass.o applicationclass.o inputclass.o main.o openglclass.o systemclass.o -l GL -l X11

modelclass.o: ./src/modelclass.cpp
	g++ -c ./src/modelclass.cpp

cameraclass.o: ./src/cameraclass.cpp
	g++ -c ./src/cameraclass.cpp

colorshadersclass.o: ./src/colorshadersclass.cpp
	g++ -c ./src/colorshadersclass.cpp

applicationclass.o: ./src/applicationclass.cpp
	g++ -c ./src/applicationclass.cpp

inputclass.o: ./src/inputclass.cpp
	g++ -c ./src/inputclass.cpp

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp

openglclass.o: ./src/openglclass.cpp
	g++ -c ./src/openglclass.cpp

systemclass.o: ./src/systemclass.cpp
	g++ -c ./src/systemclass.cpp

