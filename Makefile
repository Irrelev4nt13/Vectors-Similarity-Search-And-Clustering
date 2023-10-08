CXX := g++
FLAGS = -g3 -Wall

BIN_DIR := bin
BUILD_DIR := build
INCLUDE_DIR := include
MODULES_DIR := modules
SRC_DIR := src

LSH := $(BIN_DIR)/lsh
CUBE := $(BIN_DIR)/cube
CLUSTER := $(BIN_DIR)/cluster

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

MODULES_FILES := $(wildcard $(MODULES_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

OBJ_MODULES := $(patsubst $(MODULES_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(MODULES_FILES))

EXEC_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRC_FILES))


all: $(EXEC_FILES) $(OBJ_MODULES)

$(BUILD_DIR)/%.o: $(MODULES_DIR)/%.cpp
	$(CXX) -c $< -o $@ -I $(INCLUDE_DIR) $(FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ -I $(INCLUDE_DIR) $(FLAGS)

$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(OBJ_MODULES)
	$(CXX) $^ -o $@ -I $(INCLUDE_DIR)

.PHONY: all clean run-lsh run-cube run-cluster valgrind-lsh valgrind-cube valgrind-cluster

.SECONDARY: $(OBJ_FILES)

clean:
	rm -f $(BIN_DIR)/* $(BUILD_DIR)/*

run-lsh: $(LSH)
	./$(LSH)

run-cube: $(CUBE)
	./$(CUBE)

run-cluster: $(CLUSTER)
	./$(CLUSTER)

valgrind-lsh: $(LSH)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(LSH)

valgrind-cube: $(CUBE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(CUBE)

valgrind-cluster: $(CLUSTER)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(CLUSTER)
