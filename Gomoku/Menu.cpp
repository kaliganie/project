//
// Menu.cpp for  in /home/aroy/gomoku
// 
// Made by Antoine ROY
// Login   <aroy@epitech.net>
// 
// Started on  Thu Jul 10 00:39:17 2014 Antoine ROY
// Last update Sun Oct 26 17:41:03 2014 etienne bondot
//

#include <iostream>
#include <sstream>
#include "Menu.hh"
#include "Exception.hpp"

Menu::Menu()
  : _screen_dim(1000, 1075),
    _window(sf::VideoMode(_screen_dim.x, _screen_dim.y, 32), "Gomoku !"),
    _current_step(GAME_TYPE)
{
  _window.setKeyRepeatEnabled(false);
  _window.setFramerateLimit(60);
  if (!_font.loadFromFile("font/JKAbode-Demo.ttf") ||
      !_font_line.loadFromFile("font/underscr.ttf") ||
      !_t_background.loadFromFile("img/background_menu.png"))
    throw Exception::LoadFromFileException();
  _s_background.setTexture(_t_background);

  initRules();
  initTitle();
  initGameTypes();
  initFPSDisplay();
  initArrowsText();
  initOptionsTitle();
  initOptionsText();
  initTextMap();
}

Menu::~Menu()
{}

void		Menu::changeGameType(int type)
{
  if (_current_step)
    return;
  if (type < 0)
    type = NB_GAME_TYPE - 1;
  else if (type > NB_GAME_TYPE - 1)
    type = 0;
  _game_type = static_cast<eGameType>(type);
  _m_game_type[_game_type].setColor(sf::Color::Black);
}

void		Menu::changeOption()
{
  if (!_current_step)
    return;
  _m_rules[static_cast<eRule>(_current_step - 1)] = !_m_rules[static_cast<eRule>(_current_step - 1)];
}

void		Menu::changeCurrentStep(int step)
{
  if (step > NB_STEP)
    step--;
  else if (step < 0)
    step = 0;
  _current_step = static_cast<eStep>(step);
  resetColor();
  _current_step == GAME_TYPE ?
    _m_game_type[_game_type].setColor(sf::Color::Black) :
    _m_text[_current_step]->setColor(sf::Color::Black);
}

void		Menu::changeChoicePos()
{  
  if (_current_step == GAME_TYPE)
    return;
  if (_current_step == RULE_1)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_line_opt1.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 85.f, _screen_dim.y / 2.f + 90.f));
      else
	_line_opt1.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 90.f));
    }
  else if (_current_step == RULE_2)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_line_opt2.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 85.f, _screen_dim.y / 2.f + 130.f));
      else
	_line_opt2.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 130.f));
    }
  else if (_current_step == RULE_3)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_line_opt3.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 85.f, _screen_dim.y / 2.f + 170.f));
      else
	_line_opt3.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 170.f));
    }
  else if (_current_step == RULE_4)
    {
      if(_m_rules[static_cast<eRule>(_current_step - 1)])
	_line_opt4.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 85.f, _screen_dim.y / 2.f + 210.f));
      else
	_line_opt4.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 210.f));
    }
}

void		Menu::run()
{
  sf::Event	event;

  while (_window.isOpen())
    {
      _elapse = _clock.restart();
      while (_window.pollEvent(event))
	{
	  if (_elapse.asSeconds() > FPS)
	    {
	      if (event.type == sf::Event::Closed)
		_window.close();
	      if (event.type == sf::Event::KeyPressed)
		{
		  if (event.key.code == sf::Keyboard::Left)
		    {
		      changeGameType(static_cast<int>(_game_type) - 1);
		      changeOption();
		      changeChoicePos();
		    }
		  else if (event.key.code == sf::Keyboard::Right)
		    {
		      changeGameType(static_cast<int>(_game_type) + 1);
		      changeOption();
		      changeChoicePos();
		    }
		  else if (event.key.code == sf::Keyboard::Up)
		    {
		      changeCurrentStep(static_cast<int>(_current_step) - 1);
		    }
		  else if (event.key.code == sf::Keyboard::Down)
		    {
		      changeCurrentStep(static_cast<int>(_current_step) + 1);
		    }
		  else if (event.key.code == sf::Keyboard::Return)
		    {
		      displayInformations();
		    }
		  else if (event.key.code == sf::Keyboard::Escape)
		    {
		      _window.close();
		    }
		}
	    }
	  updateFPS();
	}
      draw();
      _window.display();
    }
}

