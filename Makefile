# Copyright 2025 Jason Montenegro-Navarro 

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Project build configuration
APPNAME := Cat_mummies
BINNAME := Cat\ mummies
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DOC_DIR := doc
ASM_DIR := asm
CXX := g++
CXXVER := -std=c++17
ASSEMBLY := nasm
CXXFLAGS := -Wall -Wextra -Isrc
LDFLAGS  :=
DEPS :=#= TODO(any): Add raylib dependencies
ASSEMBLYFLAGS := -f elf64

# Source files
CPP_SRC := $(wildcard $(SRC_DIR)/*.cpp)
CPP_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRC))

# Conditionally include ASM files only if they exist
ASM_SRC := $(wildcard $(ASM_DIR)/*.asm)
ifneq ($(ASM_SRC),)
    ASM_OBJ := $(patsubst $(ASM_DIR)/%.asm,$(BUILD_DIR)/%.o,$(ASM_SRC))
else
    ASM_OBJ :=
endif

# Combine all object files
OBJ := $(CPP_OBJ) $(ASM_OBJ)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Default target (debug build)
.PHONY: all
all: $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Build C++ object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CXXVER) -c $< -o $@

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Build Assembly (ASM) object files (only if ASM_SRC is not empty)
ifneq ($(ASM_SRC),)
$(BUILD_DIR)/%.o: $(ASM_DIR)/%.asm
	@mkdir -p $(BUILD_DIR)
	$(ASSEMBLY) $(ASSEMBLYFLAGS) $< -o $@
endif

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Link executable
$(BIN_DIR)/$(BINNAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) $(LDFLAGS) $(DEPS) -o $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Run program in the same directory
.PHONY: run
run: $(BIN_DIR)/$(BINNAME)
	./$(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Compile release build
.PHONY: release
release: CXXFLAGS += -O3
release: $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Debug build (no optimizations)
.PHONY: debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Lint C++ code
INPUTFC := $(CPP_SRC)
LINTC := +whitespace/braces,+runtime/explicit
.PHONY: lint
lint: ## Check code style conformance using Cpplint
ifneq ($(INPUTFC),)
	@-cpplint --filter=$(LINTC) $(INPUTFC)
endif

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Generate documentation
.PHONY: doc
doc:
	@doxygen Doxyfile

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Clean build files
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(DOC_DIR)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Help
.PHONY: help
help:
	@echo "Available actions:"
	@echo "  make           : Default build (sin optimización)"
	@echo "  make run       : Compiles and runs the program"
	@echo "  make release   : Compiles with -O3 optimization"
	@echo "  make debug     : Compiles with debug symbols"
	@echo "  make lint      : Checks linting warnings with cpplint"
	@echo "  make doc       : Generates doxygen documentation"
	@echo "  make clean     : Deletes build files"
	@echo "  make help      : Shows this action list"