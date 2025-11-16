# Copyright 2025 Jason Montenegro-Navarro 

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Project build configuration
BINNAME := CaveMummies
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DOC_DIR := doc
RAYLIB_DIR := libs/raylib
RAYLIB_BUILD := $(RAYLIB_DIR)/src
RAYLIB_REPO := https://github.com/raysan5/raylib.git
RAYLIB_READY := $(RAYLIB_DIR)/.built
ASM_DIR := src/asm
CXX := g++
CXXVER := -std=c++17
ASSEMBLY := nasm
WARNINGS := -Wall -Wextra
INCLUDES := -I$(RAYLIB_BUILD) -Isrc -Isrc/utils -Isrc/core \
	-Isrc/entities -Isrc/game -Isrc/handlers -Isrc/states
LIBS := -L$(RAYLIB_BUILD) -lraylib

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Raylib dependency resolution
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	LIBS += -lm -ldl -lpthread
endif

ifeq ($(UNAME_S), Darwin)
  LIBS += -framework CoreVideo -framework IOKit -framework Cocoa \
		-framework GLUT -framework OpenGL
endif

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Project build configuration
CXXFLAGS := $(CXXVER) $(INCLUDES) $(WARNINGS)
LDFLAGS := $(LIBS)
ASSEMBLYFLAGS := -f elf64

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Fetch source files and group together
CPP_SRC := $(shell find $(SRC_DIR) -name '*.cpp')
CPP_OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SRC))

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Compile assembly files
# Adapted from ChatGPT. Date: Sunday 16 November 2025
# prompt: como incluyo compilacion de archivos asm nasm 64 bits en mi makefile
ifeq ($(UNAME_S), Linux)
# Fetch all .asm files
  ASM_SRC := $(shell find $(ASM_DIR) -type f -name '*.asm')
# Convert .asm to .o files
  ASM_OBJ := $(patsubst $(ASM_DIR)/%, $(BUILD_DIR)/asm/%, $(ASM_SRC:.asm=.o))
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
release: raylib $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Debug build (no optimizations)
.PHONY: debug
debug: CXXFLAGS += -g -DDEBUG
debug: raylib $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Run program from root path
.PHONY: run
run: $(BIN_DIR)/$(BINNAME)
	./$(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Build C++ object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Link executable file
$(BIN_DIR)/$(BINNAME): $(OBJ) | $(RAYLIB_READY)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/$(BINNAME) $(OBJ) $(LDFLAGS)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Lint C++ code
INPUTFC := $(CPP_SRC)
LINTC := +whitespace/braces,+runtime/explicit,-build/include_subdir,-build/header_guard,-build/c++11,-whitespace/indent_namespace
.PHONY: lint
lint: ## Check code style conformance using Cpplint
	@-cpplint --filter=$(LINTC) $(INPUTFC)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Generate documentation with doxygen
.PHONY: doc
doc:
	@doxygen Doxyfile
	@echo "Doxygen documentation generated!"

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Clone and build raylib dependency
# Adapted from ChatGPT. Date: Sunday 16 November 2025
# prompt: como clono el repo de raylib en un target para mi makefile
.PHONY: raylib
raylib: $(RAYLIB_READY)

$(RAYLIB_READY):
	@if [ ! -d "$(RAYLIB_DIR)" ]; then \
		git clone --depth 1 $(RAYLIB_REPO) $(RAYLIB_DIR); \
	fi
	@cd $(RAYLIB_BUILD) && make 
	@touch $(RAYLIB_READY)

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
	@echo "  make                    : Default build (builds in debug mode as default)"
	@echo "  make run                : Compiles if needed, and runs the program"
	@echo "  make release            : Compiles a release version"
	@echo "  make debug              : Compiles with debug symbols"
	@echo "  make raylib             : Clones and builds raylib dependency"
	@echo "  make lint               : Checks linting warnings with Cpplint"
	@echo "  make doc                : Generates doxygen documentation"
	@echo "  make clean              : Deletes build files"
	@echo "  make help               : Shows this action list"
	@echo ""
	@echo "Dependencies:"
	@echo "  - NASM (ASM compiler for Linux-based systems)"
	@echo "  - g++ (C++ compiler)"
	@echo "  - Git (version control tool)"
	@echo "  - Make (Build tool)"
	@echo "  - Cpplint (Linting tool required for 'make lint')"
	@echo "  - Doxygen (Documentation tool required for 'make doc')"
	@echo ""
	