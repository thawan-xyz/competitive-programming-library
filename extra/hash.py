# Hash: prints each line of code with the hash of that line, ignoring spaces and comments
# Use: python3 hash.py code.cpp | compare with the notebook line by line
import sys, hashlib

for line in open(sys.argv[1]):
    code = ''.join(line.split('//')[0].split())
    h = hashlib.md5(code.encode()).hexdigest()[:3] if code else ''
    print(f'{h:3} {line}', end='')
