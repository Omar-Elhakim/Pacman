
H_FILES := $(wildcard ./Header_files/*)
C_FILES := $(wildcard ./Source_files/*)
C_FLAGS := -g
LINK := -lraylib

CC := g++

build: $(H_FILES) $(C_FILES)
	$(CC) $(CXX_FLAGS) -o game $(C_FILES) $(LINK)

