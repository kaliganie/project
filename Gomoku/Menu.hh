//
// Menu.hh for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jul 10 00:39:31 2014 Antoine ROY
// Last update Sun Oct 26 17:28:53 2014 etienne bondot
//

#ifndef	__MENU__
#define	__MENU__

#include "GameEngine.hh"
#define	FPS	1. / 60

class Menu
{
  
  typedef	enum
    {
      FIVE_BREAKABLE,
      PAWN_TAKABLE,
      DOUBLE_THREE,
      PAWN_POSSIBLE
    }		eRule;

  typedef	enum
    {
      NORMAL,
      IA,
      ONLINE,
      NB_GAME_TYPE = 3
    }		eGameType;

  typedef	enum
    {
      GAME_TYPE,
      RULE_1,
      RULE_2,
      RULE_3,
      RULE_4,
      RUN,
      NB_STEP = 5
    }		eStep;


public:
  
  Menu();
  ~Menu();
  
private:

  sf::Clock			_clock;
  sf::Clock			_time_to_refresh;
  sf::Time			_elapse;

  sf::Vector2i			_screen_dim;
  sf::RenderWindow		_window;
  sf::Texture			_t_background;
  sf::Sprite			_s_background;
  sf::Font			_font;
  sf::Font			_font_line;

  sf::Text			_tx_title;
  sf::Text			_tx_game_type_normal;
  sf::Text			_tx_game_type_ia;
  sf::Text			_tx_game_type_online;
  sf::Text			_tx_fps;
  sf::Text			_arrow_left;
  sf::Text			_arrow_right;
  sf::Text			_option_title;
  sf::Text			_option_five_breakable;
  sf::Text			_option_pawn_takable;
  sf::Text			_option_double_three;
  sf::Text			_option_pawn_possible;
  sf::Text			_line_opt1;
  sf::Text			_line_opt2;
  sf::Text			_line_opt3;
  sf::Text			_line_opt4;
  sf::Text			_press_enter;

  std::map<eRule, bool>		_m_rules;
  std::map<eGameType, sf::Text>	_m_game_type;
  std::map<eStep, sf::Vector2f>	_m_coord_arrow_left;
  std::map<eStep, sf::Vector2f>	_m_coord_arrow_right;
  std::map<eStep, sf::Text *>	_m_text;
  eGameType			_game_type;
  eStep				_current_step;

public:

  void	changeGameType(int);
  void	changeOption();
  void	changeCurrentStep(int);
  void	changeChoicePos();

  void	run();
  void	draw();
  void	updateArrows();
  void	updateFPS();
  void	initRules();
  void	initTitle();
  void	initGameTypes();
  void	initFPSDisplay();
  void	initArrowsText();
  void	initCoordArrows();
  void	initOptionsTitle();
  void	initOptionsText();
  void	initTextMap();
  void	resetColor();

  void	displayInformations();

};

#endif
