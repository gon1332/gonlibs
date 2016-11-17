CC=gcc
CFLAGS=-Werror-implicit-function-declaration -Wall -Wextra \
		-pedantic -std=c99 \
		-Iinclude/ -Itests

TEST_OBJS=test__mem_memwrap.o test__adt_stack.o test__adt_dequeue.o
MEM_OBJS=memwrap.o
ADT_OBJS=stack.o dequeue.o
OBJ_FILES=$(ADT_OBJS) $(MEM_OBJS) $(TEST_OBJS) main.o
EXEC=a.out

SURFACE=.
TESTS=./tests
INCLUDE=./include
LIB=$(SURFACE)/lib
BUILD=./build
DOCS=./docs
OBJS = $(addprefix $(BUILD)/, $(OBJ_FILES))

all: prep_build $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

prep_build:
	$(info =======================)
	$(info === Building Executable)
	$(info =======================)
	mkdir -p $(BUILD)

docs:
	$(info ==========================)
	$(info === Building Documentation)
	$(info ==========================)
	mkdir -p $(DOCS)
	doxygen Doxyfile

$(BUILD)/%.o:
	$(CC) $(CFLAGS) -c -o $@ $<


$(BUILD)/test__mem_memwrap.o: $(TESTS)/test__mem_memwrap.c $(TESTS)/tests.h
$(BUILD)/test__adt_stack.o:   $(TESTS)/test__adt_stack.c   $(TESTS)/tests.h
$(BUILD)/test__adt_dequeue.o: $(TESTS)/test__adt_dequeue.c $(TESTS)/tests.h

$(BUILD)/memwrap.o: $(LIB)/MEM/memwrap.c $(INCLUDE)/MEM/memwrap.h
$(BUILD)/stack.o:   $(LIB)/ADT/stack.c   $(INCLUDE)/ADT/stack.h
$(BUILD)/dequeue.o: $(LIB)/ADT/dequeue.c $(INCLUDE)/ADT/dequeue.h


$(BUILD)/main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD)
	rm -rf $(DOCS)
	rm -f  $(EXEC)
