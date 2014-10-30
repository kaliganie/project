//
// IA.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Wed Sep  3 20:35:17 2014 Antoine ROY
// Last update Thu Sep 11 20:50:49 2014 Antoine ROY
//

# include "IA.hh"

IA::IA(int _c, bool b, int hard) : Player(_c, b)
{
  depth = hard;
}

IA::~IA()
{}

int	IA::getX() const
{
  return x;
}

int	IA::getY() const
{
  return y;
}

bool	IA::play(std::vector<Case > &plate, std::vector<std::pair<int, int> > &poss)
{
  std::cout << "ia play()" << std::endl;
  int	nb;
  if (depth == 0)
    {
      std::vector<std::pair<int, int> >::iterator	it = poss.begin();
      nb = rand() % poss.size();
      std::cout << "ia choose : " << nb << " sur " << poss.size() << std::endl;
      while (nb > 0)
	{
	  it++;
	  nb--;
	}
      std::cout << "ia push on : " << (*it).first << " and " << (*it).second << std::endl;
      x = (*it).first * 50;
      y = (*it).second * 50;
      turn = false;
      return true;
    }
  first_node = new Node(plate, poss, 1);
  first_node->play();
  return true;
}

