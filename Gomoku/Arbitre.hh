//
// Arbitre.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Sat Jun 21 15:10:00 2014 Antoine ROY
// Last update Tue Aug 12 21:16:59 2014 Antoine ROY
//

#ifndef	__ARBITRE__
#define	__ARBITRE__

#include "Case.hh"
#include "Player.hh"

class	Case;

class	Arbitre
{
public:
  Arbitre(std::vector<Case >& cases, int rules1 = 1, int rules2 = 1);
  ~Arbitre();

private:
  std::vector<Case >	*cp_cases;
  int			rules_taked;
  int			rules_five_b;
  int			x_to;
  int			y_to;

  //  static Arbitre	*_instance;

public:
  //static Arbitre	*getInstance();

  bool	rules(Player *, int, int);
  void	take_two_pions(Player *);
  void	destroy_pions(Player *, std::vector<Case >::iterator, std::vector<Case >::iterator);
  bool	five_breakable(std::string, int, int);
  bool	check_breakable_all(std::string const&, std::string const&, int, int, int);
  bool	five_breakable_hori(std::string const&, std::string const&, int);
  bool	five_breakable_verti(std::string const&, std::string const&, int);
  bool	five_breakable_diag_hg_bd(const std::string&, const std::string&, int);
  bool	five_breakable_diag_bg_hd(const std::string&, const std::string&, int);
  int	five_concecutif(Player *);

  bool	getRulesFive();
  bool	getRulesTaked();
};

#endif
