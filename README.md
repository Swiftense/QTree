<h1>Swiftense - QTree</h1>
<p>Swift search algorithm used by swiftense.</p>
<h2>What is this?</h2>
<p>A Tree data structure in which elements are orderd, that both searching and inserting elements can happen at equal speeds.</p>
<h2>How does it work?</h2>
<p>Usually, in binary search trees elements are inserted, so, that nodes with larger keys are on the right leaf and nodes with smaller keys are on the left leaf. This Algorithm works completely different by looking at bits of inserted keys. It iterates through every bit of an key using the right shift operator, goes left if the value of the bit is 0 and right if the value is 1. Then the Node is inserted as soon as the branch ends. The PSEUDO-Code could look something like this:</p>

```python
def insert(tree, key, value):
    current = tree.root # start at root of tree
    for bit of key: # loop through bits of key
        if bit is 1: # go right if the bit is 1
            if current.right is null: # check if branch ends
                insert = QNode(key, value)
                current.right = insert # extend branch with new node
                return
            current = current.right # if branch doesn't end, continue on right leaf
        else: # go left if the bit is 0
            if current.left is null: # check if branch ends
                insert = QNode(key, value)
                current.left = insert # extend branch with new node
                return
            current = current.left # if branch doesn't end, continue on left leaf
```

<p>Getting values almost works the same way: </p>

```python
def get(tree, key):
    current = tree.root # start at root of tree
    for bit of key: # loop through bits of key
        if current.key is key: # check if key of current node is equal to key
            return key
        if bit is 1: # go right if the bit is 1
            if current.right is null: # check if branch ends
                return null
            current = current.right # if branch doesn't end, continue on right leaf
        else: # go left if the bit is 0
            if current.left is null: # check if branch ends
                return null
            current = current.left # if branch doesn't end, continue on left leaf
```

<h2>What are the advantages?</h2>
<ul>
    <li>Same insert and search speed. Most Types of binary search trees like AVL Tree or Red Black Tree need rotations and restructurings when inserting elements. This creates an imbalance of search and insert speeds. With the QTree Algorithm, this is completely balanced.</li>
    <li>Worst Case Time Complexity is independent to amount of Elements in Tree. Since this Algorithm uses the bits of an key to calculate its position in the Tree, the worst case time complexity is identical for any Tree. But the Average Time Complexity O(log n)</li>
</ul>
<h2>What are the disadvantages?</h2>
<ul>
    <li>Slow deletions. The Searchalgorithm is dependent of the subnodes of a node, so when fully deleting a node out of the tree, the subtree of the deleted node has to be fully rebuild. But the simple workaround to this problem is to just mark the node as deleted and reuse it when its possible.</li>
</ul>
<h2>Example</h2>
<p>To get an preview of the Tree structure and see how this algorithm works, execute the Bash Script with the preview argument: </p>

```bash
./qtree.sh preview
```

<p>To see some performance tests between the Red Black Tree Algorithm (implementation of std::map) and this Algorithm, execute the Bash Script with the preview argument: </p>

```bash
./qtree.sh performance
```

<h2>Strings</h2>
<p>Allthough the Example above only uses a QTree with integral keys and values, the algorithm can be easily changed to suppport strings both as key and as value, an simple implementation of this can be found in the <strong>SQTree.c</strong> source file.</p>
