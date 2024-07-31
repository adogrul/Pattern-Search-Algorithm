## Knuth-Morris-Pratt (KMP) Algorithm

The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm used to find occurrences of a pattern within a text. It achieves linear time complexity by preprocessing the pattern to avoid redundant comparisons during the search process. Here’s a detailed breakdown of how the KMP algorithm works:

### 1. Preprocessing Phase

The preprocessing phase involves creating a partial match table (also known as the prefix table or failure function). This table helps the algorithm avoid unnecessary comparisons by keeping track of the longest prefix of the pattern that is also a suffix.

#### a. Prefix Table (Partial Match Table)

**Purpose:** The prefix table provides information about the longest proper prefix of the pattern which is also a suffix for each prefix of the pattern. This allows the algorithm to skip re-evaluations of characters in the pattern when a mismatch occurs.

**Construction:**

1. **Initialize:** Create an array `lps` (Longest Prefix Suffix) of length `m` (where `m` is the length of the pattern) and initialize the first element to 0.

2. **Iterate Through the Pattern:** Use two pointers, `i` and `j`. `i` iterates through the pattern, and `j` tracks the length of the current longest prefix which is also a suffix.

**Algorithm:**

- **Match:** If `pattern[i]` matches `pattern[j]`, set `lps[i] = j + 1`, increment both `i` and `j`.

- **Mismatch:** If there is a mismatch and `j` is not zero, set `j = lps[j - 1]`. If `j` is zero, set `lps[i] = 0` and increment `i`.

**Example:**

Pattern: `"ABABAC"`

- **i = 0:** Initialize `lps[0] = 0`.

- **i = 1:** `pattern[1]` matches `pattern[0]`, so `lps[1] = lps[0] + 1 = 1`. Increment both `i` and `j`.

- **i = 2:** `pattern[2]` matches `pattern[1]`, so `lps[2] = lps[1] + 1 = 2`. Increment both `i` and `j`.

- **i = 3:** `pattern[3]` matches `pattern[2]`, so `lps[3] = lps[2] + 1 = 3`. Increment both `i` and `j`.

- **i = 4:** `pattern[4]` matches `pattern[3]`, so `lps[4] = lps[3] + 1 = 4`. Increment both `i` and `j`.

- **i = 5:** `pattern[5]` does not match `pattern[4]`. Set `j = lps[4 - 1] = 3`, and compare `pattern[5]` with `pattern[3]`. Since `pattern[5]` is not equal to `pattern[3]`, set `lps[5] = 0` and increment `i`.

The final prefix table (LPS array) for the pattern `"ABABAC"` is:

lps = [0, 1, 2, 3, 4, 0]

## 2. Searching Phase

Once the prefix table is constructed, use it to search the text efficiently.

**Initialize:** Set pointers `i` and `j` to 0. `i` iterates over the text, and `j` iterates over the pattern.

**Comparison:**

- **Match:** If `text[i]` matches `pattern[j]`, increment both `i` and `j`.

- **Mismatch:** If there is a mismatch:
  - If `j` is not zero, set `j = lps[j - 1]` and continue.
  - If `j` is zero, increment `i` and continue.

- **Pattern Found:** When `j` equals the length of the pattern, a match is found. Record the position and set `j = lps[j - 1]` to search for more occurrences.

**Continue:** Continue until the end of the text is reached.

**Example**

Suppose you have a pattern `"ABABAC"` and a text `"ABABABABABABAC"`:

1. **Build Prefix Table:** Construct the prefix table as described above.

2. **Search Process:**
   - Align the pattern with the beginning of the text.
   - Compare characters and use the prefix table to skip unnecessary comparisons when mismatches occur.
   - For example, when matching `"ABABAC"` in `"ABABABABABABAC"`, the algorithm uses the prefix table to skip over sections of the text that have already been matched, thus speeding up the search.

### Complexity

**Time Complexity:**

- **Preprocessing:** O(m), where `m` is the length of the pattern. Building the prefix table takes linear time.

- **Searching:** O(n), where `n` is the length of the text. The search process also takes linear time due to efficient skipping.

# Here's the Psuedo Codes

## `computeLPSArray`
```cpp
Function computeLPSArray(pattern, M, lps)
    len = 0 // length of the previous longest prefix suffix
    lps[0] = 0 // lps[0] is always 0

    i = 1
    While i < M
        If pattern[i] == pattern[len]
            len++
            lps[i] = len
            i++
        Else
            If len != 0
                len = lps[len - 1] // Use the previously computed lps value
            Else
                lps[i] = 0
                i++

```
## `KMPSearch`
```cpp
Function KMPSearch(pattern, path)
    txt = ReadAllBytes(path) // Read file content into a char array
    If txt is NULL
        Print error message and return

    M = length of pattern
    N = size of file content
    If M <= 0 or N <= 0
        Print error message and return

    Create an array lps with size M

    // Preprocess the pattern to create lps array
    computeLPSArray(pattern, M, lps)

    i = 0 // index for txt[]
    j = 0 // index for pattern[]
    While (N - i) >= (M - j)
        If pattern[j] == txt[i]
            Increment both i and j
            If j == M
                Print the index where the pattern is found
                j = lps[j - 1] // Use the lps array to skip characters
        Else
            If j != 0
                j = lps[j - 1]
            Else
                i = i + 1

    Free memory: delete[] lps
    Free memory: delete[] txt
```
