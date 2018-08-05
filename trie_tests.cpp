#include <iostream>
#include <vector>
#include <assert.h>
#include "Trie.h"

int main(){
	
	std::cout << "Sarting Trie tests" << std::endl;	
	std::cout << "Creating trie with word file" << std::endl;
	Trie test_trie("test_words.txt");

	std::cout << "Testing check_for_word()" << std::endl;
	std::vector<std::string> exists = {"culture", "board", "looks",
										"coaching", "coach", "cult", "a"};
	std::vector<std::string> dne = {"looked", "fire", "boar", "ting",
									"oppe", "", " ", "l", "c"};

	for(std::string word : exists){
		std::cout << "Checking word for existance: " << word << std::endl;
		assert(test_trie.check_for_word(word));
	}

	for(std::string word : dne){
		std::cout << "Checking word for non existance: " 
				<< word << std::endl;
		assert(!test_trie.check_for_word(word));
	}

	std::cout << "Testing get_first_letter/check_next_letter" << std::endl;
	std::cout << "Getting first letter: c" << std::endl;
	Trie::Node *node_ptr = test_trie.get_first_letter('c');
	assert(node_ptr != nullptr);
	assert(!node_ptr->endofword);
	std::string word = "ulturei";
	for(char letter : word){
		std::cout << "Getting next letter: " << letter << std::endl;
		node_ptr = test_trie.get_next_letter(node_ptr, letter);
		if(letter == 'i'){
			assert(node_ptr == nullptr);
		} else {
			assert(node_ptr != nullptr);
			if(letter == 't' || letter == 'e'){
				assert(node_ptr->endofword);
			} else {
				assert(!node_ptr->endofword);
			}
		}
	}

		
	std::cout << "End of Trie tests" << std::endl;	
}	
