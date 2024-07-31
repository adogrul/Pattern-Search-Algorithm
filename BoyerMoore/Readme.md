# Boyer-Moore Algorithm

## 1. Preprocessing

### a. Bad Character Heuristic

**Purpose:** Helps the algorithm determine how far to shift the pattern when a mismatch occurs.

**Preprocessing Steps:**

- **Create the Bad Character Table:**
  - For each character in the pattern, create an array (or table) that records the last occurrence of that character within the pattern.
  - **Algorithm:** For each character in the pattern (from left to right), store its index in the bad character table. If a character does not appear in the pattern, its value is set to -1.

- **Example:**
  
  **Pattern:** `ABCD`
  
  **Bad Character Table:**
  
  ```makefile
  A: 0
  B: 1
  C: 2
  D: 3
## Mismatch Handling

When a mismatch occurs, shift the pattern so that the mismatched character in the text aligns with its last occurrence in the pattern, or shift it past the mismatch if it doesn't appear in the pattern.

### Good Suffix Heuristic

**Purpose:** Optimizes the search by taking advantage of partial matches.

**Preprocessing Steps:**

1. **Create the Good Suffix Table:**

   Constructed based on the suffixes of the pattern that have been matched. Indicates how far to shift the pattern when a partial match is found.

   **Algorithm:** For each suffix of the pattern, find the rightmost occurrence of that suffix or a similar suffix in the pattern and use it to determine the shift.

   **Example:**

   Pattern: `ABCAB`

   Good Suffix Table: This table is more complex and involves finding suffixes that align with prefixes of the pattern. For `ABCAB`, it might look something like:

```
Position: 0 1 2 3 4
Shift: 2 3 2 4 5
```

### Searching

1. **Alignment:** Start by aligning the pattern with the beginning of the text.

2. **Character Comparison:**

- Compare characters from right to left in the pattern. If all characters match, report a successful match.
- If a mismatch occurs, use the bad character heuristic to determine how far to shift the pattern.

3. **Shift the Pattern:**

- Use the bad character table to shift the pattern based on the mismatched character.
- Optionally, use the good suffix table to shift further, based on the partial matches.

4. **Repeat:** Continue aligning and comparing until the end of the text is reached.

**Example:**

Pattern: `ABCD`

Text: `ABCDABCDABC`

- **Initial Alignment:** Align `ABCD` with the beginning of `ABCDABCDABC`.
- **Comparison:** Compare `ABCD` with the first four characters of the text. All match, so report a match.
- **Shifting:** Use the bad character and good suffix heuristics to determine the next alignment. For instance, if there’s a mismatch at the end of `ABCD`, shift the pattern to align it with the next possible match in the text.

### Complexity

**Time Complexity:**

- **Best Case:** O(n / m) where `n` is the length of the text and `m` is the length of the pattern. This is when the bad character heuristic leads to maximum shifts.
- **Average Case:** O(n) with a good heuristic, because the algorithm skips over parts of the text.
- **Worst Case:** O(n * m) in scenarios where the heuristics do not provide effective shifts (e.g., with repetitive patterns).

**Space Complexity:** O(m) for storing the bad character and good suffix tables.

# Here's the Psuedo Codes

## `badCharHeuristic`
```cpp
Function badCharHeuristic(str, size, badchar)
    For i from 0 to NO_OF_CHARS - 1
        badchar[i] = -1 // Initialize all occurrences to -1

    For i from 0 to size - 1
        badchar[str[i]] = i // Set the last occurrence of each character

```

## `search`
```cpp
Function search(filePath, pat)
    txt = ReadAllBytes(filePath) // Read file content into a char array
    m = size of pat // Pattern length
    n = get_file_size(filePath) // File size

    Create an array badchar with size NO_OF_CHARS

    // Initialize the bad character heuristic array
    badCharHeuristic(pat, m, badchar)

    s = 0 // Shift of the pattern with respect to text

    While s <= (n - m)
        j = m - 1 // Start from the end of the pattern

        // Reduce j while pattern matches the text at shift s
        While j >= 0 and pat[j] == txt[s + j]
            j--

        // If j is -1, pattern is found at shift s
        If j < 0
            Print "pattern occurs at shift = s"

            // Shift pattern based on the bad character heuristic
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1
        Else
            // Shift pattern to align bad character in text with its last occurrence in pattern
            s += max(1, j - badchar[txt[s + j]])

    Free memory: delete[] txt

```

