CC = g++
CFLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion	\
-Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept		\
-Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo			\
-Wzero-as-null-pointer-constant -Wsuggest-final-types			\
-Wsuggest-final-methods -Wsuggest-override -pthread
DEPS = *.hpp
S_DIR = server
C_DIR = client

compile: server.o client.o

server.o: $(S_DIR)/main.cpp $(S_DIR)/$(DEPS)
	$(CC) $(CFLAGS) $< -o $@

client.o: $(C_DIR)/main.cpp $(C_DIR)/$(DEPS)
	$(CC) $(CFLAGS) $< -o $@

# Run

serve: server.o
	./$<

connect: client.o
	./$< $1