void		Menu::draw()
{
  _window.clear();
  _window.draw(_s_background);
  _window.draw(_tx_title);
  _window.draw(_m_game_type[_game_type]);
  _window.draw(_tx_fps);
  _window.draw(_option_title);
  _window.draw(_option_five_breakable);
  _window.draw(_option_pawn_takable);
  _window.draw(_option_double_three);
  _window.draw(_option_pawn_possible);
  _window.draw(_arrow_left);
  _window.draw(_arrow_right);
  _window.draw(_line_opt1);
  _window.draw(_line_opt2);
  _window.draw(_line_opt3);
  _window.draw(_line_opt4);
  _window.draw(_press_enter);
}

void		Menu::updateFPS()
{
  std::stringstream	ss;

  if (_time_to_refresh.getElapsedTime().asSeconds() > 0.5)
    {
      ss << "fps " << (int)(1 / _elapse.asSeconds());
      _tx_fps.setString(ss.str());
      _time_to_refresh.restart();
    }
}

void		Menu::initRules()
{
  _m_rules[FIVE_BREAKABLE] = false;
  _m_rules[PAWN_TAKABLE] = false;
  _m_rules[DOUBLE_THREE] = false;
  _m_rules[PAWN_POSSIBLE] = false;
}

void		Menu::initTitle()
{
  sf::FloatRect	title_rect;

  _tx_title.setFont(_font);
  _tx_title.setString("GOMOKU");
  _tx_title.setCharacterSize(100);
  _tx_title.setColor(sf::Color::Black);
  title_rect = _tx_title.getLocalBounds();
  _tx_title.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _tx_title.setPosition(sf::Vector2f(_screen_dim.x / 2.0f, _screen_dim.y / 4.0f));

  _press_enter.setFont(_font);
  _press_enter.setString("PRESS ENTER TO PLAY");
  _press_enter.setCharacterSize(100);
  _press_enter.setColor(sf::Color::White);
  title_rect = _press_enter.getLocalBounds();
  _press_enter.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _press_enter.setPosition(sf::Vector2f(_screen_dim.x / 2.f, _screen_dim.y - 140.f));
}

void		Menu::initGameTypes()
{
  sf::FloatRect	title_rect;

  _game_type = NORMAL;

  _tx_game_type_normal.setFont(_font);
  _tx_game_type_normal.setString("PLAYER vs PLAYER");
  _tx_game_type_normal.setColor(sf::Color::Black);
  title_rect = _tx_game_type_normal.getLocalBounds();
  _tx_game_type_normal.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _tx_game_type_normal.setPosition(sf::Vector2f(_screen_dim.x / 2.0f, _screen_dim.y / 2.0f));
  _m_game_type[NORMAL] = _tx_game_type_normal;

  _tx_game_type_ia.setFont(_font);
  _tx_game_type_ia.setString("PLAYER vs IA");
  _tx_game_type_ia.setColor(sf::Color::Black);
  title_rect = _tx_game_type_ia.getLocalBounds();
  _tx_game_type_ia.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _tx_game_type_ia.setPosition(sf::Vector2f(_screen_dim.x / 2.0f, _screen_dim.y / 2.0f));
  _m_game_type[IA] = _tx_game_type_ia;

  _tx_game_type_online.setFont(_font);
  _tx_game_type_online.setString("ONLINE");
  _tx_game_type_online.setColor(sf::Color::Black);
  title_rect = _tx_game_type_online.getLocalBounds();
  _tx_game_type_online.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _tx_game_type_online.setPosition(sf::Vector2f(_screen_dim.x / 2.0f, _screen_dim.y / 2.0f));
  _m_game_type[ONLINE] = _tx_game_type_online;
}

void		Menu::initFPSDisplay()
{
  sf::FloatRect	title_rect;

  _tx_fps.setFont(_font);
  _tx_fps.setCharacterSize(20);
  _tx_fps.setString("fps ");
  _tx_fps.setColor(sf::Color::Black);
  title_rect = _tx_fps.getLocalBounds();
  _tx_fps.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _tx_fps.setPosition(sf::Vector2f(50.f, _screen_dim.y - 50.f));
}

