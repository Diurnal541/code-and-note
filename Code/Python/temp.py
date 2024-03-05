import math
d = float(input())
P = float(input())
S = float(input())
r = (d * P / (math.pi * S)) ** (1 / 3)
print("%.2f" % r)
