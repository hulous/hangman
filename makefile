CC=g++
CFLAGS=-I.
MYAPP = hangman
DEPS_FOLDER = lib
DEPS = $(DEPS_FOLDER)/$(MYAPP).hpp
OBJ = main.o $(DEPS_FOLDER)/$(MYAPP).o

RM := rm -rf

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(MYAPP): $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

run:
	./$(MYAPP)

clean:
	-$(RM) $(OBJ)
	-@echo ' '

cleanup:
	-$(RM) $(OBJ) $(MYAPP)
	-@echo ' '
