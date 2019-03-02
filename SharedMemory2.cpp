/*
Reference
http://www.cs.toronto.edu/~iq/csc209s/smalllectures/csc209_w10_4.pdf
*/


#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <string>
#include <cstring>

struct Account
{
	char name [10];
	int age;
};

int main()
{
	size_t SIZE = 4096;
	std::string MEM_NAME = "/demo.mem";
	std::string SEM_NAME = "/demo.sem";
	
	int mem_fd = shm_open(MEM_NAME.c_str(), O_CREAT|O_RDWR, 0666);
	if (mem_fd == -1)
	{
		return 0;
	}
	
	ftruncate(mem_fd, 4096);
	
	void* ptr = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, 0);
	char* base = reinterpret_cast<char*>(ptr);
	size_t offset = 0;

	sem_t* sem = sem_open(SEM_NAME.c_str(), O_CREAT|O_RDWR, 0666);
	sem_wait(sem);
	
	Account* a1 = new(reinterpret_cast<void*>(base + offset)) Account;
	memcpy(a1->name, "ABC", 3);
	a1->age = 10;
	offset += sizeof(Account);
	
	Account * a2 = new(reinterpret_cast<void*>(base + offset)) Account;
	memcpy(a2->name, "EFG", 3);
	a2->age = 20;
	offset += sizeof(Account);
	
	sem_post(sem);
	sem_close(sem);
	sem_unlink(SEM_NAME.c_str());
	
	munmap(ptr, SIZE);
	
	close(mem_fd);
	shm_unlink(MEM_NAME.c_str());
}
