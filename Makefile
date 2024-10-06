CXX = /usr/bin/g++
CXXFLAGS = -std=c++17 -Iinclude -Ilib -fdiagnostics-color=always -g
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_net
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
EXEC = apocalypso
TEST_EXEC = test_runner

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

IMGUI_SRCS := $(wildcard lib/imgui/*.cpp)
IMGUI_OBJS := $(patsubst lib/imgui/%.cpp, $(OBJ_DIR)/%.o, $(IMGUI_SRCS))

.PHONY: all clean test

all: $(EXEC)

$(EXEC): $(IMGUI_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(OBJ_DIR)/%.o: lib/imgui/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXEC)

$(TEST_EXEC): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_OBJS) 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lgtest -lgtest_main -pthread

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC) $(TEST_EXEC)
