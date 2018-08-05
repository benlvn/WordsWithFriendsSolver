#include <vector>
#include <iostream>
#include "Solver.h"

using namespace std;

int main(int argc, char *argv[]){
	// assert(argc == (15*15 + 7));
	std::vector<std::vector<char>> board;
	std::vector<char> rack;
	for(int i = 0; i < 15; ++i){
		board.push_back({});
		board[i].resize(15);
		for(int j = 0; j < 15; ++j){
			char next_space = *argv[i*15 + j + 1];
			if(next_space != '.'){
				board[i][j] = next_space;
			} else {
				board[i][j] = ' ';
			}
		}
	}
	for(int i = 0; i < 7; ++i){
		rack.push_back(*argv[15*15 + i + 1]);
	}

	std::cout << "Making solver" << std::endl;
	Solver solve("./solver/functionality/wordlist.txt");
	cout << "Loading rack" << endl;
	solve.load_rack(rack);
	cout << "Loading board" << endl;
	solve.load_board(board);
	cout << "Loaded everything" << endl;

	// Then we'll test to make sure it works
	std::cout << "Board:" << std::endl;
	solve.print_board();
	std::cout << "Rack:" << std::endl;
	solve.print_letters();
	std::cout << "Spaces:" << std::endl;
	solve.print_spaces();
}
