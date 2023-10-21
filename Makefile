CXX := g++
FLAGS = -std=c++11
RELEASE_FLAGS := -O2
DEVELOPMENT_FLAGS := -g3
DEBUG_FLAGS := -g3 -DDEBUG

FLAGS += $(DEVELOPMENT_FLAGS)

BIN_DIR := bin
BUILD_DIR := build
MODULES_DIR := modules
SRC_DIR := src
TESTS_DIR := tests

LSH_TEST := $(BIN_DIR)/lsh_test
CUBE_TEST := $(BIN_DIR)/cube_test
CLUSTER_TEST := $(BIN_DIR)/cluster_test

LSH_OBJ_TEST := $(BUILD_DIR)/lsh-test.o
CUBE_OBJ_TEST := $(BUILD_DIR)/cube-test.o
CLUSTER_OBJ_TEST := $(BUILD_DIR)/cluster-test.o

LSH := $(BIN_DIR)/lsh_main
CUBE := $(BIN_DIR)/cube_main
CLUSTER := $(BIN_DIR)/cluster_main

LSH_OBJ := $(BUILD_DIR)/lsh_main.o
CUBE_OBJ := $(BUILD_DIR)/cube_main.o
CLUSTER_OBJ := $(BUILD_DIR)/cluster_main.o

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
MODULES_FILES := $(shell find $(MODULES_DIR) -name '*.cpp')
LIBS := $(shell find $(MODULES_DIR) -name '*.hpp')

LSH_MODULES := $(shell find $(MODULES_DIR)/Lsh -name '*.cpp')
CUBE_MODULES := $(shell find $(MODULES_DIR)/Cube -name '*.cpp')
CLUSTER_MODULES := $(shell find $(MODULES_DIR)/Cluster -name '*.cpp')
COMMON_MODULES := $(shell find $(MODULES_DIR)/Common -name '*.cpp')

LSH_OBJ_MODULES := $(LSH_MODULES:$(MODULES_DIR)/Lsh/%.cpp=$(BUILD_DIR)/Lsh/%.o)
CUBE_OBJ_MODULES := $(CUBE_MODULES:$(MODULES_DIR)/Cube/%.cpp=$(BUILD_DIR)/Cube/%.o)
CLUSTER_OBJ_MODULES := $(CLUSTER_MODULES:$(MODULES_DIR)/Cluster/%.cpp=$(BUILD_DIR)/Cluster/%.o)
COMMON_OBJ_MODULES := $(COMMON_MODULES:$(MODULES_DIR)/Common/%.cpp=$(BUILD_DIR)/Common/%.o)

OBJ_MODULES_DEBUG := $(MODULES_FILES:$(MODULES_DIR)/%.cpp=$(BUILD_DIR)/%-deb.o)

EXEC_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)
INCLUDE_DIRS := $(shell find $(MODULES_DIR) -type d)
INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIRS) $(MODULES_DIR))

MAKEFLAGS += -j8

all: $(EXEC_FILES) $(LSH_TEST) $(CUBE_TEST) $(CLUSTER_TEST)

$(BUILD_DIR)/%.o: $(MODULES_DIR)/%.cpp $(LIBS)
	@mkdir -p $(@D)
	$(CXX) -c $(filter-out %.hpp, $<) -o $@ $(INCLUDE_FLAGS) $(FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIBS)
	$(CXX) -c $(filter-out %.hpp, $<) -o $@ $(INCLUDE_FLAGS) $(FLAGS)

$(LSH): $(LSH_OBJ) $(LSH_OBJ_MODULES) $(COMMON_OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)

$(CUBE): $(CUBE_OBJ) $(CUBE_OBJ_MODULES) $(COMMON_OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)

$(CLUSTER): $(CLUSTER_OBJ) $(CLUSTER_OBJ_MODULES) $(COMMON_OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)

$(BUILD_DIR)/%-test.o: $(TESTS_DIR)/%_test.cpp $(LIBS)
	$(CXX) -c $(filter-out %.hpp, $<) -o $@ $(INCLUDE_FLAGS) $(FLAGS)

$(LSH_TEST): $(LSH_OBJ_TEST) $(LSH_OBJ_MODULES) $(COMMON_OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)

$(CUBE_TEST): $(CUBE_OBJ_TEST) $(CUBE_OBJ_MODULES) $(COMMON_OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)

$(CLUSTER_TEST): $(CLUSTER_OBJ_TEST) $(CLUSTER_OBJ_MODULES) $(COMMON_OBJ_MODULES)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS)

.PHONY: all clean lsh cube cluster tests test-lsh test-cube test-cluster run-lsh run-cube run-cluster \
valgrind-lsh valgrind-cube valgrind-cluster deb-lsh deb-cube deb-cluster hpp_dependencies

clean:
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*

lsh: $(LSH)

cube: $(CUBE)

cluster: $(CLUSTER)

tests: $(LSH_TEST) $(CUBE_TEST) $(CLUSTER_TEST)

test-lsh: $(LSH_TEST)

test-cube: $(CUBE_TEST)

test-cluster: $(CLUSTER_TEST)

ARGS_LSH := -d datasets/train-images.idx3-ubyte -q datasets/t10k-images.idx3-ubyte -k 4 -L 5 -o output.txt -N 1 -R 10000

ARGS_CUBE := -d datasets/train-images.idx3-ubyte -q datasets/t10k-images.idx3-ubyte -k 14 -M 10 -probes 2 -o output.txt -N 1 -R 10000

ARGS_CLUSTER := -i datasets/t10k-images.idx3-ubyte -c conf/cluster.conf -o output.txt  -m Classic

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


$(BUILD_DIR)/%-deb.o: $(MODULES_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $< -o $@ $(INCLUDE_FLAGS) $(DEBUG_FLAGS)

$(BUILD_DIR)/%-deb.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(INCLUDE_FLAGS) $(DEBUG_FLAGS)

$(BIN_DIR)/%-deb: $(BUILD_DIR)/%-deb.o $(OBJ_MODULES_DEBUG)
	$(CXX) $^ -o $@ $(INCLUDE_FLAGS) $(DEBUG_FLAGS)

deb-lsh: clean $(LSH)-deb

deb-cube: clean $(CUBE)-deb

deb-cluster: clean $(CLUSTER)-deb
