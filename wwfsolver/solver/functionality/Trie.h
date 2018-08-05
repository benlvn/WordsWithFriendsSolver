#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>

class Trie {
public:

	// Initializes the Trie block with words
	// from specified dictionary file
	Trie(std::string dictionary_filepath);
	Trie(const Trie &copy_from);
	struct Node {
		bool endofword{false};
		Node *letters[26] = {0};
		~Node();
	};


	// Gets the first node with this letter
	Node *get_first_letter(char letter);
	
	// Checks for the specified letter in the node
	// Returns nullptr if not found, the next node if found
	// Throws error if letter isn't A-z, current_node is nullptr
	Node *get_next_letter(Node *current_node,
							char next_letter);

	// Checks for the existance of a word in the trie block
	bool check_for_word(std::string word);

	~Trie();
private:

	// Adds word to the trie tree
	// and the existance map
	void add_to_tree(std::string word);

	// Creates a node at from node at letter
	Node *add_node(Node *current_node, char add_at_letter);

	Node *copy_node(Node *copy_from);
	
	// Nothing private yet
	Node *start_node;
	std::unordered_map<std::string, bool> existance_map;
};

#endif
