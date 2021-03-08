# AVL-Trees-Implementation
Implemented AVL Trees part of an assignment requiring an efficient data structure, capable of executing all usual operations like insertion, deletion, merging, splitting, lookup in O(log(n)).


Insertion: Can be realised in O(log(n)), since an AVL tree is always balanced, so the height
is h = log(n), where n is the number of nodes in the tree. For insertion we traverse at
most h nodes, so insertion is O(log(n)), since rotations are just pointers swapping.
To not waste resources, I keep the height of the tree as a structure field.

Deletion: Works similarly as Insertion. After the element to delete is found, I deleted
it and rebalanced the remaining tree if the balance factor was bigger different from
-1, 0 or 1. Logarithmic complexity.

Lookup: Since AVL is also a binary search tree, lookup is realised in O(h), where h is
the height of the tree.

Set: It works exactly as a lookup only with one additional O(1) operation.

Split: A tree node has an additional index field. This one is for providing indexing
for each new node, useful for optimising split and merge operations. When we want
to split at a specific index, we search(O(logn)) in the tree, then create 2 different
trees, one with the root consisting of the node at that index, the second is the initial
tree with the subtree removed.

Concat/Merge: To guarantee that the resulting tree is balanced, we can add an empty root,
and set the left and right pointers to the AVL trees received as parameters. The resulting
tree is now guaranteed to be AVL. Then, I removed the unnecessary root node(O(log(n) operation).
Then I recomputed the height for the resulting tree with an O(log(n)) traversal, so
the final complexity is logarithmic.
