PROJECT_NAME = s21_containers

CXX = g++

# PROJECT DIRS
OBJ_DIR = ./obj
MODULES_DIR = ./
MODULES_HEADERS = ./headers
TEST_DIR = ./tests
DVI_DIR = ./../docs

# MAIN FLAGS FOR COMPILER
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -std=c++17

# CHECK LIBRARY FOR LINKING
LDFLAGS = -lgtest -lgtest_main

# FLAGS FOR VALGRING TEST
VAL = --tool=memcheck --leak-check=full

# FLAGS FOR CPPCHECK TEST
CPPCHECK = --enable=all --suppressions-list=supp_list.txt --language=c++

TARGET = main_test

MAIN_H = $(shell find ./ -maxdepth 1 -name "*.h")

MODULES_DIRS = $(shell find $(MODULES_DIR)  -type d)
MODULES_TPP = $(shell find $(MODULES_DIRS) -type f -name "*.tpp")
MODULES_H = $(shell find $(MODULES_HEADERS) -type f -name "*.h")
MODULES_O = $(notdir $(MODULES_TPP:%.tpp=%.o))
MODULES_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(MODULES_O))

TEST_DIRS = $(shell find $(TEST_DIR) -type d)
TEST_CPP = $(shell find $(TEST_DIR) -type f -name "*.cc")
TEST_H = $(shell find $(TEST_DIR) -type f -name "*.h")
TEST_O = $(notdir $(TEST_CPP:%.cc=%.o))
TEST_OO = $(TEST_O) $(MODULES_O)
TEST_OBJ_PATH = $(OBJ_DIR)/*_test.o
EXCLUDE = $(filter-out $(wildcard $(MODULES_DIR)/debug/*),$(MODULES_TPP))

CPP_FILES = $(MODULES_TPP) $(TEST_CPP)
H_FILES = $(MODULES_H) $(MAIN_H) $(TEST_H)
ALL_FILES = $(CPP_FILES) $(H_FILES)

vpath %.cc $(TEST_DIRS)
vpath %.o $(OBJ_DIR)

.PHONY: $(TARGET)

all: clean $(TARGET)

$(TARGET): $(OBJ_DIR) $(TEST_O)
	$(CXX) $(TEST_OBJ_PATH) $(LDFLAGS) -o $@
	@-./$@

dvi:
	rm -rf $(DVI_DIR)
	doxygen Doxyfile
#	xdg-open $(DVI_DIR)/html/index.html

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(DVI_DIR)
	@rm -f $(TARGET)
	@rm -f *.o

rebuild: clean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

%.o: %.cc ${MODULES_H}
	$(CXX) $(CXXFLAGS) -c -o $(addprefix ${OBJ_DIR}/, $@) $<

%_test.o: %_test.cc
	$(CXX) $(CXXFLAGS) -c -o $(addprefix ${OBJ_DIR}/, $@) $<
	
clang_check:
	clang-format -style=Google -n $(ALL_FILES)

valgrind: $(TARGET)
	$@ $(VAL) ./$(TARGET)

clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

cppcheck:
	$@ $(CPPCHECK) $(MODULES_TPP) $(MODULES_H) $(MODULES_DIR)*.h

dependencies:
	sudo apt-get install libgtest-dev
	sudo apt install doxygen
	sudo apt-get install graphviz