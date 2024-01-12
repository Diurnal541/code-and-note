# coding=gb2312
def calculate_alternating_series(n):
    result = 0
    for i in range(1, n+1):
        term = (-1)**(i-1) * (1 / (3*i - 2))
        result += term
    return result

# 计算数列的第100项
result_100 = calculate_alternating_series(100)
print(result_100)