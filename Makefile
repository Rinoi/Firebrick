NAME	=	interpretor

SRC	=	src/main.cpp	\
			src/Interpretor.cpp \
			src/CPU.cpp \
			src/RAM.cpp \
			src/LCD.cpp \

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++ -O3

CXXFLAGS =	-I./include -std=c++11 -g -W -Wall -Wextra -Wno-packed-bitfield-compat

LDFLAGS =	-llua -lm -lsfml-system -lsfml-window -lsfml-graphics -ldl -lpthread

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
