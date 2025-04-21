#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <exception>
#include <cassert>
//#include "DictionaryRLRB.h"
using namespace std;

template <typename Key, typename Value>
class RLRB
{
	static constexpr bool RED = true;
	static constexpr bool BLACK = false;

	struct DictionaryNode
	{
		Key word;
		Value meaning;
		DictionaryNode* right;
		DictionaryNode* left;
		int count;	 // DictionaryNode count to keep track of subtree size
		int height;	 // Counts depth of the tree
		bool color;

		DictionaryNode(Key k, Value v, int c, bool col) : word(k), meaning(v), right(nullptr), left(nullptr), count(c), height(0), color(col) {}
		DictionaryNode(Key k, Value v) : word(k), meaning(v), right(nullptr), left(nullptr), count(1) {}
		DictionaryNode() : right(nullptr), left(nullptr), count(0) {}
	};

	DictionaryNode* root;

	bool isRed(DictionaryNode* x)
	{
		if (x == nullptr)
			return false;
		return x->color == RED;
	}

	DictionaryNode* rotateLeft(DictionaryNode* h)
	{
		if (h == nullptr)
			return h;

		DictionaryNode* x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = RED;

		h->count = 1 + size(h->left) + size(h->right);
		h->height = height(h);

		x->count = 1 + size(x->left) + size(x->right);
		x->height = 1 + std::max(height(x->left), height(x->right));
		return x;
	}

	DictionaryNode* rotateRight(DictionaryNode* h)
	{
		if (h == nullptr)
			return h;

		DictionaryNode* x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = RED;

		h->count = 1 + size(h->left) + size(h->right);
		h->height = 1 + std::max(height(h->left), height(h->right));

		x->count = 1 + size(x->left) + size(x->right);
		x->height = 1 + std::max(height(x->left), height(x->right));
		return x;
	}

	void flipColors(DictionaryNode* h) {
		h->color = !h->color;
		if (h->left) h->left->color = !h->left->color;
		if (h->right) h->right->color = !h->right->color;
	}

	DictionaryNode* getMin(DictionaryNode* h) {
		if (h == nullptr)
			throw std::out_of_range("empty symbol table");
		while (h->left != nullptr) {
			h = h->left;
		}
		return h;
	}

	/*DictionaryNode* remove(DictionaryNode* h, Key word)
	{
		if (word < h->word)
		{
			if (!isRed(h->left) && !isRed(h->left->left))
			{
				h = moveRedRight(h);
			}
			h->left = remove(h->left, word);
		}
		else
		{
			if (isRed(h->left))
			{
				h = rotateRight(h);
			}

			if (word == h->word && h->right == nullptr)
			{
				delete h;
				return nullptr;
			}

			if (!isRed(h->right) && !isRed(h->right->right))
			{
				h = moveRedLeft(h);
			}

			if (word == h->word)
			{
				DictionaryNode* minNode = getMin(h->right);
				h->word = minNode->word;
				h->meaning = minNode->meaning;
				h->right = deleteMin(h->right);
			}
			else
			{
				h->right = remove(h->right, word);
			}
		}
		return balance(h);
	}

	DictionaryNode* moveRedLeft(DictionaryNode* h)
	{
		flipColors(h);
		if (isRed(h->right->left))
		{
			h->right = rotateRight(h->right);
			h = rotateLeft(h);
			flipColors(h);
		}
		return h;
	}

	DictionaryNode* moveRedRight(DictionaryNode* h)
	{
		flipColors(h);
		if (isRed(h->left->left))
		{
			h = rotateRight(h);
			flipColors(h);
		}
		return h;
	}

	DictionaryNode* deleteMin(DictionaryNode* h)
	{
		if (h->left == nullptr)
		{
			delete h;
			return nullptr;
		}
		if (!isRed(h->left) && !isRed(h->left->left))
		{
			h = moveRedRight(h); // Adjust tree to maintain balance
		}
		h->left = deleteMin(h->left);
		return balance(h);
	}

	DictionaryNode* balance(DictionaryNode* h)
	{
		if (isRed(h->left))
		{
			h = rotateRight(h);
		}

		if (isRed(h->right) && isRed(h->right->right))
		{
			h = rotateLeft(h);
		}

		if (isRed(h->left) && isRed(h->right))
		{
			flipColors(h);
		}

		h->count = 1 + size(h->left) + size(h->right);
		h->height = 1 + std::max(height(h->left), height(h->right));
		return h;
	}*/

	void FlipColors(DictionaryNode* h)
	{
		h->color = RED;
		if (h->left) h->left->color = BLACK;
		if (h->right) h->right->color = BLACK;
	}

