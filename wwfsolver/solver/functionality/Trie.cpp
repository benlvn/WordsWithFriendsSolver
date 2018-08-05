#include "Trie.h"
#include <exception>
#include <fstream>
#include <iostream>

Trie::Trie(std::string dictionary_filepath){
	start_node = new Node;
	std::string line;
	std::ifstream myfile(dictionary_filepath);
	if(myfile.is_open()){
		while(getline(myfile, line)){
			add_to_tree(line);
		}
		myfile.close();
	} else {
		throw std::runtime_error("Could not open file from Trie constructor: " + dictionary_filepath);
	}
}

Trie::Trie(const Trie &copy_from){
	start_node = copy_node(copy_from.start_node);
}

int get_letter_index(char letter){
	if(65 <= letter && letter <= 90){
		return letter - 65;
	} else if (97 <= letter && letter <= 122){
		return letter - 97;
	} else {
		throw std::runtime_error(
		"Getting letter index from non-letter character");
	}
}

Trie::Node *Trie::get_first_letter(char letter){
	return start_node->letters[get_letter_index(letter)];
}

Trie::Node *Trie::get_next_letter(Node *current_node, char next_letter){
	int index = get_letter_index(next_letter);
	if(current_node == nullptr){
		throw std::runtime_error("current_node cannot be a nullptr");
	}
	return current_node->letters[index];
}

bool Trie::check_for_word(std::string word){
	return existance_map.find(word) != existance_map.end();
}

Trie::Node::~Node(){
	for(int i = 0; i < 26; ++i){
		Node *potential = letters[i]; 
		if(potential != nullptr){
			delete potential;
		}
	}
}

Trie::~Trie(){
	delete start_node;
}

Trie::Node *Trie::add_node(Node *current_node, char add_at_letter){
	if(current_node == nullptr){
		throw std::runtime_error("Cannot add node to nullptr");
	}
	int ind = get_letter_index(add_at_letter);
	if(current_node->letters[ind] != nullptr){
		throw std::runtime_error("Current node already has node at letter");
	}
	current_node->letters[ind] = new Node;
	return current_node->letters[ind];
}

void Trie::add_to_tree(std::string word){
	if(word.empty()){
		throw std::runtime_error("Cannott add empty word to tree");
	}
	Node *current_node = get_first_letter(word.front());
	if(current_node == nullptr){
		current_node = add_node(start_node, word.front());
	}
	for(int i = 1; i < word.size(); ++i){
		char letter = word[i];
		Node *next_node = get_next_letter(current_node, letter);
		if(next_node == nullptr){
			next_node = add_node(current_node, letter);
		}
		current_node = next_node;
	}
	current_node->endofword = true;	
	existance_map.insert(std::pair<std::string, bool>(word, true));
}

Trie::Node *Trie::copy_node(Node *copy_from){
	Node *ret = new Node;
	for(int i = 0; i < 26; ++i){
		if(copy_from->letters[i] != nullptr){
			ret->letters[i] = copy_node(copy_from->letters[i]);
		}
	}
	return ret;
}

