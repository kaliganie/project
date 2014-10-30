//
// Arbitre.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sat Jun 21 15:15:39 2014 Antoine ROY
// Last update Tue Aug 12 21:20:43 2014 Antoine ROY
//

#include "GameEngine.hh"

Arbitre::Arbitre(std::vector<Case > &cases, int rules1, int rules2)
{
  cp_cases = &cases;
  rules_taked = rules1;
  rules_five_b = rules2;
}

Arbitre::~Arbitre()
{}

bool	Arbitre::rules(Player *player, int x, int y)
{
  printf("player : %p -> x : %d et y : %d\n", player, x, y);

  x_to = x / 50;
  y_to = y / 50;
  //std::cout << "Player put pion on x : " << x_to << " y : " << y_to << " -> player color is : " << player->getColor() << std::endl;

  if (rules_taked == 1)
    {
      this->take_two_pions(player);
      if (player->getTaked() >= 10)
	return (true);
    }

  //std::cout << "Player : " << (player->getColor() == 1 ? "white" : "black") << " have : " << player->getTaked() << std::endl;


  if (this->five_concecutif(player) == 2)
    return (true);
  return (false);
}

bool	Arbitre::check_breakable_all(std::string const& color, std::string const& color_inv, int nbr, int inc, int dif)
{
  int   nb = 0;
  std::vector<Case >::iterator it = cp_cases->begin() + (x_to + (y_to * 19));

  while ((*(it - nb)).getColor() == color)
    {
      if (y_to - 2 >= 0 && (*(it - nb - dif)).getColor() == color && (*(it - nb - (dif * 2))).getColor() == color_inv && (*(it - nb + dif)).getColor() == "empty")
        return true;                                                                                                                                                             
      if (y_to + 2 < 19 && (*(it - nb + dif)).getColor() == color && (*(it - nb + (dif * 2))).getColor() == color_inv && (*(it - nb - dif)).getColor() == "empty")
        return true;
      if ((y_to - 1 >= 0 && (*(it - nb - dif)).getColor() == color_inv) && (y_to + 1 < 19 && (*(it - nb + dif)).getColor() == color) && (*(it - nb + (dif * 2))).getColor() == "empty")
        return true;
      if ((y_to - 1 >= 0 && (*(it - nb - dif)).getColor() == color) && (y_to + 1 < 19 && (*(it - nb + dif)).getColor() == color_inv) && (*(it - nb - (dif * 2))).getColor() == "empty")
        return true;
      nb += inc;
    }
  nb = 0;
  while (nb < nbr && (*(it + nb)).getColor() == color)
    {
      if (y_to - 2 >= 0 && (*(it + nb - dif)).getColor() == color && (*(it + nb - (dif * 2))).getColor() == color_inv && (*(it + nb + dif)).getColor() == "empty")
        return true;
      if (y_to + 2 < 19 && (*(it + nb + dif)).getColor() == color && (*(it + nb + (dif * 2))).getColor() == color_inv && (*(it + nb - dif)).getColor() == "empty")
        return true;
      if ((y_to - 1 >= 0 && (*(it + nb - dif)).getColor() == color_inv) && (y_to + 1 < 19 && (*(it + nb + dif)).getColor() == color) && (*(it + nb + (dif * 2))).getColor() == "empty")
        return true;
      if ((y_to - 1 < 19 && (*(it + nb - dif)).getColor() == color) && (y_to + 1 < 19 && (*(it + nb + dif)).getColor() == color_inv) && (*(it + nb - (dif * 2))).getColor() == "empty")
        return true;
      nb += inc;
    }
  return false;
}

bool	Arbitre::five_breakable(std::string color, int direc, int nbr)
{
  std::string	color_inv;

  if (color == "white")
    color_inv = "black";
  else if (color == "black")
    color_inv = "white";
  else
    color_inv = "nothing";
  
  if (direc == 0) //horizontal
    {
      if (check_breakable_all(color, color_inv, nbr, 1, 19) == true || check_breakable_all(color, color_inv, nbr, 1, 20) == true || check_breakable_all(color, color_inv, nbr, 1, 18) == true)
	return true;
    }
  else if (direc == 1) //vertical
    {
      if (check_breakable_all(color, color_inv, nbr, 19, 1) == true || check_breakable_all(color, color_inv, nbr, 19, 20) == true || check_breakable_all(color, color_inv, nbr, 19, 18) == true)
	return true;
    }
  else if (direc == 2) //diagonale haut gauche -> bas droite
    {
      if (check_breakable_all(color, color_inv, nbr, 20, 1) == true || check_breakable_all(color, color_inv, nbr, 20, 19) == true || check_breakable_all(color, color_inv, nbr, 20, 18) == true)
	return true;
    }
  else if (direc == 3) //diagonale bas gauche -> haut droite
    {
      if (check_breakable_all(color, color_inv, nbr, 18, 1) == true || check_breakable_all(color, color_inv, nbr, 18, 19) == true || check_breakable_all(color, color_inv, nbr, 18, 20) == true)
	return true;
    }
  return false;
}

bool	Arbitre::getRulesFive()
{
  return rules_five_b;
}

bool	Arbitre::getRulesTaked()
{
  return rules_taked;
}

