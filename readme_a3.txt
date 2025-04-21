Assignment 3: Right Leaning Red Black Tree

/* *****************************************************************************
 *  Describe how your printRange(const Key& lo, const Key& hi) method 
 *  in RLRB.cpp prints all the keys of the tree in the range low to hi.

Initially used an inorder traversal to get all the elements in the tree into a
vector but this was inefficient. Lo is the lower bound key and hi is the upper bound key. I implemented it similar to binary search deluxe
and inorder traversal the main change being that if the current elements key is smaller then hi we go to the right 
sub tree and if it is larger than lo we got to the left subtree, and
push the elements between lo and hi into a vector. We do this recursively for
both right and left subtrees.
 **************************************************************************** */

/* *****************************************************************************
 *  The list of words in the dictionary is in sorted order and if you insert
 *  words in the same order in a vanilla version of BST, it will be created as 
 *  a degenerated tree. Does the RLRB tree solve this problem. If so, then how?
 *  Write your understanding.

Yes the red-black tree has solved this problem due by maintaining its structure due to its invariants such as 
a constant black height and rotations to maintain the red black property. This degeneration occurs in a plain BST because inserting keys in sorted order results in a tree that resembles a linked list. In red black trees such a list is not possible due to its invariants as it maintains close to logarithmic height.
The given input is not an optimal case for the tree almost being the worst case
 (some of the words though in ascending order in excel are not considered so in 
c++ built in comparison such as " " and -) which leads to a large number of 
operations such as color flips and rotations. 
 **************************************************************************** */

/* *****************************************************************************
 *  Known bugs / limitations.
All known bugs fixed. Height and size function were initially very inefficient 
however that has been fixed. I believe they can be and need to be optimized even
further. Q2 will end if incorrect input is added in choice such as a string
 **************************************************************************** */

/* *****************************************************************************
 *  Describe any serious problems you encountered.   
The remove function was difficult to implement but implemented nonetheless.
Very difficult to adjust it to cover all cases for a RLRB/2-3 tree.
(Sir Sedgewicks greatest battle XD).                 
 **************************************************************************** */

/* *****************************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                      
Remove function was fun though hard.                    
 **************************************************************************** */