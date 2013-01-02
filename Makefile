# Makefile for task: Predictive text 

include config.in

HEADERS = Prompter.hpp CharDomen.hpp CharTree.hpp
OBJECTS = main.o

OBJ = $(patsubst %,$(BUILDDIR)/%,$(OBJECTS))
DEPS = $(patsubst %,$(SRCDIR)/%,$(HEADERS))

.PHONY: all clean install

all: create_dirs $(TARGET)

create_dirs:
	$(shell mkdir -p $(BINDIR) &> /dev/null)
	$(shell mkdir -p $(BUILDDIR) &> /dev/null)

$(TARGET): $(OBJ)
	$(LINK) $(LDFLAGS) -o $(TARGET) $(OBJ) $(LIBPATH) $(LIBS) 

install: $(TARGET)
	$(shell mkdir -p $(DESTDIR) &> /dev/null)
	install -m0755 $(TARGET) $(DESTDIR)/

##########################################################################
#
# general rules
#
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

clean:
	rm -f -r $(OBJECTS)
	rm -f $(TARGET)
	rm -r $(BINDIR)
	rm -r $(BUILDDIR)