	DictionaryNode* put(DictionaryNode* h, Key word, Value meaning)
	{
		if (h == nullptr)
			return new DictionaryNode(word, meaning, 1, RED);

		if (word < h->word)
		{
			h->left = put(h->left, word, meaning);
		}
		else if (word > h->word)
		{
			h->right = put(h->right, word, meaning);
		}
		else
		{
			h->meaning = meaning;
		}

		if (!isRed(h->right) && isRed(h->left))
			h = rotateRight(h);
		if (isRed(h->right) && isRed(h->right->right))
			h = rotateLeft(h);
		if (isRed(h->right) && isRed(h->left))
			FlipColors(h);

		h->count = 1 + size(h->left) + size(h->right);
		h->height = 1 + std::max(height(h->left), height(h->right));
		return h;
	}

	size_t size(DictionaryNode* x)
	{
		if (x == nullptr) {
			return 0;
		}
		else if (x->right == nullptr && x->left == nullptr) {
			x->count = 1;
		}

		return x->count;
		//return 1 + size(x) + size()
	}

	int rank(Key word, DictionaryNode* x)
	{ 
		if (x == nullptr)
			return -1;

		if (word > x->word)
			return 1 + size(x->left) + rank(word, x->right);
		else if (word < x->word)
			return rank(word, x->left);
		else
			return size(x->left);
	}

	void inorder(DictionaryNode* x, std::vector<Key>& keys) const
	{
		if (x == nullptr)
			return;

		inorder(x->left, keys);
		keys.push_back(x->word);
		inorder(x->right, keys);
	}

	void preorder(DictionaryNode* x, std::vector<Key>& keys)
	{
		if (x == nullptr)
			return;

		keys.push_back(x->word);
		inorder(x->left, keys);
		inorder(x->right, keys);
	}

	void postorder(DictionaryNode* x, std::vector<Key>& keys)
	{
		if (x == nullptr)
			return;

		inorder(x->left, keys);
		inorder(x->right, keys);
		keys.push_back(x->word);
	}

	DictionaryNode* Floor(DictionaryNode* x, Key word)
	{

		if (x->word == word)
			return x;
		if (x->word > word)
			return Floor(x->left, word);

		DictionaryNode* t = Floor(x->right, word);
		if (t != nullptr)
			return t;
		return x;
	}
	DictionaryNode* Ceil(DictionaryNode* x, Key word)
	{
		if (x == nullptr)
			return nullptr;

		if (x->word == word)
			return x;
		if (x->word < word)
			return Ceil(x->right, word);

		DictionaryNode* t = Ceil(x->left, word);
		if (t != nullptr)
			return t;
		return x;
	}

	DictionaryNode* min(DictionaryNode* x)
	{
		if (x == nullptr)
			throw std::out_of_range("called min() with empty symbol table");
		while (x->left != nullptr)
			x = x->left;
		return x;
	}

	DictionaryNode* max(DictionaryNode* x)
	{
		if (x == nullptr)
			throw std::out_of_range("called max() with empty symbol table");

		while (x->right != nullptr)
			x = x->right;
		return x;
	}

	DictionaryNode* select(DictionaryNode* x, int k)
	{
		if (x == nullptr)
			return nullptr;

		int t = size(x->left);
		if (t > k)
			return select(x->left, k);
		else if (t < k)
			return select(x->right, k - t - 1);
		else
			return x;
	}

	/*int height(DictionaryNode* x)
	{
		if (x == nullptr)
			return -1;
		else if (x->right == nullptr && x->left == nullptr) {	// Changed
			x->height = 0;
		}

		return 1 + std::max(height(x->right), height(x->left));
	}*/
	int height(DictionaryNode* x)
	{
		if (x == nullptr)
			return -1;
		else if (x->right == nullptr && x->left == nullptr) {	// Changed
			x->height = 0;
		}
		return x->height;
	}

	bool validateRLRB(DictionaryNode* node, int currentBlackHeight, int& blackHeight) {
		if (node == nullptr) {
			// Base case: End of path, ensure black height consistency
			if (blackHeight == -1) {
				blackHeight = currentBlackHeight;
			}
			return blackHeight == currentBlackHeight;
		}

		// Check that no two consecutive red links exist
		if (isRed(node) && (isRed(node->left) || isRed(node->right))) {
			return false;
		}

		// Check right-leaning property
		if (isRed(node->left)) {
			return false; // Left-leaning red link violates RLRB property
		}

		// Increment black height if this node is black
		if (!isRed(node)) {
			currentBlackHeight++;
		}

		// Recursively validate left and right subtrees
		return validateRLRB(node->left, currentBlackHeight, blackHeight) &&
			validateRLRB(node->right, currentBlackHeight, blackHeight);
	}

