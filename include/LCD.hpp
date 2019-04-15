#pragma once

#include <thread>
#include <SFML/Graphics.hpp>
#include "RAM.hpp"

class LCD
{
public:
  LCD(RAM *ram);
  ~LCD();

  bool  run();
  void  draw();

private:
  int   render();
  void  windowUpdate();
  void  copyUpdate();

private:
  void  mode3();

public:

  std::mutex  &getM()
  {
    return (this->blank);
  }

  sf::Texture &getTexture()
  {
    return (this->text);
  }

private:
  RAM *ram;

  sf::Texture       text;
  sf::RenderWindow  window;

  std::thread       *windowT;
  std::thread       *copyT;

  std::mutex  blank;

};
