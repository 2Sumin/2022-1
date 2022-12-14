/*
========약수============//
[문제]
양수 A가 N의 진짜 약수가 되려면, N이 A의 배수이고, A가 1과 N이 아니어야 한다.
어떤 수 N의 진짜 약수가 모두 주어질 때, N을 구하는 프로그램을 작성하시오.

[입력]
첫째 줄에 N의 진짜 약수의 개수가 주어진다. 이 개수는 50보다 작거나 같은 자연수이다.
둘째 줄에는 N의 진짜 약수가 주어진다.
1,000,000보다 작거나 같고, 2보다 크거나 같은 자연수이고, 중복되지 않는다.

[출력]
첫째 줄에 N을 출력한다. N은 항상 32비트 부호있는 정수로 표현할 수 있다.

[입력 예제]
input-1
2
4 2
output-1
8

input-2
1
2
output-2
4


6
3 4 2 12 6 8

14
14 26456 2 28 13228 3307 7 23149 8 6614 46298 56 4 92596
*/

#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    int tot; // 약수의 총 개수

    cin >> tot;
    int *div = new int[tot]; // 모든 약수

    for (int i = 0; i < tot; i++)
    {
        cin >> div[i];
    }

    sort(div, div + tot);

    cout << div[0] * div[tot - 1];
}