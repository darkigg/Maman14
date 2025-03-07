# Compilation macros
CC = gcc
CFLAGS = -ansi -Wall -pedantic -g # Flags
# Paths
SRC_PATH = "./SourceFiles/CFiles"
HEADER_PATH = "./SourceFiles/HeaderFiles"
INCLUDE_FLAG = -I"$(HEADER_PATH)"
# All source files
EXE_DEPS = assembler.o compileFunc.o create_output_files.o errorHandling.o first_passage.o \
           instructions.o labels.o macros.o read_am.o second_passage.o tables.o utilities.o words.o
# Executable
assembler: $(EXE_DEPS)
	$(CC) $(CFLAGS) $(EXE_DEPS) -o $@

# Explicit compilation rules for each object file
assembler.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/assembler.c" $(CFLAGS) -o $@

compileFunc.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/compileFunc.c" $(CFLAGS) -o $@

create_output_files.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/create_output_files.c" $(CFLAGS) -o $@

errorHandling.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/errorHandling.c" $(CFLAGS) -o $@

first_passage.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/first_passage.c" $(CFLAGS) -o $@

instructions.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/instructions.c" $(CFLAGS) -o $@

labels.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/labels.c" $(CFLAGS) -o $@

macros.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/macros.c" $(CFLAGS) -o $@

read_am.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/read_am.c" $(CFLAGS) -o $@

second_passage.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/second_passage.c" $(CFLAGS) -o $@

tables.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/tables.c" $(CFLAGS) -o $@

utilities.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/utilities.c" $(CFLAGS) -o $@

words.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/words.c" $(CFLAGS) -o $@

clean:
	rm -f *.o assembler