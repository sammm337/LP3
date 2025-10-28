import random

def naive_search(text, pattern):
    n = len(text)
    m = len(pattern)
    occurrences = []
    steps = 0

    for i in range(n - m + 1):
        match = True
        for j in range(m):
            steps += 1
            if text[i + j] != pattern[j]:
                match = False
                break
        if match:
            occurrences.append(i)

    return occurrences, steps


def rabin_karp_search(text, pattern, d=256, q=101):
    n = len(text)
    m = len(pattern)
    h = pow(d, m - 1) % q  # d^(m-1)
    p = 0  # hash value for pattern
    t = 0  # hash value for text
    occurrences = []
    steps = 0

    # Preprocessing: calculate initial hash values
    for i in range(m):
        p = (d * p + ord(pattern[i])) % q
        t = (d * t + ord(text[i])) % q

    for i in range(n - m + 1):
        steps += 1
        if p == t:
            # Check characters one by one
            if text[i:i + m] == pattern:
                occurrences.append(i)

        # Calculate hash for next window
        if i < n - m:
            t = (d * (t - ord(text[i]) * h) + ord(text[i + m])) % q
            if t < 0:
                t = t + q

    return occurrences, steps



chars = ['a', 'b', 'c', 'd', 'e']
large_text = ''.join(random.choices(chars, k=1_000_000))

# Generate a pattern that may or may not exist (length ~100)
# Option 1: Extract a real substring (guaranteed match)
pattern_from_text = large_text[500_000:500_100]

# Option 2: Create a synthetic pattern (random, maybe no match)
random_pattern = ''.join(random.choices(chars, k=100))

# Use whichever you want
text = large_text
pattern = pattern_from_text  # or pattern = random_pattern

# Print length confirmation
print(f"Length of text: {len(text)}")
print(f"Length of pattern: {len(pattern)}")

# Sample Input
# text = "ababcabcabababd"
# pattern = "ababd"

naive_result, naive_steps = naive_search(text, pattern)
rk_result, rk_steps = rabin_karp_search(text, pattern)

# Output Comparison
print("Text:", text)
print("Pattern:", pattern)
print("\nNaive Algorithm:")
print("Matches found at indices:", naive_result)
print("Steps (character comparisons):", naive_steps)

print("\nRabin-Karp Algorithm:")
print("Matches found at indices:", rk_result)
print("Steps (hash + verification):", rk_steps)

