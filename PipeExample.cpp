#include <sstream>
#include <iostream>
#include <zconf.h>
#include <thread>

int fd[2];

void Write()
{

   for(int i=0 ;i<10; ++i)
   {
      std::stringstream ss;
      ss << "Halo world " << i;
      write(fd[1], ss.str().c_str(), ss.str().length());
      std::cout << "Send > " << ss.str() << "[" << ss.str().length() << "]" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds{1});
   }

   std::stringstream ss;
   ss << "END";
   std::cout << "Send > " << ss.str() << "[" << ss.str().length() << "]" << std::endl;
   write(fd[1], ss.str().c_str(), ss.str().length());
}

int main()
{
   pipe(fd);

   std::thread t {Write};

   char buff[100];
   while(true)
   {
      ssize_t n = read(fd[0], buff, 100);
      std::string msg {buff, static_cast<unsigned>(n)};
      std::cout << "Receive > " << msg << "[" << msg.length() << "]" << std::endl;
      if (msg == "END")
      {
         break;
      }
   }

   t.join();

   close(fd[0]);
   close(fd[1]);
}
