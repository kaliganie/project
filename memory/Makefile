SRC	= main.cpp \
	  GameEngine.cpp


OBJ	= $(SRC:.cpp=.o)


NAME	= Memory



$NAME : all

all : $(OBJ)
	g++ $(SRC) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	 rm -f $(NAME)

re : fclean all
