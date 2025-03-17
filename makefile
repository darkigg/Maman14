# Compilation macros
CC = gcc
CFLAGS = -ansi -Wall -pedantic -g # Flags
# Paths
SRC_PATH = "./SourceFiles/CFiles"
HEADER_PATH = "./SourceFiles/HeaderFiles"
INCLUDE_FLAG = -I"$(HEADER_PATH)"
# All source files
EXE_DEPS = assembler.o analyse_op.o error_handling.o first_passage_support_functions.o instructions.o labels.o output_files_creation.o read_am.o tables.o utilities.o words.o
# Executable
assembler: $(EXE_DEPS)
	$(CC) $(CFLAGS) $(EXE_DEPS) -o $@

# Explicit compilation rules for each object file
assembler.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/assembler.c" $(CFLAGS) -o $@

analyse_op.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/analyse_op.c" $(CFLAGS) -o $@

output_files_creation.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/output_files_creation.c" $(CFLAGS) -o $@

error_handling.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/error_handling.c" $(CFLAGS) -o $@

first_passage_support_functions.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/first_passage_support_functions.c" $(CFLAGS) -o $@

instructions.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/instructions.c" $(CFLAGS) -o $@

labels.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/labels.c" $(CFLAGS) -o $@

read_am.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/read_am.c" $(CFLAGS) -o $@

tables.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/tables.c" $(CFLAGS) -o $@

utilities.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/utilities.c" $(CFLAGS) -o $@

words.o: 
	$(CC) -c $(INCLUDE_FLAG) "$(SRC_PATH)/words.c" $(CFLAGS) -o $@

clean:
	rm -f *.o assembler