with open('shuffle.txt') as pf, open('shuffle.py.sorted.txt', 'w') as po:
    lst = []
    for line in pf:
        lst.append(int(line.strip()))
        
    lst.sort()

    for n in lst:
        po.write(str(n) + '\n')