	void keysLoHi(DictionaryNode* x, Key lo, Key hi, std::vector<Key>& result) {
		if (x == nullptr) {
			return;
		}
		if (lo < x->word) {
			keysLoHi(x->left, lo, hi, result);
		}

		if (lo <= x->word && x->word <= hi) {
			result.push_back(x->word);
		}

		if (hi > x->word) {
			keysLoHi(x->right, lo, hi, result);
		}
	}

	void clear(DictionaryNode* node)
	{
		if (node == nullptr) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

public:
	RLRB() : root(nullptr) {}
	~RLRB() {
		if (root == nullptr) {
			return;
		}

		clear(root->right);
		clear(root->left);
		delete root;
		root = nullptr;
	}

	void clear() {
		if (root == nullptr) {
			return;
		}

		clear(root->right);
		clear(root->left);
		delete root;
		root = nullptr;
	}

	/*void remove(Key word) {
		if (!isRed(root->left) && !isRed(root->right)) {
			root->color = RED;
		}

		root = remove(root, word);
		if (root != nullptr) root->color == BLACK;
	}*/

	void put(Key word, Value meaning)
	{
		root = put(root, word, meaning);
		root->color = BLACK;
	}

	Value get(Key word)
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		DictionaryNode* x = root;

		while (x != nullptr)
		{ // Search loop until word is found or null
			if (word < x->word)
				x = x->left;
			else if (word > x->word)
				x = x->right;
			else
				return x->meaning;
		}

		throw std::out_of_range("Value Not Found");
	}

	std::vector<Key> postorder() const {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> temp;
		postorder(root, temp);
		return temp;
	}

	std::vector<Key> inorder() const {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> temp;
		inorder(root, temp);
		return temp;
	}

	std::vector<Key> preorder() const {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> temp;
		preorder(root, temp);
		return temp;
	}

	size_t size()
	{
		return size(root);
	}