int	Arbitre::five_concecutif(Player *p)
{
  int	s_v = 1;
  int	s_h = 1;
  int	s_dhgd = 1;
  int	s_dbgd = 1;
  int	nb = 1;
  bool	breakable = false;

  std::vector<Case >::iterator it = cp_cases->begin() + (x_to + (y_to * 19));
  std::string	color_p = (*it).getColor();


  //checking_gauche
  while (x_to - nb >= 0 && (*(it - nb++)).getColor() == color_p)
    s_h++;
  nb = 1;
  
  //checking_droite
  while (x_to + nb < 19 && (*(it + nb++)).getColor() == color_p)
    s_h++;


  if (s_h >= 5 && (rules_five_b == 0 || five_breakable(color_p, 0, nb) == false))
    return 2;


  nb = 1;
  //checking_haut
  while (y_to - nb >= 0 && (*(it - (19 * nb++))).getColor() == color_p)
    s_v++;

  //checking_bas
  nb = 1;
  while (y_to + nb < 19 && (*(it + (19 * nb++))).getColor() == color_p)
    s_v++;


  if (s_v >= 5 && (rules_five_b == 0 || five_breakable(color_p, 1, nb) == false))
    return 2;


  nb = 1;
  //checking_haut_gauche
  while (y_to - nb >= 0 && x_to - nb >= 0 && (*(it - (20 * nb++))).getColor() == color_p)
    s_dhgd++;

  nb = 1;
  //checking_bas_droite
  while (y_to + nb < 19 && x_to + nb < 19 && (*(it + (20 * nb++))).getColor() == color_p)
    s_dhgd++;


  if (s_dhgd >= 5 && (rules_five_b == 0 || five_breakable(color_p, 2, nb) == false))
    return 2;
  

  nb = 1;
  //checking_bas_gauche
  while (y_to + nb < 19 && x_to - nb >= 0 && (*(it + (18 * nb++))).getColor() == color_p)
    s_dbgd++;

  nb = 1;
  //checking_haut_droite
  while (y_to - nb >= 0 && x_to + nb < 19 && (*(it - (18 * nb++))).getColor() == color_p)
    s_dbgd++;


  if (s_dbgd >= 5 && (rules_five_b == 0 || five_breakable(color_p, 3, nb) == false))
    return 2;

  return 0;
}

void	Arbitre::destroy_pions(Player * p, std::vector<Case >::iterator first, std::vector<Case >::iterator second)
{
  if (GameEngine::Instance().getRulesPions() == true)
    GameEngine::Instance().add_pion_possible((*(first)).getX() / 50, (*(first)).getY() / 50);
  (*(first)).setSprite(GameEngine::Instance().getCenterEmpty(), "empty");
  if (GameEngine::Instance().getRulesPions() == true)
    GameEngine::Instance().add_pion_possible((*(second)).getX() / 50, (*(second)).getY() / 50);
  (*(second)).setSprite(GameEngine::Instance().getCenterEmpty(), "empty");
  p->setTaked(p->getTaked() + 2);
}

void	Arbitre::take_two_pions(Player *p)
{
  std::string	color_inv;
  std::vector<Case >::iterator it = cp_cases->begin() + (x_to + (y_to * 19));

  if ((*it).getColor() == "black")
    color_inv = "white";
  else
    color_inv = "black";

  //gauche
  if (((x_to - 3) >= 0) && (*(it - 1)).getColor() == color_inv && (*(it - 2)).getColor() == color_inv &&
      (*(it - 3)).getColor() == (*it).getColor())
    destroy_pions(p, it - 1, it - 2);

  //droite
  if (((x_to + 3) < 19) && (*(it + 1)).getColor() == color_inv && (*(it + 2)).getColor() == color_inv &&
      (*(it + 3)).getColor() == (*it).getColor())
    destroy_pions(p, it + 1, it + 2);

  //haut
  if (((y_to - 3) >= 0) && (*(it - 19)).getColor() == color_inv && (*(it - 38)).getColor() == color_inv &&
      (*(it - 57)).getColor() == (*it).getColor())
    destroy_pions(p, it - 19, it - 38);

  //bas
  if (((y_to + 3) < 19) && (*(it + 19)).getColor() == color_inv && (*(it + 38)).getColor() == color_inv &&
      (*(it + 57)).getColor() == (*it).getColor())
    destroy_pions(p, it + 19, it + 38);

  //haut_gauche
  if (((y_to - 3) >= 0) && ((x_to - 3) >= 0) && (*(it - 20)).getColor() == color_inv &&
      (*(it - 40)).getColor() == color_inv && (*(it - 60)).getColor() == (*it).getColor())
    destroy_pions(p, it - 20, it - 40);

  //haut_droite
  if (((y_to - 3) >= 0) && ((x_to + 3) < 19) && (*(it - 18)).getColor() == color_inv &&
      (*(it - 36)).getColor() == color_inv && (*(it - 54)).getColor() == (*it).getColor())
    destroy_pions(p, it - 18, it - 36);

  //bas_gauche
  if (((y_to + 3) < 19) && ((x_to - 3) >= 0) && (*(it + 18)).getColor() == color_inv &&
      (*(it + 36)).getColor() == color_inv && (*(it + 54)).getColor() == (*it).getColor())
    destroy_pions(p, it + 18, it + 36);

  //bas_droite
  if (((y_to + 3) < 19) && ((x_to + 3) < 19) && (*(it + 20)).getColor() == color_inv &&
      (*(it + 40)).getColor() == color_inv && (*(it + 60)).getColor() == (*it).getColor())
    destroy_pions(p, it + 20, it + 40);
}
