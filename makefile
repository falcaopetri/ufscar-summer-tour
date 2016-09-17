# Source: http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
CC := g++
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/Tour

ALLEGRO5_LIB := "../allegro/build/lib"
ALLEGRO5_INC := "../allegro/include"
ALLEGRO5_INC2 := "../allegro/build/include"
ALLEGRO5_INC_ADDONS := $(addprefix -I,$(shell find ../allegro/addons/ -type d -print))

SRCEXT := cpp
SOURCES:=$(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -Wall -std=c++11
LIB := -L$(ALLEGRO5_LIB) -lallegro_dialog -lallegro_image -lallegro_video -lallegro_memfile -lallegro_primitives -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_main -lallegro_physfs -lallegro_ttf -lallegro_font -lallegro -lphysfs
INC := -I include -I$(ALLEGRO5_INC) $(ALLEGRO5_INC_ADDONS) -I$(ALLEGRO5_INC2) -I/usr/include/physfs

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) $(TARGET) $(BUILDDIR)/*"; $(RM) $(TARGET) $(BUILDDIR)/*

.PHONY: clean
