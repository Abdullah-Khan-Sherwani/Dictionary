#include <iostream>
#include <vector>
#include <stdexcept>

/// <summary>
/// 
///GOATED code
///
/// 
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <typeparam name="Value"></typeparam>

template <typename Key, typename Value>
class RLRB
{
	static constexpr bool RED = true;
	static constexpr bool BLACK = false;

	struct Node
	{
		Key key;
		Value val;
		Node* right; 
		Node* left;	 
		int count;	 // Node count to keep track of subtree size
		int height;	 // Counts depth of the tree
		bool color;

		Node(Key k, Value v, int c, bool col) : key(k), val(v), right(nullptr), left(nullptr), count(c), height(0), color(col) {}
		Node(Key k, Value v) : key(k), val(v), right(nullptr), left(nullptr), count(1) {}
		Node() : right(nullptr), left(nullptr), count(0) {}
	};

	Node* root;

	bool isRed(Node* x)
	{
		if (x == nullptr)
			return false;
		return x->color == RED;
	}

	Node* rotateLeft(Node* h)
	{
		if (h == nullptr)
			return h;

		Node* x = h->right;
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

	Node* rotateRight(Node* h)
	{
		if (h == nullptr)
			return h;

		Node* x = h->left;
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

	void flipColors(Node* h) {
		h->color = !h->color;
		if (h->left) h->left->color = !h->left->color;
		if (h->right) h->right->color = !h->right->color;
	}

	Node* getMin(Node* h) {
		if (h == nullptr)
			throw std::out_of_range("called min() with empty symbol table");

		while (h->left != nullptr) {
			h = h->left;
		}
		return h;
	}

	Node* getMax(Node* h) {
		if (h == nullptr)
			throw std::out_of_range("called max() with empty symbol table");

		while (h->right != nullptr) {
			h = h->right; // Keep moving to the rightmost node
		}
		return h;
	}

	Node* remove(Node* h, Key key)
	{
		if (key > h->key)
		{
			if (!isRed(h->right) && !isRed(h->right->right))  // change
			{
				h = moveRedRight(h);
			}
			h->right = remove(h->right, key);
		}
		else
		{
			if (isRed(h->right))
			{
				h = rotateLeft(h);
			}

			if (key == h->key && h->right == nullptr)
			{
				delete h;
				return nullptr;
			}

			if (!isRed(h->left) && !isRed(h->left->right))
			{
				h = moveRedLeft(h);
			}

			if (key == h->key)
			{
				Node* maxNode = getMax(h->left);
				h->key = maxNode->key;
				h->val = maxNode->val;
				h->left = deleteMax(h->left);
			}
			else
			{
				h->left = remove(h->left, key);
			}
		}
		return balance(h);
	}


	Node* moveRedLeft(Node* h)
	{
		flipColors(h);
		if (isRed(h->left->left))
		{
			h->right = rotateRight(h->right);
			h = rotateLeft(h);
			flipColors(h);
		}
		return h;
	}

	Node* moveRedRight(Node* h) // Peak changes here
	{
		flipColors(h);
		if (isRed(h->left->right))
		{
			h->left = rotateLeft(h->left);
			h = rotateRight(h);
			//flipColors(h);
		}
		return h;
	}

	Node* deleteMax(Node* h)
	{
		if (h->right == nullptr)
		{
			delete h;
			return nullptr;
		}

		if (!isRed(h->right) && !isRed(h->right->right))
		{
			h = moveRedLeft(h); 
		}

		h->right = deleteMax(h->right);

		return balance(h);
	}


	Node* deleteMin(Node* h)
	{
		if (h->left == nullptr)
		{
			delete h;
			return nullptr;
		}
		if (!isRed(h->left) && !isRed(h->left->left))
		{
			h = moveRedRight(h); 
		}
		//h->height = 1 + std::max(height(h->left), height(h->right));
		return balance(h);
	}

	Node* balance(Node* h)
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
	}

	Node* put(Node* h, Key key, Value val)
	{
		if (h == nullptr)
			return new Node(key, val, 1, RED); 

		if (key < h->key)
		{
			h->left = put(h->left, key, val);
		}
		else if (key > h->key)
		{
			h->right = put(h->right, key, val);
		}
		else
		{
			h->val = val; // Overwrite h value 
		}

		if (!isRed(h->right) && isRed(h->left)) // Changes
			h = rotateRight(h);
		if (isRed(h->right) && isRed(h->right->right))
			h = rotateLeft(h);
		if (isRed(h->right) && isRed(h->left))
			flipColors(h);

		h->count = 1 + size(h->left) + size(h->right);
		h->height = 1 + std::max(height(h->left), height(h->right));
		return h;
	}

	size_t size(Node* x)
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

	int rank(Key key, Node* x)
	{ 
		if (x == nullptr)
			return -1;

		if (key > x->key)
			return 1 + size(x->left) + rank(key, x->right);
		else if (key < x->key)
			return rank(key, x->left);
		else
			return size(x->left);
	}

	void inorder(Node* x, std::vector<Key>& keys) const
	{
		if (x == nullptr)
			return;

		inorder(x->left, keys);
		keys.push_back(x->key);
		inorder(x->right, keys);
	}

	void preorder(Node* x, std::vector<Key>& keys) const
	{
		if (x == nullptr)
			return;

		keys.push_back(x->key);
		inorder(x->left, keys);
		inorder(x->right, keys);
	}

	void postorder(Node* x, std::vector<Key>& keys) const
	{
		if (x == nullptr)
			return;

		inorder(x->left, keys);
		inorder(x->right, keys);
		keys.push_back(x->key);
	}

	Node* Floor(Node* x, Key key)
	{
		if (x == nullptr)
			return nullptr;

		if (x->key == key)
			return x;
		if (x->key > key)
			return Floor(x->left, key);

		Node* t = Floor(x->right, key);
		if (t != nullptr)
			return t;
		return x;
	}
	Node* Ceil(Node* x, Key key)
	{
		if (x == nullptr)
			return nullptr;

		if (x->key == key)
			return x;
		if (x->key < key)
			return Ceil(x->right, key);

		Node* t = Ceil(x->left, key);
		if (t != nullptr)
			return t;
		return x;
	}

	Node* select(Node* x, int k)
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

	int height(Node* x)
	{
		if (x == nullptr)
			return -1;
		else if (x->right == nullptr && x->left == nullptr) {	// Changed
			x->height = 0;
		}
		return x->height;
	}

	void keysLoHi(Node* x, Key lo, Key hi, std::vector<Key>& result) { // printRange
		if (x == nullptr) {
			return;
		}

		if (lo < x->key) {
			keysLoHi(x->left, lo, hi, result);
		}
		if (lo <= x->key && x->key <= hi) {
			result.push_back(x->key);
		}
		if (hi > x->key) {
			keysLoHi(x->right, lo, hi, result);
		}
	}

	bool validateRLRB(Node* node, int currentBlackHeight, int& blackHeight) {
		if (node == nullptr) {
			if (blackHeight == -1) {
				blackHeight = currentBlackHeight;
			}
			return blackHeight == currentBlackHeight;
		}

		if (isRed(node) && (isRed(node->left) || isRed(node->right))) {
			return false;
		}

		if (isRed(node->left)) {
			return false; 
		}

		if (!isRed(node)) {
			currentBlackHeight++;
		}

		return validateRLRB(node->left, currentBlackHeight, blackHeight) && validateRLRB(node->right, currentBlackHeight, blackHeight);
	}
	void clear(Node* node)
	{
		if (node == nullptr) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

	Value Findmin(Node* h)
	{
		if (h == nullptr)
			throw std::out_of_range("called min() with empty symbol table");
		Node* x = h;
		while (x->left != nullptr)
			x = x->left;
		return x->val;
	}

	Value Findmax(Node* h)
	{
		if (root == nullptr)
			throw std::out_of_range("called max() with empty symbol table");
		Node* traverse = h;
		while (traverse->right != nullptr)
		{
			traverse = traverse->right;
		}
		return traverse->val;
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

	void remove(Key key) {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		if (!isRed(root->left) && !isRed(root->right)) {
			root->color = RED;
		}

		root = remove(root, key);
		if (root != nullptr) root->color == BLACK;
	}

	void put(Key key, Value val)
	{
		root = put(root, key, val);
		root->color = BLACK;
	}

	Value get(Key key)
	{
		Node* x = root;

		while (x != nullptr)
		{ 
			if (key < x->key)
				x = x->left; 
			else if (key > x->key)
				x = x->right; 
			else
				return x->val; 
		}

		throw std::out_of_range("Value Not Found"); 
	}

	void postorder() const {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> temp;
		postorder(root, temp);
		for (auto& key : temp) {
			std::cout << key << " ";
		}
		std::cout << std::endl;
	}

	void inorder() const {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> temp;
		inorder(root, temp);

		for (auto& key : temp) {
			std::cout << key << " ";
		}
		std::cout << std::endl;
	}

	void preorder() const {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> temp;
		preorder(root, temp);
		for (auto& key : temp) {
			std::cout << key << " ";
		}
		std::cout << std::endl;
	}

	size_t size()
	{
		return size(root);
	}

	int rank(Key key)
	{
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		return rank(key, root);
	}

	Key Floor(Key key)
	{
		Node* x = Floor(root, key);
		if (x == nullptr)
			throw std::out_of_range("No floor exists for the given key");
		return x->key;
	}

	Key Ceil(Key key)
	{
		Node* x = Ceil(root, key);
		if (x == nullptr)
			throw std::out_of_range("No ceiling exists for the given key");
		return x->key;
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
	{ 
		if (root == nullptr)
			throw std::out_of_range("called min() with empty symbol table");
		Node* x = root;
		while (x->left != nullptr)
			x = x->left;
		return x->key;
	}

	Value Findmin()
	{
		if (root == nullptr)
			throw std::out_of_range("called min() with empty symbol table");
		Node* x = root;
		while (x->left != nullptr)
			x = x->left;
		return x->val;
	}

	Key max()
	{
		if (root == nullptr)
			throw std::out_of_range("called max() with empty symbol table");
		Node* traverse = root;
		while (traverse->right != nullptr)
		{
			traverse = traverse->right;
		}
		return traverse->key; 
	}

	Value Findmax()
	{
		if (root == nullptr)
			throw std::out_of_range("called max() with empty symbol table");
		Node* traverse = root;
		while (traverse->right != nullptr)
		{
			traverse = traverse->right;
		}
		return traverse->val;
	}

	Key select(int k)
	{ 
		if (k < 0 || k >= size())
			throw std::out_of_range("called select() with invalid argument");

		Node* x = select(root, k);
		return x->key;
	}

	void keysLoHi(Key lo, Key hi) {
		if (root == nullptr)
			throw std::out_of_range("empty symbol table");

		std::vector<Key> result;
		keysLoHi(root, lo, hi, result);
		for (int key : result) {
			std::cout << key << " ";
		}
		std::cout << std::endl;
	}

	bool isRightLeaningRedBlackTree() {
		//if (root == nullptr)
			//throw std::out_of_range("empty symbol table");

		int blackHeight = -1; 
		return validateRLRB(root, 0, blackHeight);
	}

	Value& operator[](const Key& key)
	{ 
		if (root == nullptr)
			root = new Node(key, Value());

		Node* x = root;
		while (true)
		{
			if (key < x->key)
			{
				if (x->left == nullptr)
					x->left = new Node(key, Value());
				x = x->left;
			}
			else if (x->key < key)
			{
				if (x->right == nullptr)
					x->right = new Node(key, Value());
				x = x->right;
			}
			else
				return x->val;
		}
	}

	bool isEmpty() {
		return root == nullptr;
	}

	static void test() {
		RLRB<int, std::string> tree;

		std::cout << "Testing put and isEmpty\n";
		std::cout << "Tree is empty: " << std::boolalpha << tree.isEmpty() << "(Expected: True)\n";
		tree.put(10, "ten");
		tree.put(20, "twenty");
		tree.put(5, "five");
		tree.put(4, "four");
		tree.put(15, "fifteen");
		tree.put(25, "twenty-five");
		tree.put(12, "twelve");
		tree.put(30, "thirty");
		std::cout << "(After putting 10, 20, 5, 4, 15, 25, 12, 30) Tree is empty: " << std::boolalpha << tree.isEmpty() << "(Expected: False)\n";

		try {
			std::cout << "Value for key 10: " << tree.get(10) << " (Expected: ten)\n";
			std::cout << "Value for key 20: " << tree.get(20) << " (Expected: twenty)\n";
			std::cout << "Value for key 5: " << tree.get(5) << " (Expected: five)\n";
			std::cout << "Value for key 15: " << tree.get(15) << " (Expected: fifteen)\n";
			std::cout << "Value for key 25: " << tree.get(25) << " (Expected: twenty-five)\n";
			std::cout << "Value for key 3: " << tree.get(3) << " (Expected: Error)\n";
		}
		catch (const std::out_of_range& e) {
			std::cerr << "Error: " << e.what() << "";
		}
		std::cout << "\tExpected: Value not found\n";

		std::cout << "\nTree size: " << tree.size() << " (Expected: 8)\n";

		std::cout << "\nTesting min, Findmin, max, Findmax\n";
		std::cout << "Minimum key: " << tree.min() << " (Expected: 4)\n";
		std::cout << "Minimum value: " << tree.Findmin() << " (Expected: four)\n";

		std::cout << "Maximum key: " << tree.max() << " (Expected: 30)\n";
		std::cout << "Maximum value: " << tree.Findmax() << " (Expected: thirty)\n";

		try {
			std::cout << "\nFloor of 11: " << tree.Floor(11) << " (Expected: 10)\n";
			std::cout << "Ceiling of 11: " << tree.Ceil(11) << " (Expected: 12)\n";
		}
		catch (const std::out_of_range& e) {
			std::cerr << "Error: " << e.what() << "\n";
		}

		std::cout << "\nRank of key 15: " << tree.rank(15) << " (Expected: 4)\n";
		std::cout << "Select key with rank 4: " << tree.select(4) << " (Expected: 15)\n";

		std::cout << "\nTesting Keys and inorder functions: \n";
		std::vector<int> keys = tree.keys();
		std::cout << "Keys in order: ";
		for (int key : keys) {
			std::cout << key << " ";
		}
		std::cout << "(Expected: 4 5 10 12 15 20 25 30 )\n";

		std::cout << "Tree height: " << tree.height() << " (Expected: 3)\n";

		std::cout << "Testing Preorder and Postorder: \n";
		std::cout << "Keys in Preorder: ";
		tree.preorder();
		std::cout << "(Expected: 10 4 5 12 15 20 25 30 )\n";

		std::cout << "Keys in Postorder: ";
		tree.postorder();		
		std::cout << "(Expected: 4 5 12 15 20 25 30 10 )\n";

		std::cout << "Testing Print Range: \n";
		tree.keysLoHi(5, 15);
		std::cout << "(Expected: 5 10 12 15)\n";

		std::cout << "\nIs it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(30);
		std::cout << "Removed node with key 30." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(25);
		std::cout << "Removed node with key 25." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(4);
		std::cout << "Removed node with key 4." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(5);
		std::cout << "Removed node with key 5." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(15);
		std::cout << "Removed node with key 15." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(12);
		std::cout << "Removed node with key 12." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(20);
		std::cout << "Removed node with key 20." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;
		tree.remove(10);
		std::cout << "Removed node with key 10." << std::endl;
		std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << tree.isRightLeaningRedBlackTree() << std::endl;


		std::cout << "\nClearing tree of any remaining elements\n";
		tree.clear();
		std::cout << "Tree is empty: " << std::boolalpha << tree.isEmpty() << "(Expected: True)\n";
	}
};

int main() {
	/*RLRB<int, int> test;
	for (int i = 0 ; i < 25; i++) {
		test.put(i, i);
	}
	test.remove(10);
	test.remove(15);
	test.remove(23);
	test.remove(1);
	std::cout << "Is it a right leaning red black tree?: " << std::boolalpha << test.isRightLeaningRedBlackTree() << std::endl;*/

	RLRB<int, std::string>::test();

	return 0;
}