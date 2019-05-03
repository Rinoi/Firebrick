#include <fstream>

#include "Interpretor.hpp"

int main(int argc, char **argv)
{
  if (argc < 2)
    return (1);

  std::ifstream file(argv[1]);
  Interpretor m;

  m.init();
  m.run(file);
}
