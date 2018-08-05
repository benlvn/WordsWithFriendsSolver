#include <iostream>
#include <fstream>
#include "Solver.h"

int main(){
	std::cout << "Creating Solver" << std::endl;	
	Solver test_solver("wordlist.txt");
	// test_solver.print_spaces();
	std::ifstream input_tiles("blank_board.txt");
	if(input_tiles.is_open()){
		test_solver.load_board(input_tiles);
		test_solver.print_board();
	}
	std::ifstream input_letters("letters1_fortest.txt");
	if(input_letters.is_open()){
		test_solver.load_letters(input_letters);
		test_solver.print_letters();
	}
	test_solver.find_moves();
}
