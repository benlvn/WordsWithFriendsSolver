#include <iostream>

int main(int argc, char *argv[]) {
	std::cout << "Running C++ program" << std::endl;

	std::cout << "ARGV:" << std::endl;
	for(int i = 0; i < argc; ++i){
		std::cout << argv[i] << std::endl;
	}
	std::cout << "END ARGV" << std::endl;

	return 0;
}
