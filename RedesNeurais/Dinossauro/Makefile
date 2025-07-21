TARGET = simulation_neural_network

SRC = main.cpp

# Flags do SDL2
SDL_CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
SDL_LIBS   = -lSDL2 -lSDL2_image -lSDL2_ttf

# Compilador e flags
CXXFLAGS = g++ -Wall -std=c++17 $(SDL_CFLAGS)
LDFLAGS  = $(SDL_LIBS)

################################################################

all: $(TARGET)

# $^ -> variável de entrada
# S@ -> variável de saída
$(TARGET): $(SRC)
	$(CXXFLAGS) $^ -o $@ $(LDFLAGS); ./$(TARGET); rm -f $(TARGET)

clean:
	rm -f $(TARGET)  
