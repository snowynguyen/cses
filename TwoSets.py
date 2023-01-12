n = int(input()) 
totalsum = n * (n + 1) // 2
if (totalsum % 2 == 1):
    print("NO")
else: 
    suma = sumb = 0 
    a = []
    b = []
    for x in range(n, 0, -1): 
        if (suma + x <= totalsum // 2):
            suma += x
            a.append(x)
        else:
            sumb += x
            b.append(x)
    print("YES")
    print(len(a)) 
    for i in a: print(i, end=' ')
    print('') 
    print(len(b)) 
    for i in b: print(i, end=' ')