void		Menu::initArrowsText()
{
  sf::FloatRect	title_rect;

  _arrow_left.setFont(_font);
  _arrow_left.setCharacterSize(20);
  _arrow_left.setString("(");
  _arrow_left.setColor(sf::Color::White);
  title_rect = _arrow_left.getLocalBounds();
  _arrow_left.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _arrow_left.setPosition(_screen_dim.x / 2.f - _screen_dim.x / 5, _screen_dim.y / 2.f);
 
  _arrow_right.setFont(_font);
  _arrow_right.setCharacterSize(20);
  _arrow_right.setString(")");
  _arrow_right.setColor(sf::Color::White);
  title_rect = _arrow_right.getLocalBounds();
  _arrow_right.setOrigin(title_rect.left + title_rect.width / 2.0f, title_rect.top + title_rect.height / 2.0f);
  _arrow_right.setPosition(_screen_dim.x / 2.f + _screen_dim.x / 5, _screen_dim.y / 2.f);
}

void		Menu::initOptionsTitle()
{
  _option_title.setFont(_font);
  _option_title.setString(".... Options ........................................................");
  _option_title.setColor(sf::Color::White);
  _option_title.setPosition(sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5, _screen_dim.y / 2.f + 40.f));
}

void		Menu::initOptionsText()
{
  _line_opt1.setFont(_font_line);
  _line_opt1.setString("___");
  _line_opt1.setColor(sf::Color::White);
  _line_opt1.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 90.f));

  _line_opt2.setFont(_font_line);
  _line_opt2.setString("___");
  _line_opt2.setColor(sf::Color::White);
  _line_opt2.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 130.f));

  _line_opt3.setFont(_font_line);
  _line_opt3.setString("___");
  _line_opt3.setColor(sf::Color::White);
  _line_opt3.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 170.f));

  _line_opt4.setFont(_font_line);
  _line_opt4.setString("___");
  _line_opt4.setColor(sf::Color::White);
  _line_opt4.setPosition(sf::Vector2f(_screen_dim.x / 2.f + 145.f, _screen_dim.y / 2.f + 210.f));

  _option_five_breakable.setFont(_font);
  _option_five_breakable.setString("5 pions prenables          yes\tno");
  _option_five_breakable.setColor(sf::Color::White);
  _option_five_breakable.setPosition(sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5, _screen_dim.y / 2.f + 80.f));

  _option_pawn_takable.setFont(_font);
  _option_pawn_takable.setString("pion prenable                  yes\tno");
  _option_pawn_takable.setColor(sf::Color::White);
  _option_pawn_takable.setPosition(sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5, _screen_dim.y / 2.f + 120.f));

  _option_double_three.setFont(_font);
  _option_double_three.setString("double trois                       yes\tno");
  _option_double_three.setColor(sf::Color::White);
  _option_double_three.setPosition(sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5, _screen_dim.y / 2.f + 160.f));

  _option_pawn_possible.setFont(_font);
  _option_pawn_possible.setString("pion possible                    yes\tno");
  _option_pawn_possible.setColor(sf::Color::White);
  _option_pawn_possible.setPosition(sf::Vector2f(_screen_dim.x / 2.f - _screen_dim.x / 5, _screen_dim.y / 2.f + 200.f));
}

void		Menu::initTextMap()
{
  _m_text[GAME_TYPE] = &_tx_game_type_normal;
  _m_text[RULE_1] = &_option_five_breakable;
  _m_text[RULE_2] = &_option_pawn_takable;
  _m_text[RULE_3] = &_option_double_three;
  _m_text[RULE_4] = &_option_pawn_possible;
  _m_text[RUN] = &_press_enter;
}

void		Menu::resetColor()
{
  _m_game_type[NORMAL].setColor(sf::Color::White);
  _m_game_type[IA].setColor(sf::Color::White);
  _m_game_type[ONLINE].setColor(sf::Color::White);
  for (std::map<eStep, sf::Text *>::iterator it = _m_text.begin();
       it != _m_text.end();
       it++)
    it->second->setColor(sf::Color::White);
}

void		Menu::displayInformations()
{
  std::cout << "GAME INFORMATIONS________________" << std::endl
	    << "mode: ";
  if (_game_type == NORMAL)
    std::cout << "player vs player" << std::endl;
  else if (_game_type == IA)
    std::cout << "player vs ia" << std::endl;
  else
    std::cout << "online" << std::endl;

  std::cout << "five pawn breakable: " << (_m_rules[FIVE_BREAKABLE] ? "TRUE" : "FALSE") << std::endl
	    << "pawn takable       : " << (_m_rules[PAWN_TAKABLE] ? "TRUE" : "FALSE") << std::endl
	    << "double three       : " << (_m_rules[DOUBLE_THREE] ? "TRUE" : "FALSE") << std::endl
	    << "pawn possible      : " << (_m_rules[PAWN_POSSIBLE] ? "TRUE" : "FALSE") << std::endl;

}
