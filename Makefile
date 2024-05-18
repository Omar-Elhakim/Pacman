
H_FILES := $(wildcard ./Header_files/*)
C_FILES := $(wildcard ./Source_files/*)
C_FLAGS := -g -Wall -Wextra -Wno-enum-compare -Wno-missing-field-initializers
LINK := -lraylib

CC := g++

build: $(H_FILES) $(C_FILES)
	$(CC) $(C_FLAGS) -o game $(C_FILES) $(LINK)

