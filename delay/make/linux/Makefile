CC=clang
LIBS=-L../../lib/osx -lportaudio
# if running on mac os x you must link these frameworks
FRAMEWORKS=-framework CoreAudio -framework CoreFoundation  -framework AudioUnit -framework AudioToolbox -framework CoreServices
INCLUDES=-I../../include
SRCDIR=../../src
BINDIR=../../bin/linux
EXECUTABLE=$(BINDIR)/delay_main.out

SOURCES=$(SRCDIR)/ringbuffer.c $(SRCDIR)/Delay.c $(SRCDIR)/main.c
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE) clean
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(INCLUDES) $(LIBS) $(FRAMEWORKS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	@echo "Removing intermediate object files"
	rm $(SRCDIR)/*.o

uninstall:
	@echo "Removing executable"
	rm $(EXECUTABLE)
