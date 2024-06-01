ifeq ($(OS), Windows_NT)
	EXECUTABLE = bin/test.exe
else
	EXECUTABLE = bin/test
endif

all: $(EXECUTABLE)

$(EXECUTABLE): src/test.c
	gcc src/test.c -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

