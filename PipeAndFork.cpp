

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <array>
#include <iostream>
#include <string_view>

struct PipeTest
{
    std::array<int, 2> m_handles{};

    PipeTest()
    {
        if(pipe(m_handles.data()) < 0)
        {
            exit(1);
        }
    }

    ~PipeTest()
    {
        close(m_handles[0]);
        close(m_handles[1]);
    }

    std::string read()
    {
        std::array<char, 256> buffer{};
        int nByte = ::read(m_handles.at(0), buffer.data(), buffer.size());
        if(nByte > 0)
        {
            return {buffer.data(), nByte};
        }
        else
        {
            return {};
        }
    }

    void write(const std::string& val)
    {
        ::write(m_handles.at(1), val.c_str(), val.size());
    }
};

int main()
{
    PipeTest lPipeTest{};
    if (fork() > 0)
    {
        sleep(1);
        lPipeTest.write("Halo");
        wait(nullptr);
    }
    else
    {
        std::string msg = lPipeTest.read();
        std::cout << msg << std::endl;
    }
}
