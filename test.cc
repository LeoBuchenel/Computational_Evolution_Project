#include <iostream>
#include <fstream>
#include <vector>
//using namespace std;

void write(std::ostream& os);

int main()
{
	std::ofstream os1;
	std::ofstream os2;
	os1.open("write1.out");
	os2.open("write2.out");
	
	std::vector<std::ofstream*> oss{&os1, &os2};

	
	//*(oss[0]) << "1" << endl;
	
	//*(oss[1]) << "1" << endl;
	
	write(*oss[0]);
	
	(oss[0])->close();
	(oss[1])->close();
	
	return 0;
	
}

void write(std::ostream& os)
{
	os << "1" << std::endl;
}
