CC = g++
CFLAGS = -I./headers
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# List of source files
SRCS = main.cpp ./source/Grid.cpp ./source/Organism.cpp ./source/Game.cpp ./source/Vars.cpp ./source/Gui.cpp ./source/Stats.cpp ./source/Food.cpp ./source/GameWorld.cpp ./source/Maps.cpp

# Generate corresponding object file names
OBJS = $(SRCS:%.cpp=%.o)

# Name of the final executable
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
