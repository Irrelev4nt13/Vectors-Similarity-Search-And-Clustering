CXX := g++
FLAGS := -g3 -std=c++11

BIN_DIR := bin
BUILD_DIR := build
INCLUDE_DIR := include
MODULES_DIR := modules
SRC_DIR := src

LSH := $(BIN_DIR)/lsh_main
CUBE := $(BIN_DIR)/cube_main
CLUSTER := $(BIN_DIR)/cluster_main

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

MODULES_FILES := $(shell find $(MODULES_DIR) -name '*.cpp')

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

OBJ_MODULES := $(patsubst $(MODULES_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(MODULES_FILES))

EXEC_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRC_FILES))

INCLUDE_DIRS := $(shell find $(INCLUDE_DIR) -type d)

INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIRS) $(INCLUDE_DIR))


all: $(EXEC_FILES) $(OBJ_MODULES)

$(BUILD_DIR)/%.o: $(MODULES_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $< -o $@ $(INCLUDE_FLAGS) $(FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(INCLUDE_FLAGS) $(FLAGS)

$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)


.PHONY: all clean run-lsh run-cube run-cluster valgrind-lsh valgrind-cube valgrind-cluster

.SECONDARY: $(OBJ_FILES)

clean:
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*


lsh: $(LSH)

cube: $(CUBE)

cluster: $(CLUSTER)


ARGS_LSH := -d datasets/train-images.idx3-ubyte -q query_file -k 1 -L 2 -o output_file -N 3 -R 3.14

ARGS_CUBE := -d input_file -q query_file -k 1 -M 2 -probes 3 -o output_file -N 4 -R 3.14

ARGS_CLUSTER := -i input_file -c config_file -o output_file -complete -m Classic

run-lsh: lsh
	./$(LSH) $(ARGS_LSH)

run-cube: cube
	./$(CUBE) $(ARGS_CUBE)

run-cluster: cluster
	./$(CLUSTER) $(ARGS_CLUSTER)


VALGRIND_ARGS := --leak-check=full --show-leak-kinds=all --track-origins=yes -s

valgrind-lsh: $(LSH)
	valgrind $(VALGRIND_ARGS) ./$(LSH) $(ARGS_LSH)

valgrind-cube: $(CUBE)
	valgrind $(VALGRIND_ARGS) ./$(CUBE) $(ARGS_CUBE)

valgrind-cluster: $(CLUSTER)
	valgrind $(VALGRIND_ARGS) ./$(CLUSTER) $(ARGS_CLUSTER)
