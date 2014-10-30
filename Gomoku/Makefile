##
## Makefile for  in /home/aroy/gomoku
## 
## Made by Antoine ROY
## Login   <aroy@epitech.net>
## 
## Started on  Thu Jun 19 22:24:52 2014 Antoine ROY
## Last update Thu Jul 10 01:15:09 2014 Antoine ROY
##

SRC_CLIENT	= main.cpp \
		  Case.cpp \
	  	  GameEngine.cpp \
	  	  Player.cpp \
	  	  Arbitre.cpp \
		  IA.cpp \
		  Node.cpp \
		  Menu.cpp

OBJ_CLIENT	= $(SRC_CLIENT:.cpp=.o)

NAME_CLIENT	= gomoku





SRC_SERVEUR	= Server.cpp \
	  	  main_srv.cpp

OBJ_SERVEUR	= $(SRC_SERVEUR:.cpp=.o)

NAME_SERVEUR	= srv_gomoku



LIBS	= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


all : $(NAME_CLIENT) $(NAME_SERVEUR)


$(NAME_CLIENT) :  $(OBJ_CLIENT)
		  g++ $(OBJ_CLIENT) -g -o $(NAME_CLIENT) $(LIBS)


$(NAME_SERVEUR) : $(OBJ_SERVEUR)
	 	  g++ $(OBJ_SERVEUR) -o $(NAME_SERVEUR) $(LIBS)

clean :
	  rm -f $(OBJ_CLIENT) $(OBJ_SERVEUR)


fclean : clean
	 rm -f $(NAME_CLIENT) $(NAME_SERVEUR)


re : fclean all
