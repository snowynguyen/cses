s = input() 
n = len(s) 
f = [0 for _ in range (n)] 

i = 1
j = 0 
while i < n: 
    while j > 0 and s[j] != s[i]:
        j = f[j - 1]
    if s[i] == s[j]:
        j += 1  
        f[i] = j
    i += 1

borders = [] 
border = n - 1 
while border > 0: 
    border = f[border]
    if border > 0: 
        borders.append(border) 
        border -= 1 
borders = reversed(borders) 
for b in borders: print(b, end=' ')
