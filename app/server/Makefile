CC = g++
CFLAGS = -std=c++14 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion	\
-Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept		\
-Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo			\
-Wzero-as-null-pointer-constant -Wsuggest-final-types			\
-Wsuggest-final-methods -Wsuggest-override -pthread
DEPS = *.hpp

server.o: main.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

# Run

serve: server.o
	./$<
