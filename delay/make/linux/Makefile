CC=clang
LIBS=-L../../lib/osx -lportaudio
# if running on mac os x you must link these frameworks
#FRAMEWORKS=-framework CoreAudio -framework CoreFoundation  -framework AudioUnit -framework AudioToolbox -framework CoreServices
INCLUDES=-I../../include
SRCDIR=../../src
SOURCES=$(SRCDIR)/ringbuffer.c
OBJECTS:=$(SOURCES:.c=.o)
BINDIR=../../bin/linux
EXECUTABLE=$(BINDIR)/delay_main.out

$(EXECUTABLE): $(SRCDIR)/main.c $(OBJECTS)
	@mkdir -p $(BINDIR)
	@echo "Compiling executable"
	$(CC) $(LIBS) $(FRAMEWORKS) $(INCLUDES) -o $@ $^

$(OBJECTS) : $(SOURCES)
	@echo "Compiling objects"
	$(CC) $(INCLUDES) -c -o $@ $^

clean:
	@echo "Removing intermediate object files"
	rm $(SRCDIR)/*.o

uninstall:
	@echo "Removing exectuable"
	rm $(EXECUTABLE)
