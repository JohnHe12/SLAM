#include <iostream>

int main(int argc, char *argv[])
{
   std::cout << "Hello Main2!" << std::endl;
   int* x = nullptr;
   int y = 1;
   x = &y;
   int &ref = y;
   std::cout << *x << std::endl;
   std::cout << "ref: " << y << std::endl;
   return 0;
}
