# Aho-Corasick Algorithm

## 1. Building the Trie (Pattern Tree)

### Insert Patterns
- Build a trie (or prefix tree) from the set of patterns.
- Each node in the trie represents a character in the patterns.
- Edges between nodes represent transitions from one character to the next.

### Create Failure Links
- Create failure links to handle mismatches efficiently.
- Failure links are pointers to the longest suffix of the current prefix that is also a prefix of some pattern.

### Failure Function
- Determines where to continue searching in the trie when a mismatch occurs.
- If you’re at node `n` and encounter a mismatch, the failure function tells you which node to transition to next.

## 2. Constructing the Finite State Machine

### Add Failure Links
- For each node in the trie that doesn’t lead to a pattern match, add a failure link to a different node representing the longest suffix which is also a prefix.

### Root Failure Links
- Failure links from the root node point back to the root itself.

### Intermediate Nodes
- For non-root nodes, failure links point to the longest suffix in the trie that’s also a prefix of some pattern.

### Output Links
- Each node in the trie might also be an end of a pattern.
- Maintain output links to track which patterns end at that node.
- This allows identifying all patterns that end at that position when a match is found.

## 3. Searching the Text

### Process Text Character by Character
- Start at the root of the trie and process each character of the text.

### Follow Trie Edges
- Follow the trie edges according to the current character.
- Record the match if you reach a node with a pattern match.

### Handle Mismatches
- If a mismatch occurs, follow the failure link until you reach a node where the character matches, or until you reach the root.
- Continue processing from there.

### Report Matches
- Report any patterns that end at the current node as you traverse the trie.

## Example

Suppose you have patterns `["he", "she", "his", "hers"]` and you want to search these in the text `“ushers”`.

### Build Trie
- Construct a trie where each path from root to leaf represents one of the patterns.

### Add Failure Links
- Add failure links to ensure quick backtracking when a mismatch occurs.

### Search Text
- Process each character of the text while following the trie edges and utilizing failure links to handle mismatches.
- For `“ushers”`, the algorithm will efficiently locate all occurrences of the patterns.

## Complexity

- **Time Complexity**: `O(n + m + z)`, where `n` is the length of the text, `m` is the total length of all patterns combined, and `z` is the number of matches found.
- **Space Complexity**: `O(m)` for the trie and failure links, and can be higher if the number or length of patterns is large.
# Here's the Psuedo Codes
## `buildMatchingMachine`
```cpp
Function buildMatchingMachine(arr, k)
    // Initialize out[] and g[][] arrays, and set g[][] to -1
    out[] = 0
    g[][] = -1

    // Populate character index mapping table
    For each ASCII character i
        charToIndex[character] = ASCII value of character

    state = 1 // Initial state

    // Build the states for each word
    For each word i in arr
        currentState = 0
        For each character c in word
            ch = charToIndex[c]
            If g[currentState][ch] == -1
                g[currentState][ch] = state++
            currentState = g[currentState][ch]
        out[currentState] |= (1 << i) // Mark the state as matching the word

    // Set transitions for the root state
    For each character ch in MAXC
        If g[0][ch] == -1
            g[0][ch] = 0

    // Calculate failure functions
    f[] = -1
    Create a queue q
    For each character ch in MAXC
        If g[0][ch] != 0
            f[g[0][ch]] = 0
            q.push(g[0][ch])

    // Expand failure functions
    While the queue q is not empty
        state = q.pop()
        For each character ch in MAXC
            If g[state][ch] != -1
                failure = f[state]
                While g[failure][ch] == -1
                    failure = f[failure]
                failure = g[failure][ch]
                f[g[state][ch]] = failure
                out[g[state][ch]] |= out[failure]
                q.push(g[state][ch])

    return states // Total number of states

```

## `findNextState`
```cpp
Function findNextState(currentState, nextInput)
    ch = charToIndex[nextInput]
    If currentState or ch is invalid
        Show error message and return default state (0)
    While g[currentState][ch] == -1
        currentState = f[currentState]
    return g[currentState][ch]

```
## `searchWords`
```cpp
Function searchWords(arr, k, filePath)
    size = get_file_size(filePath)
    text = ReadAllBytes(filePath)
    buildMatchingMachine(arr, k)
    currentState = 0

    For i from 0 to size - 1
        currentState = findNextState(currentState, text[i])
        If out[currentState] != 0
            For each word j from 0 to k - 1
                If out[currentState] & (1 << j) != 0
                    Print: "Word" arr[j] "occurs between" i - arr[j].size() + 1 "and" i
    Free memory: delete[] text

```