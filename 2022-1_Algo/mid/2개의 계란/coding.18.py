import random

n = 100
answer = random.randint(1, n)

def isSafe(height):
    if (height < answer):
        return True
    else:
        return False

# 계란이 하나인 경우

def eggDrop1(n):
    for height in range(1, n + 1):
        if (not isSafe(height)):
            return height

print(answer, eggDrop1(n))

# 계란이 무한한 경우

def eggDrop2(n):
    start = 1
    end = n
    while (start + 1 < end):
        mid = (start + end) // 2
        if (isSafe(mid)):
            start = mid
        else:
            end = mid
    return end

print(answer, eggDrop2(n))

# 계란이 몇 개나 필요할까?

def countEggDrop2(n):
    start = 1
    end = n
    count = 0
    while (start + 1 < end):
        count += 1
        mid = (start + end) // 2
        if (isSafe(mid)):
            start = mid
        else:
            end = mid
    return count

for i in range(1, 21):
    maxcount = 0
    n = 2 ** i
    for _ in range(1000):
        answer = random.randint(1, n)
        count = countEggDrop2(n)
        if (maxcount < count):
            maxcount = count
    print(n, maxcount)

# 계란이 만약 두 개 뿐이라면?

import math

def twoEggsDrop(n):
    sqrt_n = math.floor(math.sqrt(n))
    for height1 in range(sqrt_n, n + 1, sqrt_n):
        if (not isSafe(height1)):
            break
    for height2 in range(height1 - sqrt_n + 1, height1):
        if (not isSafe(height2)):
            return height2


n = 100
answer = random.randint(1, n)
print(answer, twoEggsDrop(n))
   
def twoEggsDrop2(n):
    count = 0
    sqrt_n = math.floor(math.sqrt(n))
    for height1 in range(sqrt_n, n + 1, sqrt_n):
        count += 1
        if (not isSafe(height1)):
            break
    for height2 in range(height1 - sqrt_n + 1, height1 + 1):
        count += 1
        if (not isSafe(height2)):
            return count

n = 100
for answer in range(1, 101):
    print(answer, twoEggsDrop2(n))
   
