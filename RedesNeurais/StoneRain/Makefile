TARGET = main

SRC = src/main.cpp

# Compilador e Flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Flags de ligação com SDL2
SDL_CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
SDL_LDFLAGS = -lSDL2

# Regra padrão
all:
	@$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -o $(TARGET) $(SRC) $(SDL_LDFLAGS);
	@./$(TARGET); 
	@rm -f $(TARGET);

debug: 
	@$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -o $(TARGET) $(SRC) $(SDL_LDFLAGS);
	@valgrind --show-leak-kinds=all ./$(TARGET); 
	@rm -f $(TARGET);
