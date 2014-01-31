UNAME = $(shell uname)

# Compiler:
CC = g++

# Flags:
# -Wall -pedantic
CFLAGS = -O3 -s

# More flags:
ifeq ($(UNAME), Darwin)
	FRAMEWORKS = -lsgct -framework Opengl -framework Cocoa -framework IOKit -stdlib=libstdc++
else
	FRAMEWORKS = -lsgct32 -lopengl32 -lglu32 -lgdi32 -lws2_32 -static-libgcc -static-libstdc++
endif

# Even more flags:
ifeq ($(UNAME), Darwin)
	MKDIR_FLAGS = -p 
	LIBFOLD = -L"/opt/local/lib"
	INCFOLD = -I"/opt/local/include"
else
	MKDIR_FLAGS = asd
	LIBFOLD = -L"C:\sgct\lib"
	INCFOLD = -I"C:\sgct\include"
endif

# Files:
ifeq ($(UNAME), Darwin)
	FILES = src/*.cpp
else
	FILES = src\*.cpp
endif

#Binary folder:
ifeq ($(UNAME), Darwin)
	BINFOLD = bin/
else
	BINFOLD = bin\\
endif

# Binary name:
BINNAME = main

all: compile
.PHONY: all

compile: $(FILES)
	mkdir $(MKDIR_FLAGS)$(BINFOLD)
	$(CC) $(CFLAGS) $(FILES) -o $(BINFOLD)$(BINNAME) $(LIBFOLD) $(INCFOLD) $(FRAMEWORKS)
.PHONY: compile

run:
	./$(BINFOLD)$(BINNAME) -config "configs/single.xml"
.PHONY: run

clean:
	rm -f $(BINFOLD)*
.PHONY: clean
