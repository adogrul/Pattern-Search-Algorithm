## Rabin-Karp Algorithm

### 1. Algorithm Overview
The Rabin-Karp algorithm uses a rolling hash function to transform each substring of the text into a numerical value. By comparing these hash values instead of the actual strings, the algorithm can quickly identify potential matches. If the hash values of the pattern and a substring of the text match, a further check is done to confirm that the actual strings match.

### 2. Hash Function
A simple and commonly used hash function for strings is the polynomial rolling hash. The hash value of a string is calculated using the following formula:

\[ \text{Hash}(s) = \left( s[0] \cdot p^{m-1} + s[1] \cdot p^{m-2} + \ldots + s[m-1] \cdot p^0 \right) \mod q \]

where:
- \( s[i] \) is the ASCII value of the character at position \( i \),
- \( p \) is a chosen base (a small prime number, e.g., 31),
- \( q \) is a large prime number to mod the hash value (to avoid overflow),
- \( m \) is the length of the pattern.

### 3. Steps of the Rabin-Karp Algorithm

**Preprocessing:**
1. Calculate the hash value of the pattern.
2. Calculate the hash value of the first substring of the text of the same length as the pattern.

**Sliding Window:**
1. Slide the pattern over the text one character at a time.
2. For each position, compare the hash value of the current text substring with the hash value of the pattern.
3. If the hash values match, perform a character-by-character comparison to confirm the match.

**Hash Value Update:**
Efficiently update the hash value of the text substring as you slide the window. This can be done using the following formula:

\[ \text{Hash}(s_{i+1}) = \left( p \cdot \left( \text{Hash}(s_i) - s[i] \cdot p^{m-1} \right) + s[i+m] \right) \mod q \]

### 4. Example

Suppose you have a pattern `"ABC"` and a text `"ABABABC"`:

**Initial Hash Calculation:**
1. Compute the hash of the pattern `"ABC"`.
2. Compute the hash of the first substring `"ABA"` of the text.

**Sliding Window:**
1. Slide the window over the text and update the hash value for each new substring.
2. Compare the updated hash value with the pattern's hash value.

**Match Check:**
If the hash values match, verify by comparing the actual strings.

### 6. Complexity

**Time Complexity:**
- **Preprocessing:** O(m) for calculating the hash of the pattern.
- **Searching:** O(n) for sliding the window over the text and updating the hash value, making the overall complexity O(n + m).
- However, in the worst case (e.g., due to hash collisions), the complexity can degrade to O(n * m).

**Space Complexity:** O(1) additional space for variables, excluding the input text and pattern.
# Here's the Psuedo Codes
## `search`
```cpp
Function search(keywords, filePath, q)
    pat = keywords.c_str()  // Convert keywords to a C-style string
    M = length of pat
    N = get_file_size(filePath)  // Get the size of the file
    txt = ReadAllBytes(filePath)  // Read file content into a char array

    Initialize p = 0, t = 0, h = 1

    // Compute the value of h = pow(d, M-1) % q
    For i from 0 to M-2
        h = (h * d) % q

    // Compute the initial hash values of the pattern and the first window of text
    For i from 0 to M-1
        p = (d * p + pat[i]) % q
        t = (d * t + txt[i]) % q

    // Slide the pattern over the text one by one
    For i from 0 to N-M
        // If the hash values of the current window of text and pattern match
        If p == t
            // Check characters one by one
            For j from 0 to M-1
                If txt[i + j] != pat[j]
                    Break

            // If all characters match, pattern is found
            If j == M
                Print "Pattern found at index i"

        // Calculate hash value for the next window of text
        If i < N-M
            t = (d * (t - txt[i] * h) + txt[i + M]) % q

            // Convert negative hash value to positive
            If t < 0
                t = t + q

    Free memory: delete[] txt

```