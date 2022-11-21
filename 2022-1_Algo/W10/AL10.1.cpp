#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;

typedef unsigned long long int ull;
typedef vector<int> matrixint;
typedef vector<string> matrixString;
typedef vector<ull> matrixull;

/*
input-1
4
output-1
2
3142

input-2
9
output-2
352
974286135

input-3
12
output-3
14200
975811210364211
*/

/*
 백트래킹 : 상태공간트리 (SST)를 DFS로 탐색
 방문 중인 노드가 유망한지 체크
 만약 유망하지 않으면 부모 노드로 되돌아감 (backtrack)
 -> 하위 트리를 가지치기 함 (pruning)

 <n-Queens 문제>
 : n*n 체스보드에 n개의 퀸을 배치하는 문제
   퀸은 같은 행,열,대각선에 있는 것을 다 잡아먹음
   어떤 퀸도 다른 퀸에 의해 잡아먹히지 않도록,
   같은 행,열,대각선에는 다른 퀸을 놓지 않으면서
   n개의 퀸을 배치하는 문제

*/

int n;
matrixint col;
// col 배열에 col[행]=열 의 형태로 저장돼있음.
matrixString result; // 문자열 하나에 solution 하나씩 저장
// 2차원 res배열의 행이 0일때부터 결과 저장
// res배열의 행의 개수 = 경우의 수(cnt)

bool promising(int i)
{
    // 입력 받은 행 (i+1) 까지 탐색하며
    // 이전에 찾은 퀸(k=1 ~ i-1)들의 열 위치와 같은 열에 위치해 있거나,
    // 대각선에 위치해 있다면 불가능하다고 판단 -> flag = false -> pruning
    int k = 1; // 첫번째 행부터 탐색
    bool flag = true;
    while (k < i && flag) // i-1번째 행까지 탐색
    {
        // 1. (col[i] == col[k]) 이면 같은 열에 놓인 것 -> promising X
        // 2. (abs(col[i] - col[k]) == i - k), 즉 가로 길이와 세로 길이의 차가 같으면
        // 열의 차와 행의 차가 같다면 대각선에 놓인 것 -> promising X
        if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k))
            flag = false;
        k++; // 다음 행 탐색
    }
    return flag;
}

int cnt = 0; // solution의 개수 세기
void queens(int i)
{
    int j;
    // i번재 depth의 column으로 promising한지 check
    if (promising(i))
    {
        // 끝까지 다 놓았다면
        if (i == n)
        {
            // 현재 col 배열에 저장된 값을 string으로 변경해서 result 배열에 넣기
            string str;

            // 현재 col 배열에 저장된 값들을 문자로 변경해서 하나의 문자열로 만들기
            for (int k = 1; k <= n; k++)
                str += to_string(col[k]);

            // 문자열을 result 배열에 저장
            result.push_back(str);
            cnt++; // solution의 개수 세기
        }
        // 아직 끝까지 다 놓지 못했다면 (solution이 아니면)
        else
            // 다음 행에서 모든 열 검사
            for (j = 1; j <= n; j++)
            {
                // i+1 번째 행의 j번째 열에 놓기
                col[i + 1] = j;
                // 재귀할 때 promising 검사 -> pruning -> backtracking
                // pruning 되면 재귀할 때 if문 안으로 못 들어오고 재귀 종료
                queens(i + 1);
            }
    }
}

int main()
{
    // 입력 1 - n의 값이 주어진다.
    cin >> n;
    col.resize(n + 1);

    cout << "***output***" << endl;

    // 출력 1 - 가능한 보드의 배치 개수를 출력한다.
    queens(0);
    cout << "the number of cases: " << cnt << endl;

    // 출력 2 - col 배열의 값을 숫자의 문자열로 취급했을 때 최대값을 출력한다.
    matrixull res;
    // result 배열에 문자열로 저장되어있는 solution들을 ull형태(숫자)로 변경 후 res 배열에 넣기
    // (크기 비교를 위해서)
    for (int i = 0; i < cnt; i++)
        res.push_back(stoull(result[i]));

    // 저장된 값: 1행에 1번째열, 2행에 3번째 열, 3행에 2번째 열에 뒀다면 132
    // res 배열에 저장된 값들 중 가장 큰 값을 max 변수에 담은 후 출력
    ull max = *max_element(res.begin(), res.end());
    cout << "max: " << max << endl;
}