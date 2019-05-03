NAME	=	interpretor
NAMET	=	Test

SRC	=	src/Interpretor.cpp \
		src/CPU.cpp \
		src/RAM.cpp \
		src/LCD.cpp \
		src/utils.cpp \

SRCT	=	test/main.cpp \
				test/CPU_test.cpp \

SRCM	=	src/main.cpp

OBJ	=	$(SRC:.cpp=.o)
OBJT	=	$(SRCT:.cpp=.o)
OBJM	=	$(SRCM:.cpp=.o)

CXX	=	g++ -std=c++11 -g

CXXFLAGS =	-I./include -W -Wall -Wextra -Wno-packed-bitfield-compat

LDFLAGS =	-llua -lm -lsfml-system -lsfml-window -lsfml-graphics -ldl -lpthread

all:		$(NAME)

$(NAME):	$(OBJ) $(OBJM)
		$(CXX) -o $(NAME) $(OBJ) $(OBJM) $(LDFLAGS)

test:		$(OBJ) $(OBJT)
		$(CXX) -o $(NAMET) $(OBJ) $(OBJT) $(LDFLAGS) -lgtest_main  -lgtest

clean:
		rm -f $(OBJ) $(OBJM) $(OBJT)

fclean:		clean
		rm -f $(NAME) $(NAMET)

re:		fclean all
