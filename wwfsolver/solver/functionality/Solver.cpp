#include "Solver.h"
#include "Trie.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

Solver::Solver(std::string dictionary_filepath) :
	trie_block(dictionary_filepath) {
	char next_space;
	std::ifstream spaces_file(dictionary_filepath);
	if(spaces_file.is_open()){
		for(int i = 0; i < 15; ++i){
			for(int j = 0; j < 15; ++j){
				spaces_file >> next_space;
				if(48 > next_space || next_space > 53){
					throw std::runtime_error("Invalid spaces in file");
				}
				spaces[i][j] = next_space - 48;
			}
		}
	} else {
		throw std::runtime_error("Could not find file wwf_spaces.txt");
	}
	load_spaces("./solver/functionality/spaces.txt");
	return;
}

void Solver::load_rack(std::vector<char> rack_in){
	letters.clear();
	for(int i = 0; i < 7; ++i){
		letters.push_back(rack_in[i]);
	}
	std::sort(letters.begin(), letters.end());
	return;
}

void Solver::load_board(std::vector<std::vector<char>> board_in){
	tiles.clear();
	for(int i = 0; i < 15; ++i){
		tiles.push_back({});
		tiles[i].resize(15);
		for(int j = 0; j < 15; ++j){
			tiles[i][j] = board_in[i][j];
		}
	}
	return;
}

void Solver::load_spaces(string board_filepath){
	std::ifstream myfile(board_filepath);
	int next_type = 0;
	if(myfile.is_open()){
		for(int i = 0; i < 15; ++i){
			for(int j = 0; j < 15; ++j){
				myfile >> next_type;
				spaces[i][j] = next_type;
			}
		}
	}
}

void Solver::print_board(){
	for(auto row : tiles){

		for(char tile : row){
			std::cout << tile << " ";
		}
		std::cout << std::endl;
	};
	return;
}

void Solver::print_spaces(){
	std::cout << "Printing spaces" << std::endl;
	std::string space_types[6] = {"--", "DL", "TL", "DW", "TW", "ST"};
	for(int i = 0; i < 15; ++i){
		for(int j = 0; j < 15; ++j){
			std::cout << space_types[spaces[i][j]] << " ";
		}
		std::cout << std::endl;
	}
	return;
}

void Solver::print_letters(){
	std::cout << "Printing letters" << std::endl;
	for(int i = 0; i < 7; ++i){
		std::cout << letters[i] << " ";
	}
	std::cout << std::endl;
	return;
}

void Solver::find_moves(){
	for(int i = 0; i < 7; ++i){
		test_tile(7 - i, 7, 7 - i, 7, nullptr, "", 0, 1);
	}
	
	std::cout << "All moves:" << std::endl;
	for(auto move : moves){
		std::cout << std::endl;
		std::cout << move.main_word << std::endl;
		std::cout << '\t' << move.points << std::endl;
		std::cout << '\t' << move.start.first
				<< " " << move.start.second << std::endl;
	}
	return;
}

std::vector<Solver::Move> Solver::solve_at_tile(int x, int y){
	if(x < 0 || DIM < x || y < 0 || DIM < y){
		throw std::runtime_error("Can't wolve at tile outside of board");
	}
	if(tiles[x][y] == '.'){
		throw std::runtime_error("Can't solve at empty tile");
	}
	return {};
}	

int Solver::letter_multiplier(int space_type){
	if(space_type < 0 || 5 < space_type){
		throw std::runtime_error(
				"Trying to get letter multiplier from invalid space type");
	}
	if(space_type == 1){
		return 2;
	} else if (space_type == 2){
		return 3;
	} else {
		return 1;
	}
}

int Solver::word_multiplier(int space_type){
	if(space_type < 0 || 5 < space_type){
		throw std::runtime_error(
				"Trying to get letter multiplier from invalid space type");
	}
	if(space_type == 3){
		return 2;
	} else if (space_type == 4){
		return 3;
	} else {
		return 1;
	}
}

void Solver::test_tile(int startx, int starty, 
					int x, int y, Trie::Node *current_node,
					std::string current_word,
					int sum_score, int word_mult){
	if(startx < 0 || DIM < startx
		|| starty < 0 || DIM < starty){
		throw std::runtime_error(
				"testing tile from out of range start");
	}
	if(x < 0 || DIM < x
		|| y < 0 || DIM < y){
		throw std::runtime_error(
				"testing tile at out of range space");
	}
	if(sum_score < 0){
		throw std::runtime_error(
				"test_tile called with negative sum_score");
	}
	if(word_mult < 1){
		throw std::runtime_error(
				"test_tile called with invalid word multiplier");
	}
	for(int i = 0; i < letters.size(); ++i){
		if(i > 0 && letters[i] == letters[i-1]){
			continue;
		}
		char try_letter = letters[i];
		letters.erase(letters.begin() + i);
		Trie::Node *next_node;
		if(current_node == nullptr){
			next_node = trie_block.get_first_letter(try_letter);
		} else {
			next_node = trie_block.get_next_letter(current_node, try_letter);
		}
		if(next_node != nullptr){
			std::string new_word = current_word + try_letter;
			int new_sum_score = sum_score + letter_multiplier(spaces[x][y])
								+ tile_points(try_letter);
			int new_word_mult = word_mult * word_multiplier(spaces[x][y]);
			if(next_node->endofword){
				save_move(new_sum_score*new_word_mult, startx, starty,
								new_word);
			}
			if(x < DIM){
				test_tile(startx, starty, x+1, y, next_node, new_word,
								new_sum_score, new_word_mult);
			}
		}
		letters.insert(letters.begin()+i, try_letter);
	}

}

int Solver::tile_points(char letter){
	int pointvals[26] = {1, 4, 4, 2, 1, 4, 3, 3, 1, 10, 5, 2, 4,
						2, 1, 4, 10, 1, 1, 1, 2, 5, 4, 8, 3, 10};
	if(letter < 97 || 122 < letter){
		throw std::runtime_error(
					"Checking point value of invalid character");
	}
	return pointvals[letter - 97];
}

void Solver::save_move(int points, int x, int y, std::string word){
	Move to_save;
	to_save.points = points;
	to_save.start = std::pair<int, int>(x,y);
	to_save.main_word = word;
	for(int i = 0; i < moves.size(); ++i){
		if(moves[i].points < points){
			moves.insert(moves.begin() + i, to_save);
			return;
		}
	}
	moves.push_back(to_save);	
}

Solver::~Solver() {
	return;
}
