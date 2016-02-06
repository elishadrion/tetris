CC = g++
CPPFLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion	\
-Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept		\
-Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo			\
-Wzero-as-null-pointer-constant -Wsuggest-final-types			\
-Wsuggest-final-methods -Wsuggest-override -pthread
CPPFLAGS += -MMD -MP		# Gen dependencies
S_DIR = server
C_DIR = client

.PHONY: clean tests all
all: server_wizard client_wizard


SRC_S=$(wildcard $(S_DIR)/*.cpp)
OBJ_S=$(SRC_S:.cpp=.o)
DEP_S=$(SRC_S:.cpp=.d)
-include $(DEP_S)		# Hyphen ignores errors

server_wizard: $(OBJ_S)
	$(CC) -o $@ $^

SRC_C = $(wildcard $(C_DIR)/*.cpp)
OBJ_C = $(SRC_C:.cpp=.o)
DEP_C = $(SRC_C:.cpp=.d)
-include $(DEP_C)		# Hyphen ignores errors

client_wizard: $(OBJ_C)
	$(CC) -o $@ $^



clean:
	rm -f $(OBJ_S) $(DEP_S) 2> /dev/null
	rm -f $(OBJ_C) $(DEP_C) 2> /dev/null

# Tests
tests:
	@echo Hello world
