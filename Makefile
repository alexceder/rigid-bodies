# Compiler:
CC = g++

# Flags:
# -Wall -pedantic
CFLAGS = -O3

# More flags:
FRAMEWORKS = -lsgct -framework Opengl -framework Cocoa -framework IOKit -stdlib=libstdc++

# Even more flags:
LIBFOLD = -L"/opt/local/lib"
INCFOLD = -I"/opt/local/include"

# Files:
FILES = src/*.cpp

# Binary folder:
BINFOLD = bin/

# Binary name:
BINNAME = main

all: compile
.PHONY: all

compile: $(FILES)
	mkdir -p $(BINFOLD)
	$(CC) $(CFLAGS) $(FILES) -o $(BINFOLD)$(BINNAME) $(LIBFOLD) $(INCFOLD) $(FRAMEWORKS)
.PHONY: compile

run:
	./$(BINFOLD)$(BINNAME) -config "configs/single.xml"
.PHONY: run

run-double:
	./$(BINFOLD)$(BINNAME) -config "configs/double.xml" -local 0
.PHONY: run

run-double-second:
	./$(BINFOLD)$(BINNAME) -config "configs/double.xml" -local 1 --slave
.PHONY: run

clean:
	rm $(BINFOLD)*
.PHONY: clean



