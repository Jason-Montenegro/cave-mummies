# Copyright 2025 Jason Montenegro-Navarro 

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Project build configuration
BINNAME := CaveMummies
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DOC_DIR := doc
RAYLIB_DIR := libs/raylib
RAYLIB_BUILD := $(RAYLIB_DIR)/build
RAYLIB_REPO := https://github.com/raysan5/raylib.git
RAYLIB_INSTALL := $(RAYLIB_DIR)/install
RAYLIB_READY := $(RAYLIB_INSTALL)/.built
ASM_DIR := src/asm
CXX := g++
CXXVER := -std=c++17
ASSEMBLY := nasm
WARNINGS := -Wall -Wextra
INCLUDES := -I$(RAYLIB_INSTALL)/include -Isrc -Isrc/utils -Isrc/core \
	-Isrc/entities -Isrc/game -Isrc/handlers -Isrc/states
LIBS := -L$(RAYLIB_INSTALL)/lib -lraylib

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
release: raylib $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Debug build (no optimizations)
.PHONY: debug
debug: CXXFLAGS += -g -DDEBUG
debug: raylib $(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Run program in the same directory
.PHONY: run
run: raylib $(BIN_DIR)/$(BINNAME)
	./$(BIN_DIR)/$(BINNAME)

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Build C++ object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*-
# Link executable
$(BIN_DIR)/$(BINNAME): $(OBJ) | $(RAYLIB_READY)
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
.PHONY: raylib
raylib: $(RAYLIB_READY)

$(RAYLIB_READY):
	@if [ ! -d "$(RAYLIB_DIR)" ]; then \
		git clone --depth 1 $(RAYLIB_REPO) $(RAYLIB_DIR); \
	fi
	@mkdir -p $(RAYLIB_BUILD)
	@cd $(RAYLIB_BUILD) && LDFLAGS= CFLAGS= CXXFLAGS= CPATH= LIBRARY_PATH= \
		cmake -DBUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_INSTALL_PREFIX=$(abspath $(RAYLIB_INSTALL)) \
		$(abspath $(RAYLIB_DIR))
	@cd $(RAYLIB_BUILD) && LDFLAGS= CFLAGS= CXXFLAGS= CPATH= LIBRARY_PATH= \
		make install
	@find $(RAYLIB_DIR) -mindepth 1 -maxdepth 1 \
		! -name 'install' -exec rm -rf {} +
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
	@echo "  make           : Default build (no optimization)"
	@echo "  make run       : Compiles and runs the program"
	@echo "  make release   : Compiles a release version"
	@echo "  make debug     : Compiles with debug symbols"
	@echo "  make raylib    : Clones and builds raylib dependency"
	@echo "  make lint      : Checks linting warnings with cpplint"
	@echo "  make doc       : Generates doxygen documentation"
	@echo "  make clean     : Deletes build files"
	@echo "  make help      : Shows this action list"
	@echo ""
	@echo "Dependencies:"
	@echo "  - NASM (assembler)"
	@echo "  - g++ (C++ compiler)"
	@echo "  - git (version control)"
	@echo "  - CMake (Build tool)"
	@echo ""
	@echo "Install all dependencies on your system before attempting compilation."
	@echo ""
	