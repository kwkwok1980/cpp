#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include <assert.h>
#include <sstream>
#include <iomanip>

class Config
{
public:
   template<std::size_t N>
   decltype(auto) get()
   {
      if constexpr (N == 0)
      {
         return (this->i);
      }
      else if constexpr (N == 1)
      {
         return (this->d);
      }
   }

private:
   int i = 42;
   double d = 7.0;
};

namespace std
{
   template<>
   struct tuple_size<Config>
   {
      static unsigned const value = 2;
   };

   template<std::size_t N>
   struct tuple_element<N, Config>
   {
      using type = decltype(std::declval<Config>().get<N>());
   };
}

Config gm{};
Config& f()
{
   return gm;
}


int main()
{
   auto&& [i,d] = f();
   std::cout << gm.get<0>() << std::endl;
   std::cout << gm.get<1>() << std::endl;
   i = 43;
   d = 8.0;
   std::cout << gm.get<0>() << std::endl;
   std::cout << gm.get<1>() << std::endl;

   std::cout << std::boolalpha << std::is_reference_v<decltype(i)> << std::endl;

}
