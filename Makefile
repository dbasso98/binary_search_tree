EXE = binary_search_tree.x
CXX = g++
CXXFLAGS = -I include -g -std=c++17 -Wall -Wextra

SRC= binary_search_tree.cpp
OBJ=$(SRC:.cpp=.o)
INC = include/bst.hpp  include/node.hpp  include/iterator.hpp

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

clean:
	rm -rf $(OBJ) $(EXE) include/*~ *~ html latex

.PHONY: clean

# %.o: %.cpp ap_error.h
# 	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation

binary_search_tree.o: include/node.hpp include/bst.hpp include/iterator.hpp

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
