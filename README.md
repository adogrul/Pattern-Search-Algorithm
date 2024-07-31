# Pattern Search Algortihms:
### What are Pattern Search Algorithms
Pattern search algorithms are used to find occurrences of a pattern within a larger text or dataset. These algorithms are essential in various fields, such as text processing, data mining, and bioinformatics. Here are some common pattern search algorithms:
* [Aho-Corasick Algorithm](https://github.com/adogrul/Pattern-Search-Algorithm/tree/main/Aho-Corasick)
* [Boyer Moore Algorithm](https://github.com/adogrul/Pattern-Search-Algorithm/tree/main/BoyerMoore)
* [KMP Algorithm](https://github.com/adogrul/Pattern-Search-Algorithm/tree/main/KMP%20Algorithm)
* [Rabin Karp Algorithm](https://github.com/adogrul/Pattern-Search-Algorithm/tree/main/Rabin%20Karp)

### 1. Aho Corasick
*This algorithm is used for searching multiple patterns simultaneously. It builds a finite state machine (FSM) from the patterns and processes the text in a single pass. It's efficient for scenarios where multiple patterns need to be searched concurrently*


### 2. Boyer Moore
*This algorithm uses two heuristics to skip portions of the text, improving efficiency. The bad character heuristic and the good suffix heuristic help reduce the number of character comparisons, making it very fast for practical use cases.*

### 3. KMP
*This algorithm preprocesses the pattern to create a partial match table (or prefix table) that allows the search process to avoid redundant comparisons. It achieves a linear time complexity of O(n + m), where n is the length of the text and m is the length of the pattern.*

### 4. Rabin Karp
*This algorithm uses hashing to quickly compare the hash values of the pattern and substrings of the text. It is particularly useful for multiple pattern searches. Its average time complexity is O(n + m), but the worst-case complexity can be higher due to hash collisions.*

