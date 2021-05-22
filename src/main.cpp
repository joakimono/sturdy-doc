#include <iostream>
#include <cstdlib>
#include <Fishy.hpp>

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
int main(int argc, char *argv[])
{
  std::cout << "Hello World.." << std::endl;
  auto fisk = ocean::fish();
  fisk.fish_me();
  return EXIT_SUCCESS;
}
#endif // DOXYGEN_SHOULD_SKIP_THIS
