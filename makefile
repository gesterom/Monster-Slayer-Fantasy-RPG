
TARGET=a.out

FLAGS= -std=c++2a -Wall -O3

LFLAGS=
LIB=-ldl -lmysqlpp -lzmq
LINKER=g++

CFLAGS=
INCLUDELIB=-I/usr/include/mysql
CC=g++

INCDIR=src/include
SRCDIR=src
OBJDIR=target/obj
BINDIR=target

SRC:= $(wildcard $(SRCDIR)/*.cpp)
INC:= $(wildcard $(INCDIR)/*.h)
OBJ:= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJ)
	ln -sf ../assets target/assets
	$(LINKER) $(LFLAGS) $(OBJ) $(LIB) -o $@ 

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDELIB) -I$(INCDIR) -c $< -o $@

clear:
	rm -f a.out
