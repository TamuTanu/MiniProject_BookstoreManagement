CC = gcc
PKG = pkg-config
CFLAGS = `$(PKG) --cflags gtk4` -Iheaders -Ithirdparty -Wall -g -MMD -MP 
LDFLAGS = `$(PKG) --libs gtk4` 

SRC = $(wildcard src/*.c) thirdparty/sqlite3.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
TARGET = gtkapp

# Windows cross-compile
WINCC = x86_64-w64-mingw32-gcc
WINPKG = x86_64-w64-mingw32-pkg-config
WINCFLAGS = `$(WINPKG) --cflags gtk4` -Iheaders -Ithirdparty -Wall -g -MMD -MP
WINLDFLAGS = `$(WINPKG) --libs gtk4` -mwindows

WINOBJ = $(SRC:.c=.win.o)
WINTARGET = winbuild/gtkapp.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.win.o: %.c
	$(WINCC) $(WINCFLAGS) -c $< -o $@

# -----------------------------
# Windows build section
# -----------------------------
win: $(WINTARGET)

$(WINTARGET): $(WINOBJ)
	mkdir -p $(dir $@)
	$(WINCC) -o $@ $^ $(WINLDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o src/*.d thirdparty/*.o thirdparty/*.d \
	      src/*.win.o thirdparty/*.win.o \
	      $(TARGET) winbuild/*.exe

