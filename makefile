CC := clang
SDL_DIR := C:/Libraries/SDL2-2.30.10/
TTF_DIR := C:/Libraries/SDL2_ttf-2.22.0/
# GLAD https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=compatibility&loader=on

# project_root/
#   bin/
#   src/**/*.c
#   include/**/*.h

SRC_DIR := src/
INCLUDE_DIR := include/
BIN_DIR := bin/

#
# No need to change anything below here in normal use cases
#

CFLAGS := -Wall -Wextra -std=c99 -Wno-missing-braces
# REMARKS: SDL2 folder structure may be different to yours
CFLAGS += -I$(SDL_DIR)include/ -I$(TTF_DIR)include/ -I$(INCLUDE_DIR)
LDFLAGS := -L$(SDL_DIR)lib/x64/ -L$(TTF_DIR)lib/x64/

LIBS := -lSDL2 -lSDL2main -lSDL2_ttf
# Libraries for SDL2 to work on windows
LIBS += -lole32 -loleaut32 -limm32 -lversion -lShell32
LIBS += -lgdi32 -lwinmm -lsetupapi -luser32 -lkernel32

SRCS := $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)**/*.c)

DEBUG_FLAGS := -g -O1 -UNDEBUG -Xlinker /subsystem:console
RELEASE_FLAGS := -O3 -DNDEBUG -Xlinker /subsystem:console # /subsystem:windows

debug:
	$(CC) -o $(BIN_DIR)$@.exe $(SRCS) $(DEBUG_FLAGS) $(CFLAGS) $(LDFLAGS) $(LIBS)
	./$(BIN_DIR)$@

release:
	$(CC) -o $(BIN_DIR)$@.exe $(SRCS) $(RELEASE_FLAGS) $(CFLAGS) $(LDFLAGS) $(LIBS)