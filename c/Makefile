
client: opengl.o application.o camera.o main.o  model.o  vector.o  system.o texture.o textureshader.o utils.o input.o
	g++ -o client textureshader.o main.o camera.o opengl.o vector.o application.o model.o system.o texture.o utils.o input.o -l GL -l X11

input.o: ./src/input.cpp
	g++ -c ./src/input.cpp

utils.o: ./src/utils.cpp
	g++ -c ./src/utils.cpp

application.o: ./src/application.cpp
	g++ -c ./src/application.cpp

camera.o: ./src/camera.cpp
	g++ -c ./src/camera.cpp

model.o: ./src/model.cpp
	g++ -c ./src/model.cpp

system.o: ./src/system.cpp
	g++ -c ./src/system.cpp

texture.o: ./src/texture.cpp
	g++ -c ./src/texture.cpp

textureshader.o: ./src/textureshader.cpp
	g++ -c ./src/textureshader.cpp

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp

opengl.o: ./src/opengl.cpp
	g++ -c ./src/opengl.cpp

vector.o: ./src/vector.cpp
	g++ -c ./src/vector.cpp
