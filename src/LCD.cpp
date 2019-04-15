#include <unistd.h>

#include "LCD.hpp"

LCD::LCD(RAM *ram)
{
  this->window.create(sf::VideoMode(240, 160), "My window");
  this->window.setFramerateLimit(60);
  this->text.create(240, 160);

  this->ram = ram;

  this->windowT = NULL;
  this->copyT = NULL;
}

LCD::~LCD()
{

}

bool  LCD::run()
{
  if (this->windowT == NULL)
    this->windowT = new std::thread(&LCD::windowUpdate, this);
  if (this->copyT == NULL)
    this->copyT = new std::thread(&LCD::copyUpdate, this);
  return (true);
}

void LCD::copyUpdate()
{
  int x;
  int y;
  u32 colorTab[240];
  sf::Clock t;
  int cycle;

  while (this->window.isOpen())
  {
    for (y = 0; y < 160; y += 1)
    {
      t.restart();
      for (x = 0; x < 240; x += 1)
      {
        u32 addr = 0x6000000 + ((y * 240 + x) * sizeof(u16));
        u16 c = ram->getValue<u16>(addr);

        int color;
        u8 *cc = (u8*)(&color);
        cc[0] = (float)(c & 0x001F) / 31 * 255;
        cc[1] = (float)(c & 0x03E0) / 31 * 255;
        cc[2] = (float)(c & 0x7C00) / 31 * 255;
        cc[3] = 255;

        colorTab[x] = color;
      }
      this->text.update((u8*)&colorTab[0], 240, 1, 0, y);
      cycle = toCycle(t.getElapsedTime());
      sf::sleep(toTime(cycle - 272));
      //HBLANK 272 cycle
    }
    sf::sleep(toTime(83776));
    //VBLANK 83776 cycle
  }
}

void LCD::windowUpdate()
{
  sf::Sprite sp;

  sp.setTexture(this->text);
  while (this->window.isOpen())
  {
      sf::Event event;

      while (this->window.pollEvent(event));
      //this->blank.lock();
      this->window.draw(sp);
      this->window.display();
      //this->blank.unlock();
  }
}
