def collatz(n):
    seq = [n]
    while (n > 1):
        if (n % 2 == 0):
            n = n // 2
        else:
            n = 3 * n + 1
        seq.append(n)
    return seq

print(collatz(1))
print(collatz(2))
print(collatz(3))

for n in range(1, 10):
    print(collatz(n))
    
for n in range(1, 100):
    print(len(collatz(n)), end = ' ')
print()

# 콜라츠 수열의 길이가 100인 숫자들 중에서 가장 작은 수는?
n = 0
while (True):
    n += 1
    halestone = collatz(n)
    if (len(halestone) == 100):
        break
print(halestone)
print('길이가 100인 가장 작은 우박수는', n)

# 10000 이하의 자연수 중에서 콜라츠 수열의 길이가 가장 긴 수
maxlength = 0
maxseq = []
for n in range(1, 10001):
    halestone = collatz(n)
    length = len(halestone)
    if (maxlength < length):
        maxlength = length
        maxseq = halestone

print(maxseq)
print('10,000 이하의 가장 긴 우박수는', maxseq[0])
print('그리고 그 길이는', maxlength)

# 콜라츠 수열의 길이가 500보다 큰 첫번째, 열번째 자연수는?

n = 0
while (True):
    n += 1
    halestone = collatz(n)
    length = len(halestone)
    if (length > 500):
        print(halestone[0], length)

