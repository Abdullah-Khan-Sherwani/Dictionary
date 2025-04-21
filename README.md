# Right-Leaning Red-Black Tree (RLRB Tree)

This repository contains an implementation of the Right-Leaning Red-Black Tree (RLRB Tree), a self-balancing binary search tree that maintains efficient performance through structural invariants like balanced black heights and tree rotations.

## Features

- Efficient insertion, deletion, and search operations
- Maintains tree balance even with sorted input
- Optimized implementations of `height` and `size`
- Range-based key search with `printRange(lo, hi)`
- Handles worst-case input gracefully through rotations and color flips

---

## Method Highlights

### `printRange(const Key& lo, const Key& hi)`

Prints all keys in the range `[lo, hi]`. Instead of traversing the entire tree, the implementation leverages properties of binary search trees for an efficient traversal:
- Recursively visits the left subtree if the current node's key is greater than `lo`
- Recursively visits the right subtree if the current key is less than `hi`
- Collects only the nodes that lie within the given range

This approach significantly improves efficiency over the naïve full inorder traversal method.

---

## Tree Structure and Performance

Inserting keys in sorted order into a regular binary search tree typically leads to degeneration into a linked list. However, the RLRB Tree avoids this by:
- Preserving a balanced tree through red-black properties
- Ensuring the black height is consistent
- Performing necessary rotations and color flips to maintain structure

This allows the tree to maintain logarithmic height and ensures efficient operations regardless of the input order.

---

## Known Limitations / Bugs

- All known bugs have been fixed.
- The `height` and `size` functions were initially inefficient but have since been optimized. Further improvements may still be possible.
- Invalid input for menu-driven prompts (e.g., entering a string instead of an expected numeric choice) may terminate the program.

---

## Challenges Faced

- Implementing the `remove` function was particularly challenging due to the complexity of covering all structural cases in a 2-3/RLRB Tree.
- Managing color flips, rotations, and tree balance during deletion was a major technical hurdle.
- Some input edge cases (e.g., special characters or non-standard C++ comparisons) increased the number of balancing operations required.

---

## Final Thoughts

This project provided a deep dive into the inner workings of self-balancing binary search trees. While the `remove` function was difficult to implement, it was also one of the most rewarding aspects of the work. The learning experience was valuable, particularly in understanding how theoretical invariants translate into practical implementations.
