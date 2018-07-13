#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>

void PrintTime(const std::chrono::high_resolution_clock::time_point& rTimePoint)
{
   auto time = std::chrono::high_resolution_clock::to_time_t(rTimePoint);
   std::cout << std::ctime(&time) << std::endl;
}

void PrintTime(const std::chrono::steady_clock::time_point& rTimePoint)
{
   std::cout << rTimePoint.time_since_epoch().count() << std::endl;
}

int main()
{
   {
      auto now = std::chrono::steady_clock::now();
      PrintTime(now);

      auto epoch = std::chrono::steady_clock::time_point{};
      PrintTime(epoch);

      auto minTimePoint = std::chrono::steady_clock::time_point{std::chrono::steady_clock::duration::min()};
      PrintTime(minTimePoint);

      auto maxTimePoint = std::chrono::steady_clock::time_point{std::chrono::steady_clock::duration::max()};
      PrintTime(maxTimePoint);
   }

   {
      auto now = std::chrono::high_resolution_clock::now();
      PrintTime(now);

      auto epoch = std::chrono::high_resolution_clock::time_point{};
      PrintTime(epoch);

      auto minDuration = std::chrono::high_resolution_clock::duration::min();
      auto minTimePoint = std::chrono::high_resolution_clock::time_point{minDuration};
      PrintTime(minTimePoint);

      auto maxDuration = std::chrono::high_resolution_clock::duration::max();
      auto maxTimePoint = std::chrono::high_resolution_clock::time_point{maxDuration};
      PrintTime(maxTimePoint);

      auto myDuration = std::chrono::high_resolution_clock::duration{1000000000};
      auto myTimePoint = std::chrono::high_resolution_clock::time_point{myDuration};
      PrintTime(myTimePoint);
   }
}
