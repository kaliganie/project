//
// GameEngine.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jun 19 18:54:46 2014 Antoine ROY
// Last update Tue Aug 12 22:19:15 2014 Antoine ROY
//

#ifndef	__GAMEENGINE__
#define	__GAMEENGINE__

# include	<cstdlib>
# include	<iostream>
# include	<SFML/Graphics.hpp>
# include	<SFML/Audio.hpp>
# include	<SFML/Window.hpp>
# include	<SFML/System.hpp>
# include	<vector>
# include	<stdio.h>
# include       <sstream>
# include       <fstream>
# include       <sys/types.h>
# include       <sys/socket.h>
# include       <netinet/in.h>
# include       <netinet/ip.h>
# include       <arpa/inet.h>
# include       <netdb.h>
# include       <unistd.h>
# include       <cstring>
# include	"Arbitre.hh"
# include	"Player.hh"
# include	"Singleton.hpp"
# include	"IA.hh"
# include	"Node.hh"

class	Case;
class	Arbitre;
class	IA;

class	GameEngine : public Singleton<GameEngine>
{
public:
  GameEngine();
  ~GameEngine();

private:
  int			sock;

  sf::RenderWindow	window;

  sf::Event		event;

  std::vector<Case >	cases;
  std::vector<std::pair<int, int > >	possible;

  int			online;
  bool			ia;
  bool			rules_pions;
  std::string		port;
  std::string		addr;

  sf::Texture		font;
  sf::Sprite		s_font;
  sf::Texture		center_empty;
  sf::Texture		center_black;
  sf::Texture		center_white;
  sf::Texture		white_winner;
  sf::Texture		black_winner;

  sf::Font		police;
  sf::Text		*have_you;
  sf::Text		*have_him;
  sf::Text		*restart;
  
  Player		*p1;
  Player		*p2;
  Player		*you;

  IA			*p_ia;

  Arbitre		*arbitre;

public:
  Arbitre		*getArbitre();

  void	display_plate();
  void	add_pion_possible(int, int);
  bool	change_case(int, int, std::string const&);
  void	affiche_winner();
  void	xsend(int, std::string);
  std::string	xrecv(int);
  std::string	connect_to_srv(std::string const& port, std::string const& addr);
  void		Connection();
  void		Save_port_addr(int online = 1, std::string const& port = "6667", std::string const& addr = "127.0.0.1");
  bool		Restart_all();

  bool	play_online_other_player(std::string msg);
  bool	play_online(int, int);
  
  bool	play(int, int);
  void	loop();
  void	loop_online();
  void	loop_IA();
  bool	play_with_ia(int, int);

public:

  std::vector<Case >	getCases() const;
  sf::Texture const&	getCenterEmpty() const;
  bool			getRulesPions() const;

};


#endif
