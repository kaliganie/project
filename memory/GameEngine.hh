#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace	sf;

class	GameEngine
{
public:
  GameEngine(int);
  ~GameEngine();

private:
  int		hard;
  int		score;
  bool		your_turn;
  int		nb_clic;
  std::vector<int>	memory;
  Sprite	s_red;
  Sprite	s_blue;
  Sprite	s_green;
  Sprite	s_yellow;

  Texture	t_red;
  Texture	t_red_p;
  Texture	t_blue;
  Texture	t_blue_p;
  Texture	t_green;
  Texture	t_green_p;
  Texture	t_yellow;
  Texture	t_yellow_p;

  SoundBuffer	b0;
  SoundBuffer	b1;
  SoundBuffer	b2;
  SoundBuffer	b3;

  Sound		s0;
  Sound		s1;
  Sound		s2;
  Sound		s3;

  RenderWindow	app;

public:
  void	run();
  void	print_screen();
  void	reset_screen();
  void	add_new_touch();
  void	auto_show();
  void	verif_change_color(int);
  bool	check_clic(int);

  void	change_red();
  void	change_green();
  void	change_blue();
  void	change_yellow();
};
