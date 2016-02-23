CXX = g++-5
CXXFLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion	\
-Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept		\
-Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo			\
-Wzero-as-null-pointer-constant -Wsuggest-final-types			\
-Wsuggest-final-methods -Wsuggest-override
LINKERFLAGS = -pthread -lpanel -lform -lncurses
GEN_DEPS = -MMD -MP
INCLUDE_ROOT_DIR = -isystem./include/ -idirafter.

CXXFLAGS += $(GEN_DEPS) $(INCLUDE_ROOT_DIR)

SERVER_DIR = server
CLIENT_DIR = client
COMMON_DIR = common

DOCU_DIR = ../docu

.PHONY: clean tests all
all: server_wizard client_wizard

SRC_S = $(wildcard $(SERVER_DIR)/*.cpp)
SRC_S += $(wildcard $(COMMON_DIR)/*.cpp)
OBJ_S = $(SRC_S:.cpp=.o)
DEP_S = $(SRC_S:.cpp=.d)
-include $(DEP_S)		# Hyphen ignores errors

server_wizard: $(OBJ_S)
	$(CXX) -o $@ $^ $(LINKERFLAGS)

SRC_C = $(wildcard $(CLIENT_DIR)/*.cpp)
SRC_C += $(wildcard $(CLIENT_DIR)/CLI/*.cpp)		# Don't compile subdir by default
SRC_C += $(wildcard $(CLIENT_DIR)/GUI/*.cpp)		# Don't compile subdir by default
SRC_C += $(wildcard $(COMMON_DIR)/*.cpp)
OBJ_C = $(SRC_C:.cpp=.o)
DEP_C = $(SRC_C:.cpp=.d)
-include $(DEP_C)		# Hyphen ignores errors

client_wizard: $(OBJ_C)
	$(CXX) -o $@ $^ $(LINKERFLAGS)

clean:
	rm -f $(OBJ_S) $(DEP_S) 2> /dev/null
	rm -f $(OBJ_C) $(DEP_C) 2> /dev/null

# Tests
tests:
	@echo Hello world

# Documentation
docu:
	doxygen doxygen.conf
	$(MAKE) -C $(DOCU_DIR)/latex
clean-docu:
	rm -rf $(DOCU_DIR) 2> /dev/null
