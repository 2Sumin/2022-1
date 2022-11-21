#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> matrix1;
typedef vector<bool> matrixbool;
typedef vector<vector<bool>> matrixbool2;

/*
input-1
4 13
3 4 5 6
output-1
1
3 4 6

input-2
3 10
1 2 3
output-2
0

input-3
20 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
output-3
64
1 2 3 4 10
1 2 3 5 9
1 2 3 6 8
1 2 3 14
1 2 4 5 8
1 2 4 6 7
1 2 4 13
1 2 5 12
1 2 6 11
1 2 7 10
1 2 8 9
1 2 17
1 3 4 5 7
1 3 4 12
1 3 5 11
1 3 6 10
1 3 7 9
1 3 16
1 4 5 10
1 4 6 9
1 4 7 8
1 4 15
1 5 6 8
1 5 14
1 6 13
1 7 12
1 8 11
1 9 10
1 19
2 3 4 5 6
2 3 4 11
2 3 5 10
2 3 6 9
2 3 7 8
2 3 15
2 4 5 9
2 4 6 8
2 4 14
2 5 6 7
2 5 13
2 6 12
2 7 11
2 8 10
2 18
3 4 5 8
3 4 6 7
3 4 13
3 5 12
3 6 11
3 7 10
3 8 9
3 17
4 5 11
4 6 10
4 7 9
4 16
5 6 9
5 7 8
5 15
6 14
7 13
8 12
9 11
20

*/

/*
 <sum-of-subset problem>
 : 원소가 n개인 양의 정수 집합 w와 양의 정수 W가 주어졌을 때,
   합이 W가 되는 w의 부분집합 모두 찾기

*/

int W;              // 부분집합의 합이 W가 되게 함
matrix1 w;          // 집합
matrixbool include; // 원소가 부분집합에 들어갈 수 있으면 true, 못 들어가면 false 저장
matrixbool2 result; // include 배열 전부 저장

bool promising(int i, int weight, int total)
{
    // weight : 레벨 i 까지 "포함된" 모든 원소의 합
    // total :  남은 원소들의 합

    // promising 하지 않을 조건

    //  1. weight + w[i + 1] > W
    // 검색하기 전에 정수 원소를 오름차순으로 정렬해두면
    // 아직 고려해보지 않은 i+1번째 이후의 원소들 중 w[i+1]이 가장 작은 값인데
    // 가장 작은 원소인 w[i+1]을 포함했을 때도 W보다 더 큰 값이 된다면 더 이상 계산해볼 필요 없음 -> pruning
    // 2. weight + total < W
    // 남은 원소들(total)을 모두 더해도 W보다 작다면 더이상 확인할 필요 없음

    // weight == W : 답을 찾은 것
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}
void sum_of_subsets(int i, int weight, int total)
// i: 집합 인덱스, (현재 레벨)
// weight : 이때까지 포함한 원소의 합
// total : 현재 남은 것의 total
{
    if (promising(i, weight, total))
    {
        cout << i << " " << weight << " " << total << endl;
        // solution
        if (weight == W)
        {
            // 첫번째 원소부터 n번째 원소까지를 포함한다면 1, 포함하지 않는다면 0이
            // 저장돼있는 bool형 배열 include
            result.push_back(include);
            // for (int k = 1; k <= i; k++)
            // {
            //     cout << include[k];
            //     if (k != i)
            //         cout << " ";
            // }
            // cout << endl;
        }
        // 아직 solution이 아니라면
        // include 배열에 i+1번째 원소를 포함시킬지말지 결정
        else
        {
            // 그 레벨의 원소를 고려했으면 포함하든말든 total에서 빼주기
            // (W+1이 포함되든말든 total에서는 w[i+1] 빼줘야함)

            // left subtree
            // w[i+1] 포함 (다음 레벨의 원소를 포함)
            include[i + 1] = true;
            // 한 단계 지나니까 depth+1, 무게에 i+1번째 원소 무게 더하고, 남은 무게에서 i+1번째 원소 무게 빼고
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);

            // right subtree
            // w[i+1] 포함 X
            include[i + 1] = false;
            //포함 안 하니까 weight에 더 이상 안 더해지고, 포함 안 해주지만 단계 지나가니까 total에서는 i+1 무게 빼줌
            sum_of_subsets(i + 1, weight, total - w[i + 1]);
        }
    }
}

int main()
{
    // 입력 1 - 첫 줄에 원소의 개수 n과 임의의 정수 W가 주어진다.
    int n;
    cin >> n >> W;
    w.resize(n + 1);
    include.resize(n + 1);

    // 입력 2 - 둘째 줄에 n개의 정수가 주어진다.
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    cout << "***output***" << endl;

    // 출력 1 - 첫 줄에 원소의 합이 W가 되는 부분집합의 개수를 출력한다.
    int total = 0; // w 집합 모든 수의 합
    for (int i = 1; i <= n; i++)
        total += w[i];

    // 0 : root부터 시작, 현재 노드 합은 0, 남은 값의 합은 total
    sum_of_subsets(0, 0, total);

    cout << "the number of subset: " << result.size();
    if (result.size())
        cout << endl;

    // 출력 2 - 둘째 줄부터 원소의 합이 W가 되는 모든 부분집합을 한 줄에 하나씩 출력한다.
    //단, 부분집합에서의 원소 출력 순서는 주어진 S의 원소 순서와 동일해야 한다. (백트래킹 순서대로)
    matrix1 arr;
    // result배열 : solution이 되는 include 배열(bool)을 모두 저장해둔 배열
    for (int i = 0; i < result.size(); i++)
    {
        arr.clear();
        for (int j = 0; j < result[i].size(); j++)
        {
            if (result[i][j])
                arr.push_back(w[j]);
        }
        cout << i + 1 << "th solution: ";
        for (int k = 0; k < arr.size(); k++)
        {
            cout << arr[k];
            if (k != arr.size() - 1)
                cout << " ";
        }
        if (i != result.size() - 1)
            cout << endl;
    }
}