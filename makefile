# compiler
CC = gcc
# editor
EDITOR = vim
# c compiler flags
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -ggdb3
# valgrind flags
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

# binary name
TARGET_EXEC = seer_exec
# where to build
BUILD_DIR := build
# source file folders
SRC_DIRS := seer student instructor
# include directories
INC_DIRS := seer student instructor

# create all source file (.c) names
SRCS := $(shell find $(SRC_DIRS) -name *.c)
# create all obj file (.o) names
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# include flags
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# info
help:
	@echo "=========================== Gryphsig =============================="
	@echo ""
	@echo "    \e[7mgrade\e[0m"
	@echo "        grade student's submission"
	@echo ""
	@echo "    \e[7mvalgrade\e[0m"
	@echo "        grade submission with valgrind"
	@echo ""
	@echo "    \e[7medit\e[0m"
	@echo "        edit test cases"
	@echo ""
	@echo "    \e[7mplan\e[0m"
	@echo "        edit grading calculations"
	@echo ""
	@echo "=========================== Internal =============================="
	@echo ""
	@echo "    \e[7mclean\e[0m"
	@echo "        cleans up all extraneous files/folders"
	@echo ""
	@echo "    \e[7mscan\e[0m"
	@echo "        view scanned source files"
	@echo ""
	@echo "    \e[7mtest\e[0m"
	@echo "        run internal tests"
	@echo ""
	@echo "==================================================================="

scan:
	@echo "\e[7msrcs\e[0m"
	@printf "    "
	@echo $(SRCS) | sed 's/ /\n    /g'
	@echo ""
	@echo "\e[7mobjs\e[0m"
	@printf "    "
	@echo $(OBJS) | sed 's/ /\n    /g'
	@echo ""
	@echo "\e[7mincl\e[0m"
	@printf "    "
	@echo $(INC_FLAGS) | sed 's/ /\n    /g'

grade: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)

valgrade: $(BUILD_DIR)/$(TARGET_EXEC)
	valgrind $(VFLAGS) ./$(BUILD_DIR)/$(TARGET_EXEC)

# build executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# build c objs
$(BUILD_DIR)/%.c.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: test clean edit

test: $(BUILD_DIR)/gryphsig.c.o
	@echo "hello"

edit:
	$(EDITOR) ./instructor/test_cases.c

plan:
	$(EDITOR) ./instructor/run_main.c

clean:
	rm -rf $(BUILD_DIR)/seer/*
	rm -rf $(BUILD_DIR)/student/*
	rm -rf $(BUILD_DIR)/instructor/*
	rm -rf $(BUILD_DIR)/$(TARGET_EXEC)
