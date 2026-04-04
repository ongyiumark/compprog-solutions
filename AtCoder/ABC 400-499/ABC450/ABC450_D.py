""" https://atcoder.jp/contests/abc450/tasks/abc450_d """
from collections import deque
n, k = [int(x) for x in input().split()]
A = [int(x) for x in input().split()]
A = sorted([x % k for x in A])

if n == 1:
  print(0)
else:
  dq = deque(A)
  best = dq[-1]-dq[0]
  for _ in range(n):
    first = dq.popleft()
    dq.append(first+k)

    if dq[-1]-dq[0] < best:
      best = dq[-1]-dq[0]
  
  print(best)