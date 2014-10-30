#include "GameEngine.hh"

int	main(int ac, char **av)
{
  srand(time(NULL));

  if (av[1] && atoi(av[1]) < 3 && atoi(av[1]) > 0)
    GameEngine	game(atoi(av[1]));
  else
    std::cout << "Memory : ./Memory [hard : 1 - 3]" <<  std::endl;
//    GameEngine::Instance().run();
  std::cout << "fin\n";
  return 0;
}
