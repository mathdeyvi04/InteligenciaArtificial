all:
	g++ \
	-I/usr/include/SDL2 -D_REENTRANT \
	main.cpp -o main \
	-lSDL2; \
	./main; rm -f main;	

create:
	g++ \
	-I/usr/include/SDL2 -D_REENTRANT \
	main.cpp -o main \
	-lSDL2;

python:
	g++ -O3 -Wall -shared -std=c++17 -fPIC \
	-D BUILD_AS_PYTHON_MODULE \
	-I/usr/include/python3.12 -I/usr/lib/python3/dist-packages/pybind11/include \
	-I/usr/include/SDL2 -D_REENTRANT \
	main.cpp -o genectic_lab.so \
	-lSDL2;