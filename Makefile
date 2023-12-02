CXX = /usr/bin/g++
CXXFLAGS = -std=c++17 -Iinclude -Ilib -fdiagnostics-color=always -g
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRC_DIR = src
OBJ_DIR = obj
EXEC = apocalypso

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)
