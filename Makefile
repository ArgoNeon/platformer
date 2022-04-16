CXX = g++
CXXFLAGS = -Wall
PROG = game
OBJECT = camera.o map.o  person.o 
OBJ = $(addprefix source/, $(OBJECT)) main.o
SRCDIR = . source
SRC = $(addsuffix /*.cpp, $(SRCDIR))
SFML = -lsfml-graphics -lsfml-window -lsfml-system
 
all: $(PROG)

depend:
	$(CXX) -MM $(CXXFLAGS) $(SRC) > .depend

clean:
	$(RM) $(OBJ) $(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(PROG) $(SFML)
