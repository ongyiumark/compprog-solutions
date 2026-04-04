""" https://atcoder.jp/contests/abc450/tasks/abc450_c """
h, w = [int(x) for x in input().split()]
S = [list(input()) for _ in range(h)]

# wrap everything in '.' then '#'
h, w = h+4, w+4
S = [
  list("#"*w),
  list("#"+"."*(w-2)+"#"),
  *[list("#.") + s + list(".#") for s in S],
  list("#"+"."*(w-2)+"#"),
  list("#"*w)
]

def dfs(si, sj):
  stack = [(si, sj)]
  while len(stack) != 0:
    ci, cj = stack.pop()
    S[ci][cj] = "X"
    for di, dj in [(-1,0), (1,0), (0,-1), (0,1)]:
      ni = ci+di
      nj = cj+dj
      if ni < 0 or ni >= h or nj < 0 or nj >= w:
        continue
      if S[ni][nj] != ".":
        continue
      
      stack.append((ni, nj))
    

count = 0
for i in range(h):
  for j in range(w):
    if S[i][j] == ".":
      dfs(i, j)
      count += 1

print(count-1)