# include "GameEngine.hh"

GameEngine::GameEngine(int _hard) : hard(_hard), score(0), your_turn(false), nb_clic(0)
{
  app.create(VideoMode(800, 800, 32), "Memory game by Roy_a", Style::Close);

  t_red.loadFromFile("pictures/red.png");
  t_red_p.loadFromFile("pictures/red_pressed.png");

  t_blue.loadFromFile("pictures/blue.png");
  t_blue_p.loadFromFile("pictures/blue_pressed.png");

  t_green.loadFromFile("pictures/green.png");
  t_green_p.loadFromFile("pictures/green_pressed.png");

  t_yellow.loadFromFile("pictures/yellow.png");
  t_yellow_p.loadFromFile("pictures/yellow_pressed.png");


  s_red.setTexture(t_red);
  s_red.setPosition(200,200);

  s_blue.setTexture(t_blue);
  s_blue.setPosition(400,200);

  s_green.setTexture(t_green);
  s_green.setPosition(200,400);

  s_yellow.setTexture(t_yellow);
  s_yellow.setPosition(400,400);

  b0.loadFromFile("sound/banzai.wav");
  b1.loadFromFile("sound/bouchon.wav");
  b2.loadFromFile("sound/foghi.wav");
  b3.loadFromFile("sound/ting.wav");

  s0.setBuffer(b0);
  s1.setBuffer(b1);
  s2.setBuffer(b2);
  s3.setBuffer(b3);

  this->run();
}

GameEngine::~GameEngine()
{}

void	GameEngine::print_screen()
{
  app.clear();

  app.draw(s_red);
  app.draw(s_blue);
  app.draw(s_green);
  app.draw(s_yellow);

  app.display();
}

void	GameEngine::reset_screen()
{
  s_red.setTexture(t_red);
  s_blue.setTexture(t_blue);
  s_green.setTexture(t_green);
  s_yellow.setTexture(t_yellow);
}

void	GameEngine::change_red()
{
  if (s_red.getTexture() != &t_red)
    s_red.setTexture(t_red);
  else
    {
      s_red.setTexture(t_red_p);
      s0.play();
    }
}

void	GameEngine::change_blue()
{
  if (s_blue.getTexture() != &t_blue)
    s_blue.setTexture(t_blue);
  else
    {
      s_blue.setTexture(t_blue_p);
      s1.play();
    }
}

void	GameEngine::change_green()
{
  if (s_green.getTexture() != &t_green)
    s_green.setTexture(t_green);
  else
    {
      s_green.setTexture(t_green_p);
      s2.play();
    }
}

void	GameEngine::change_yellow()
{
  if (s_yellow.getTexture() != &t_yellow)
    s_yellow.setTexture(t_yellow);
  else
    {
      s_yellow.setTexture(t_yellow_p);
      s3.play();
    }
}

void	GameEngine::verif_change_color(int nb)
{
  if (nb == 0)
    change_red();
  else if (nb == 1)
    change_blue();
  else if (nb == 2)
    change_green();
  else if (nb == 3)
    change_yellow();
}

void	GameEngine::auto_show()
{
  std::vector<int>::iterator	it = memory.begin();

  while (it != memory.end())
    {
      verif_change_color((*it));
      print_screen();
      usleep(700000);
      verif_change_color((*it));
      print_screen();
      usleep(700000);
      it++;
    }
}

void	GameEngine::add_new_touch()
{
  int	i = 0;

  while (i < hard)
    {
      memory.push_back(rand() % 4);
      i++;
    }
  your_turn = true;
  auto_show();
}

bool	GameEngine::check_clic(int nb_color)
{
  int	i = 0;
  std::vector<int>::iterator	it = memory.begin();

  while (i++ < nb_clic - 1)
    it++;

  if ((*it) == nb_color)
    return true;
  return false;
}

void	GameEngine::run()
{
  Event		event;
  Vector2i	pos;
  int		nb_color = 5;
  std::vector<int>::iterator	itt = memory.begin();

  while (app.isOpen())
    {
      if (your_turn == false)
	add_new_touch();
      while (app.pollEvent(event))
        {
	  if (event.type == Event::Closed)
	    app.close();
	  if (Mouse::isButtonPressed(Mouse::Left) && event.type != Event::MouseMoved && your_turn == true && nb_clic != memory.size())
	    {
	      pos = Mouse::getPosition(app);
	      std::cout << "ici 1 \n";
	      if (pos.x > 200 && pos.x < 400 && pos.y > 200 && pos.y < 400)
		nb_color = 0;
	      else if (pos.x > 400 && pos.x < 600 && pos.y > 200 && pos.y < 400)
		nb_color = 1;
	      else if (pos.x > 200 && pos.x < 400 && pos.y > 400 && pos.y < 600)
		nb_color = 2;
	      else if (pos.x > 400 && pos.x < 600 && pos.y > 400 && pos.y < 600)
		nb_color = 3;
	      
	      verif_change_color(nb_color);
	      
	      while (Mouse::isButtonPressed(Mouse::Left) == true)
		print_screen();
	      
	      nb_clic++;
	      if (check_clic(nb_color) == false)
		return ;
	      reset_screen();
	    }
	  if (nb_clic == memory.size())
	    {
	      nb_clic = 0;
	      your_turn = false;
	    }
	}
      print_screen();
    }
  std::cout << "toto\n";
  std::vector<int>::iterator	it = memory.begin();

  while (it != memory.end())
    {
      std::cout << (*it) << std::endl;
      it++;
    }
}
