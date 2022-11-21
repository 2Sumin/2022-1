/*
교재: Algorithm 8.6 Selection by Median of Medians (알고리즘에 의해 선택되는 중앙값 출력)

BOJ # 1037 약수

BOJ # 1978. 소수 찾기

BOJ # 1929. 소수 구하기 (에라토스테네스의 체)

BOJ # 16563. 어려운 소인수분해 (에라토스테네스의 체 응용)

BOJ # 7450. Bin Packing (가방 꾸리기 문제)

SWEA # 8016. 홀수 피라미드 (홀수 피라미드의 합을 구해볼 것)
*/

/*

<<소수 구하기>>
[문제]
M이상 N이하의 소수를 모두 출력하는 프로그램을 작성하시오.

[입력]
첫째 줄에 자연수 M과 N이 빈 칸을 사이에 두고 주어진다.
(1 ≤ M ≤ N ≤ 1,000,000)
 M이상 N이하의 소수가 하나 이상 있는 입력만 주어진다.

[출력]
한 줄에 하나씩, 증가하는 순서대로 소수를 출력한다.

[입력 예제]
1.
3 16
출력
3
5
7
11
13

2.


*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int min, max;
    bool *prime;
    cin >> min;
    cin >> max;
    prime = new bool[max + 1];
    fill_n(prime, max + 1, 1);
    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i <= sqrt(max); i++)
        if (prime[i] == true)
            for (int j = i * 2; j <= max; j += i)
                prime[j] = false;

    int count = 0;

    for (int i = min; i <= max; i++)
        if (prime[i] == true)
        {
            cout << i << "\n";
            count++;
        }
    cout << "count : " << count << endl;
    return 0;
}