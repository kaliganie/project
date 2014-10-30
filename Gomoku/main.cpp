//
// main.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Wed Jun 18 19:18:10 2014 Antoine ROY
// Last update Sun Oct 26 18:05:26 2014 etienne bondot
//

#include "GameEngine.hh"
#include "Menu.hh"

using namespace sf;

int		main(int ac, char **av)
{
  try
    {
      if (av[1] && av[1][0] == '1' && (av[2] == NULL || av[3] == NULL))
	{
	  std::cout << "error param\n";
	  return (0);
	}
  
      if (av[1] && av[1][0] == '1') //online
	{
	  std::string param1(av[2]);
	  std::string param2(av[3]);
	  std::cout << "ici\n";
	  GameEngine::Instance().Save_port_addr(1, param1, param2);
	  GameEngine::Instance().Connection();
	  GameEngine::Instance().loop_online();
	}
      else
	{
	  Menu	m;
	  m.run();

	  // GameEngine::Instance().Save_port_addr(0);
	  // GameEngine::Instance().Connection();
	  // if (av[1] && av[1][0] == '2') //IA
	  //   GameEngine::Instance().loop_IA();
	  // else 
	  //   GameEngine::Instance().loop();
	}
    }
  catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  return (0);
}
