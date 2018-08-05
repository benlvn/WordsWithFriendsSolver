#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <vector>
#include "Trie.h"

using namespace std;
//
// Finds all playable words in a Scrabble scenario
// and presents them in score order
class Solver {
public:
	// Initializes the Solver the list of words in a file
	Solver(std::string dictionary_filepath);
	
	struct Move {
		int points{0};	
		std::pair<int, int> start;
		std::string main_word;
		std::vector<std::pair<int, int>> other_starts;
		bool horizontal; // true if horizontal, false if vertical
	};
	void load_rack(std::vector<char> rack_in);

	void load_board(std::vector<std::vector<char>> board_in);

	void find_moves();

	// For testing purposes
	void print_board();
	void print_spaces();
	void print_letters();

	~Solver();
private:
	static const int DIM = 15;
	int spaces[DIM][DIM] = {0};
	std::vector<char> letters;
	std::vector<std::vector<char>> tiles;
	Trie trie_block;
	std::vector<Move> moves;

	std::vector<Move> solve_at_tile(int x, int y);
	void test_tile(int startx, int starty,
					int x, int y, Trie::Node *current_node, 
					std::string current_word,
					int sum_score, int word_mult);

	int letter_multiplier(int space_type);
	int word_multiplier(int space_type);
	int tile_points(char tile);
	void save_move(int points, int x, int y, std::string word);

	void load_spaces(string board_filepath);
};

#endif
