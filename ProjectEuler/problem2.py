def fibonacci() -> int:
    aux = 0
    f1 = 0
    f2 = 1
    res = 0
    sum = 0
    while(res < 4000000):
        res = f1 + f2
        f1 = f2
        f2 = res
        if f2 % 2 == 0:
            sum = sum + f2
    return sum

