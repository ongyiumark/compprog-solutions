""" https://atcoder.jp/contests/abc450/tasks/abc450_b """
n = int(input())
C = [[0]*n for _ in range(n)]

for i in range(0, n-1):
  x_list = [int(x) for x in input().split()]
  for j in range(i+1, n):
    C[i][j] = C[j][i] = x_list[j-i-1]

found = False
for i in range(n):
  for j in range(i+1, n):
    for k in range(j+1, n):
      if C[i][j] + C[j][k] < C[i][k]:
        found = True

print("Yes") if found else print("No")