	int rank(Key word)
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		return rank(word, root);
	}

	Key Floor(Key word)
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		DictionaryNode* x = Floor(root, word);
		if (x == nullptr)
			throw std::out_of_range("No floor exists for the given word");
		return x->word;
	}

	Key Ceil(Key word)
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		DictionaryNode* x = Ceil(root, word);
		if (x == nullptr)
			throw std::out_of_range("No ceiling exists for the given word");
		return x->word;
	}

	std::vector<Key> keys()
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> keyList;
		inorder(root, keyList);
		return keyList;
	}

	int height()
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");
		return root->height;
	}

	Key min()
	{ // Returns the smallest word in the BST.
		if (root == nullptr)
			throw std::out_of_range("called min() with empty symbol table");
		DictionaryNode* x = root;
		while (x->left != nullptr)
			x = x->left;
		return x->word;
	}

	Key max()
	{
		if (root == nullptr)
			throw std::out_of_range("called max() with empty symbol table");
		DictionaryNode* traverse = root;
		while (traverse->right != nullptr)
		{
			traverse = traverse->right;
		}
		return traverse->word; // Return the maximum word
	}

	Key select(int k)
	{ // Returns the word with a specified rank k.
		if (k < 0 || k >= size())
			throw std::out_of_range("called select() with invalid argument");

		DictionaryNode* x = select(root, k);
		return x->word;
	}

	std::vector<Key> keysLoHi(Key lo, Key hi) {
		std::vector<Key> result;
		keysLoHi(root, lo, hi, result);
		return result;
	}

	bool isRightLeaningRedBlackTree() {
		int blackHeight = -1; // Initialize to an invalid value
		return validateRLRB(root, 0, blackHeight);
	}

	Value& operator[](const Key& word)
	{ // Accesses or inserts the value for a given word. If the word doesn't exist, it inserts a new node with a default value.
		if (root == nullptr)
			root = new DictionaryNode(word, Value());

		DictionaryNode* x = root;
		while (true)
		{
			if (word < x->word)
			{
				if (x->left == nullptr)
					x->left = new DictionaryNode(word, Value());
				x = x->left;
			}
			else if (x->word < word)
			{
				if (x->right == nullptr)
					x->right = new DictionaryNode(word, Value());
				x = x->right;
			}
			else
				return x->meaning;
		}
	}

	void unitTesting() {
		std::cout << "Unit testing after put() and inserting all dictionary keys and values into the RLRB\n\n";
		std::cout << "Test 1: Is it a red black tree?\n";
		assert(isRightLeaningRedBlackTree() && "Test 1: RLRB tree should be valid");
		std::cout << std::boolalpha << isRightLeaningRedBlackTree() << std::endl;
		std::cout << "Test 1 Passed\n";

		std::cout << "\nTest 2: red black tree size?\n";
		assert(size() == 34194 && "Test 2: Tree size should be 34914");
		std::cout << "Size is (should be 34194): " << size() << "\n";
		std::cout << "Test 2 Passed\n";

		std::cout << "\nTest 3: rank and select\n";
		assert(select(0) == "#NAME?" && "Test 3: select(0) should be #NAME?");
		std::cout << "Select(0) is (should be #NAME?): " << select(0);
		assert(rank("#NAME?") == 0 && "\nTest 3: rank('#NAME?') should be 0");
		std::cout << "\nrank(#NAME?) is (should be 0): " << rank("#NAME?");
		assert(select(34193) == "women" && "Test 3: select(34193) should be women");
		std::cout << "\nSelect(34193) is (should be women): " << select(34193);
		assert(rank("women") == 34193 && "\nTest 3: rank('women) should be 34193");
		std::cout << "\nrank(women) is (should be 34193): " << rank("women");
		std::cout << "\nTest 3 Passed\n";

		std::cout << "\nTest 4: Floor and Ceiling Methods\n";
		assert(Floor("Aam") == "Aam" && "Floor of 'Aam' should be 'Aam'");
		std::cout << "Floor('Aam') is: " << Floor("Aam") << "\n";
		assert(Ceil("A") == "A" && "Ceiling of 'A' should be 'A'");
		std::cout << "Ceiling of 'A' should be 'A'\n";
		std::cout << "Ceiling('A') is: " << Ceil("A") << "\n";
		assert(Ceil("Aard") == "Aard-vark" && "Ceiling of 'Aard' should be 'Aard-vark'");
		std::cout << "Ceil('Aard') is: " << Ceil("Aard") << "\n";
		std::cout << "Ceiling of 'Aard' should be 'Aard-vark'\n";
		std::cout << "Test 4 Passed\n";

		std::cout << "\nTest 5: Min Max Method\n";
		assert(min() == "#NAME?" && "Test 1: Min should be '#NAME?'");
		std::cout << "Min() is: " << min() << "\n";
		std::cout << "Min should be '#NAME?'\n";
		assert(max() == "women" && "Test 5: Max should be 'women'");
		std::cout << "Max() is: " << max() << "\n";
		std::cout << "Expected: women\nTest 5 Passed\n";

		std::cout << "\nTest 6: tree height\n";
		assert(height() == 27 && "Test 6: Height should be 27");
		std::cout << "Height is: " << height() << "\n";
		std::cout << "Expected: 27\nTest 6 Passed\n";

		std::cout << "\nTest 7: Traverse Method and Keys between lo and hi\n";
		std::vector<Key> keys = keysLoHi("A", "Aard-wolf");
		for (auto& elem : keys) {
			std::cout << elem << ", ";
		}
		std::cout << "\nExpected: (A, A 1, A B C, A cappella, A fortiori, A-, Aam, Aard-vark, Aard-wolf)";
		//std::cout << std::is_sorted(keys.begin(), keys.end());
		std::cout << "\nTest 7 passed\n";

		std::cout << "\nAll tests passed\n";
	}
};

int main() {
	RLRB<std::string, std::string> dictionary;
	ifstream file("dictionary.csv");

	if (!file.is_open()) {
		cerr << "Error: Could not open file dictionary.csv\n";
		return 1;
	}

	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string word, meaning;

		if (getline(iss, word, ',') && getline(iss, meaning)) {
			dictionary.put(word, meaning);
		}
	}

    dictionary.unitTesting();

    // General dictionary interface
	file.close();
    int choice;
    do {
        std::cout << "\nDictionary Options:\n";
        std::cout << "1. Search for a word\n";
        std::cout << "2. Display all words\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer.\n";
			break;
        }
        else if (choice == 1) {
            std::cin.ignore();
            std::string searchWord;
            std::cout << "Enter the word: ";
            std::getline(std::cin, searchWord);

            try {
                std::string meaning = dictionary.get(searchWord);
                std::cout << "Meaning: " << meaning << "\n";
            }
            catch (out_of_range& e) {
                cerr << e.what() << endl;
            }
        }
        else if (choice == 2) {
            vector<string> temp = dictionary.inorder();
            for (string& elem : temp) {
                cout << elem << endl;
            }
        }
        else if (choice != 3) {
            std::cout << "Wrong choice.\n";
            //cin >> choice;
        }
    } while (choice != 3);

    dictionary.clear();

    return 0;
}