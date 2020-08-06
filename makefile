# compiler
CC = gcc

# c compiler flags
CFLAGS = -std=gnu99 -Wall -Wextra -Wpedantic -ggdb3 -Iinclude -D_CATCH_CRASHES

# valgrind flags
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

# binary name
TARGET_EXEC ?= a.out

# where to build
BUILD_DIR := ./build
# source file folders
SRC_DIRS := ./gryphsig ./student
# include directories
INC_DIRS := ./gryphsig ./student

# create all source file (.c) names
SRCS := $(shell find $(SRC_DIRS) -name *.c)
# create all obj file (.o) names
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# dependencies
DEPS := $(OBJS:.o=.d)
# include flags
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# info
help:
	@echo ""
	@echo "=========================== Gryphsig =============================="
	@echo ""
	@echo "    \e[7mgrade\e[0m"
	@echo "        grade student's submission"
	@echo ""
	@echo "    \e[7medit\e[0m"
	@echo "        edit test cases"
	@echo ""
	@echo "    \e[7mplan\e[0m"
	@echo "        edit grading rules"
	@echo ""
	@echo "=========================== Internal =============================="
	@echo ""
	@echo "    \e[7mclean\e[0m"
	@echo "        cleans up all extraneous files/folders"
	@echo ""
	@echo "    \e[7mtest\e[0m"
	@echo "        run internal tests"
	@echo ""
	@echo "==================================================================="

# build executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# build c objs
$(BUILD_DIR)/%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test clean

test: $(BUILD_DIR)/gryphsig.c.o
	@echo "hello"

clean:
	rm -rf $(BUILD_DIR)/*