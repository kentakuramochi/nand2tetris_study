CXX      := g++
CXXFLAGS  = -Wall -Werror -Wextra -Wpedantic -std=c++11 -I$(INCDIR)

SRCDIR := ./src
INCDIR := ./include
BINDIR := ./bin

PROG = $(BINDIR)/asm
SRCS = $(SRCDIR)/Parser.cpp \
	$(SRCDIR)/Code.cpp \
	$(SRCDIR)/SymbolTable.cpp \
	$(SRCDIR)/Main.cpp
OBJS = $(subst $(SRCDIR), $(BINDIR), $(SRCS:.cpp=.o))

RM := rm -rf

.PHONY: all dir clean

all: dir $(PROG)

dir:
	@mkdir -p $(BINDIR)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -O2 $(INCLUDE) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

clean:
	$(RM) $(BINDIR)
