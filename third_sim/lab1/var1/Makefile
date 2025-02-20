TARGET = rbtree.out

CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -g

OBJ = main.o rbtree.o

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CPP) $(CPPFLAGS) $^ -o $@

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) ./*.o