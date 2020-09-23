# MAKEFILE

help:
	@echo "============================ Grading =============================="
	@echo ""
	@echo "    \e[7mgrade\e[0m"
	@echo "        grade student's submission"
	@echo ""
	@echo "    \e[7mvalgrade\e[0m"
	@echo "        grade submission with valgrind"
	@echo ""
	@echo "    \e[7mconfig\e[0m"
	@echo "        edit config"
	@echo ""
	@echo "    \e[7medit\e[0m"
	@echo "        edit test cases"
	@echo ""
	@echo "    \e[7mplan\e[0m"
	@echo "        edit grading report"
	@echo ""
	@echo "========================== Development ============================"
	@echo ""
	@echo "    \e[7mscan\e[0m"
	@echo "        view scanned source files"
	@echo ""
	@echo "    \e[7mdebug\e[0m"
	@echo "        view all make variables"
	@echo ""
	@echo "    \e[7mclean\e[0m"
	@echo "        cleans up all extraneous files/folders"
	@echo ""
	@echo "==================================================================="

# compiler
CC = gcc
# editor
EDITOR = vim
# c compiler flags
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -ggdb3 -D"main(...)"="old_basic_main(__VA_ARGS__)"
# valgrind flags
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

# binary name
TARGET_EXEC = seer_exec
# where to build
BUILD_DIR := build
# source file folders
SRC_DIRS := src student instructor
# include directories
INC_DIRS := include student instructor

# create all source file (.c) names
SRCS := $(shell find $(SRC_DIRS) -name *.c)
# create all obj file (.o) names
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# include flags
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# action recipes
.PHONY: grade valgrade config edit plan scan debug clean

# build executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) FORCE_CLEAN
	$(CC) $(OBJS) -o $@

# build c objs
$(BUILD_DIR)/%.c.o: %.c FORCE_CLEAN
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# grade student submission
# TODO: if needed, you may need to redirect user input in using < ./path/to/input.txt
grade: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)

# grade student submission with valgrind
# TODO: if needed, you may need to redirect user input in using < ./path/to/input.txt
valgrade: $(BUILD_DIR)/$(TARGET_EXEC)
	valgrind $(VFLAGS) ./$(BUILD_DIR)/$(TARGET_EXEC) --valgrind

# edit config
config:
	$(EDITOR) ./instructor/config.h

# edit test cases
edit:
	$(EDITOR) ./instructor/test_cases.c

# plan grading scheme
plan:
	$(EDITOR) ./instructor/run_main.c

# scan files 
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

# debug variables
debug:
	$(foreach v, $(.VARIABLES), $(if $(filter file,$(origin $(v))), $(info $(v)=$($(v)))))

# clean extraneous files
clean:
	rm -rf $(BUILD_DIR)/src/*
	rm -rf $(BUILD_DIR)/student/*
	rm -rf $(BUILD_DIR)/instructor/*
	rm -rf $(BUILD_DIR)/$(TARGET_EXEC)

# workaround to force rebuild
FORCE_CLEAN:
