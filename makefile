
## TO Config ##

FLAGS= -std=c++2a -Wall -O3

LFLAGS=
LIB=-ldl -lmysqlpp -lzmq -lpthread -lPocoNet -lPocoUtil -lPocoFoundation
LINKER=g++

CFLAGS=
INCLUDELIB=-I/usr/include/mysql -I/usr/include
CC=g++

INCDIR=src/include
SRCDIR=src
OBJDIR=target/obj
BINDIR=target

################
## DONT TOUCH ##
################

SRC:= $(shell find $(SRCDIR) -type f -name '*.cpp')
INC:= $(shell find $(INCDIR) -type f -name '*.h')
OBJ:= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
MAINS=$(wildcard $(SRCDIR)/*.main.cpp)
TARGET=$(MAINS:$(SRCDIR)/%.main.cpp=$(BINDIR)/%.out)

all: $(TARGET)

prebuild:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@ln -sf ../assets target/assets

$(BINDIR)/%.out: $(OBJ) prebuild
	@echo "build target : " $(@:$(BINDIR)/%.out=$(OBJDIR)/%.main.o)
	@$(LINKER) $(LFLAGS) $(filter-out %.main.o,$(OBJ)) $(@:$(BINDIR)/%.out=$(OBJDIR)/%.main.o) $(LIB) -o $@ 

$(OBJ) : $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "build : " $@
	@$(CC) $(CFLAGS) $(INCLUDELIB) -I$(INCDIR) -c $< -o $@

clean: all
	rm -rf $(OBJDIR)

clear:
	rm -rf $(BINDIR)
