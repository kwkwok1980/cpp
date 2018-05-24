#include <vector>
#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <fstream>
#include <sstream>
#include <memory>
#include <fcntl.h>
#include <sys/mman.h>
#include <zconf.h>
#include <iomanip>
#include <unordered_map>
#include <iterator>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <time.h>

int main()
{
   std::time_t localTime = std::time(0);
   std::cout << localTime << std::endl;

   std::tm localTm;
   if (localtime_r(&localTime, &localTm) == nullptr)
   {
      std::cout << "Fail" << std::endl;
      return 0;
   }

   std::cout << localTm.tm_year + 1900 << "-"
             << localTm.tm_mon + 1 << "-"
             << localTm.tm_mday << " "
             << localTm.tm_hour << ":"
             << localTm.tm_min << ":"
             << localTm.tm_sec << std::endl;
}
