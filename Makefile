CXX = /usr/bin/g++
CXXFLAGS = -std=c++17 -Iinclude -Ilib -fdiagnostics-color=always -g
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -pthread
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
EXEC = apocalypso
TEST_EXEC = test_runner

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Exclude main.cpp from test build
TEST_SRCS := $($(wildcard $(TEST_DIR)/*.cpp))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

.PHONY: all clean test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXEC)

$(TEST_EXEC): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -I/usr/local/include/ -L/usr/local/lib $^ -o $@ $(LDFLAGS) -lgtest_main -lgtest -lgmock_main -lgmock

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC) $(TEST_EXEC)
