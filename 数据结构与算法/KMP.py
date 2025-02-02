def getnext(pattern) :
    next = [0] * len(pattern)
    j = 0
    for i in range(1, len(pattern)) :
        while j > 0 and pattern[i] != pattern[j] :
            j = next[j - 1]
        if pattern[i] == pattern[j] :
            j += 1
        next[i] = j
    return next

def kmp(text, pattern) :
    j = 0
    next = getnext(pattern)
    for i in range(len(text)) :
        while j > 0 and text[i] != pattern[j]:
            j = next[j - 1]
        if text[i] == pattern[j] :
            j += 1
        if j == len(pattern) :
            return i - len(pattern) + 1
    return -1

def main():
    text = "ABABDABACDABABCABAB"
    pattern = "ABABCABAB"
    result = kmp(text, pattern)
    if result != -1:
        print("Pattern found at index", result)
    else:
        print("Pattern not found")

if __name__ == "__main__":
    main()

