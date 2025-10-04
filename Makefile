# Copyright 2025 Jason Montenegro-Navarro 

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Project build configuration
BINNAME := CatMummies
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DOC_DIR := doc
ASM_DIR := src/asm
CXX := g++
CXXVER := -std=c++17
ASSEMBLY := nasm
INCLUDES := -Isrc -Isrc/utils -Isrc/core -Isrc/entities -Isrc/game -Isrc/handlers -Isrc/states
WARNINGS := -Wall -Wextra

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Raylib dependency resolution (global install preferred)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	INCLUDES += -I/usr/local/include
	LIBS += -L/usr/local/lib -lraylib -lm -ldl -lpthread
endif

ifeq ($(UNAME_S), Darwin)
	INCLUDES += -I/opt/homebrew/include
  LIBS += -L/opt/homebrew/lib -lraylib \
		-framework CoreVideo -framework IOKit -framework Cocoa \
		-framework GLUT -framework OpenGL
endif

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Project build configuration
CXXFLAGS := $(CXXVER) $(INCLUDES) $(WARNINGS)
LDFLAGS := $(LIBS)
ASSEMBLYFLAGS := -f elf64

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Source files
CPP_SRC := $(shell find $(SRC_DIR) -name '*.cpp')
CPP_OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SRC))

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Compile assembly files
ifeq ($(UNAME_S), Linux)
# Fetch all .asm files
    ASM_SRC := $(wildcard $(ASM_DIR)/*.asm)
# Convert .asm to .o files
    ASM_OBJ := $(patsubst $(ASM_DIR)/%.asm, $(BUILD_DIR)/asm/%.o, $(ASM_SRC))

    # Compile .asm files
    $(BUILD_DIR)/asm/%.o: $(ASM_DIR)/%.asm
		@mkdir -p $(dir $@)
		$(ASSEMBLY) $(ASSEMBLYFLAGS) $< -o $@
endif

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Combine all object files
OBJ := $(CPP_OBJ) $(ASM_OBJ)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Default target (debug build)
.PHONY: all
all: debug

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Compile release build
.PHONY: release
release: CXXFLAGS += -O3 -DNDEBUG
release: $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Debug build (no optimizations)
.PHONY: debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Run program in the same directory
.PHONY: run
run: $(BIN_DIR)/$(BINNAME)
	./$(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Build C++ object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Link executable
$(BIN_DIR)/$(BINNAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/$(BINNAME) $(OBJ) $(LDFLAGS)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Lint C++ code
INPUTFC := $(CPP_SRC)
LINTC := +whitespace/braces,+runtime/explicit,-build/include_subdir,-build/header_guard
.PHONY: lint
lint: ## Check code style conformance using Cpplint
	@-cpplint --filter=$(LINTC) $(INPUTFC)

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
	@echo ""
	@echo "Dependencies:"
	@echo "  - Raylib (graphics library)"
	@echo "  - NASM (assembler)"
	@echo "  - g++ (C++ compiler)"
	@echo ""
	