# Hash: prints the code with a hash at each line that closes a block, ignoring spaces and comments
# Use: python3 hash.py code.cpp | each hash covers from the line with { to the line with its }, the last one covers the whole file
import sys, hashlib

lines = open(sys.argv[1]).readlines()
code = [''.join(line.split('//')[0].split()) for line in lines]
last = max(i for i in range(len(code)) if code[i])
stack = []
for i, line in enumerate(lines):
    start = i
    for c in code[i]:
        if c == '{': stack.append(i)
        if c == '}': start = min(start, stack.pop())
    if i == last: start = 0
    h = hashlib.md5(''.join(code[start:i + 1]).encode()).hexdigest()[:3]
    print(line.rstrip(), h if start < i or i == last else '')
