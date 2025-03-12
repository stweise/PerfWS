CC=gcc
CFLAGS= -Wall -O3 -march=native 
LDFLAGS:= 
INCLUDES:= -I. 
SOURCES = main.c timing.c
EXECUTABLE := matrix.x
all: $(LSOURCES) $(EXECUTABLE) 

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
DEPS = $(patsubst %.o,%.d,$(OBJECTS))

$(OBJECTS): %.o: %.c
	$(CC) -c -MMD -MP $(INCLUDES) $(CFLAGS) $< -o $@
	@sed -i-e '1s,\($*\)\.o[ :]*,\1.o $*.d: ,' $*.d

-include $(DEPS)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
clean:
	-rm -f *.[do] *.d-e 
	-rm -f $(EXECUTABLE)
