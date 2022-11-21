#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

/*
input-1
3
5 10 20
50 60 140
1
30
output-1
200
1 10 50
1 20 50
1 30 50
2 20 140
2 30 190
3 30 200

input-2
4
2 5 10 5
40 30 50 10
4
8
16
20
25
output-2
70
1 3 40
1 8 40
2 3 40
2 8 70
3 3 40
3 8 70
4 8 70
90
1 1 0
1 6 40
1 11 40
1 16 40
2 1 0
2 6 40
2 11 70
2 16 70
3 11 70
3 16 90
4 16 90
120
1 5 40
1 10 40
1 15 40
1 20 40
2 5 40
2 10 70
2 15 70
2 20 70
3 15 90
3 20 120
4 20 120
130
1 5 40
1 10 40
1 15 40
1 20 40
1 25 40
2 10 70
2 15 70
2 20 70
2 25 70
3 20 120
3 25 120
4 25 130
*/

/*
 <0-1 knapsack problem - DP>
 : 배낭의 용량을 넘지 않은면서 가치가 최대가 되게
 DP
 2차원 배열 P
 P[i][w] : 총 무게가 w를 초과할 수 없을 때 처음 i개 아이템에서만 선택할 때 얻는 최적의 이익 - i개 아이템으로 w의 이익
 P[n][w] : n개의 아이템으로 얻을 수 있는 최대 이익 - solution

  1. 재귀 관계식 찾기
   P[i][w]
    1) max(P[i-1][w], pi+P[i-1][w-wi]) if wi <= w
     -> i번째 아이템을 포함하지 않거나 포함하거나
     행에는 몇번째 아이템을 담을지 말지 고려중임을 표현,
     열에는 앞으로 배낭에 담을 수 있는 남은 무게
     -> i-1번째 아이템을 담으면 그만큼 배낭 수용 무게가 줄어드니까 빼는 것
    2) P[i-1][w] if wi > w
     -> 무게 초과했으면 i번째 아이템 제외
  2. Bottom up

  -> 시간복잡도 세타_(nW) -> W가 너무 큰 값이라면 W=n! -> 시간복잡도 세타_(n!)
     -> 효율적인 동적계획법 사용
*/

int n;
matrix1 p, w, W, sorted_p, sorted_w;

typedef struct item *item_ptr;
typedef struct item
{
    int id;
    int weight;
    int profit;
    int profit_per_unit;
} item_t;

struct compare
{
    bool operator()(item_t *i, item_t *j)
    {
        if (i->profit_per_unit < j->profit_per_unit)
            return true;
        return false;
    }
};

typedef priority_queue<item_ptr, vector<item_ptr>, compare> PriorityQueue;

item_ptr create_node(int i, int w, int p)
{
    item_ptr item = (item_ptr)malloc(sizeof(item_t));
    item->id = i;
    item->weight = w;
    item->profit = p;
    item->profit_per_unit = p / w;
    return item;
}

void sorting(PriorityQueue &PQ, int n, matrix1 &w, matrix1 &p)
{
    for (int i = 1; i <= n; i++)
    {
        item_ptr item = create_node(i, w[i], p[i]);
        PQ.push(item);
    }
}

/*
n = 3
wi : 5  10 20
pi : 50 60 140
W=30
구하는 것 : P[3][30] - 3개의 아이템으로 30의 무게를 넘지 않게하는 최대 이익이 얼마인가
-P[2][30] (w3 포함 안 시킴) - 아이템 개수만 줄어들음
-P[2][30-20] + 140 = P[2][10] + 140 (w3 포함 시킴) - 배낭 용량이 담은 w3만큼 줄어들었다
leaf node에 가면 P[0][w] = 0 (
    P[n][0] : 배낭에 남은 게 없으면
)
*/

/*
i번째까지의 원소와 w라는 배낭무게를 가지고 최대값 찾기
P[i][w]
-wi를 포함하면 : P[i-1][w-wi]+pi //아이템 개수 줄고, 남은 무게에서 wi 무게 빼고, 최대 이익에 pi 더하기
-wi를 제외하면 : P[i-1][w] //배낭무게는 그대로, 아이템 개수는 준다. 최대 이익에는 i번째 원소의 이익을 더하지 않는다
wi를 포함했을 때와 제외했을 때를 비교해서 더 큰 값으로
*/
// int knapsack2(map<pair<int, int>, int> &P)
// {

//     // 1. 초기화 - 바닥
//     for (int i = 0; i <= n; i++)
//         // w=0 배낭에 더이상 못 담을 때
//         P[i][0] = 0;
//     for (int j = 1; j <= W; j++)
//         // p=0 담을 아이템이 없을 때
//         P[0][j] = 0;
//     // 2. i번째 아이템을 배낭에 담았을 때봐 안 담았을 때의 이익을 비교하면서 올라가기
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= W; j++)
//             // wi번째 용량이 이미 배낭 무게를 넘어갔다면 굳이 더 따질 필요 없음
//             P[i][j] = (w[i] > j) ? P[i - 1][j] : max(P[i - 1][j], p[i] + P[i - 1][j - w[i]]);
//     return P[0][W];
// }

// 모든 무게에 대해서 고려할 필요없음
// 무게의 모든 집합 (2^n) 을 찾기
// P 배열을 n*w 로 만들지 말고 필요한 항목만 만들기

int knapsack3(int n, int W, matrix1 w, matrix1 p, map<pair<int, int>, int> &P)
{ // map : n, , maxProfit
    //남은 아이템이 없거나 더 이상 담을 수 있는 무게(W)가 0이 되면
    if (n == 0 || W <= 0)
    { // exit condition
        P[make_pair(n, W)] = 0;
        return 0;
    }
    // lvalue: 포함 안 했을 때 -> P[n-1][w]를  계산이 되어있으면 그냥 넣고 아니면 재귀호출해서 집어넣기
    // -> 계산 되어있으면 그냥 넣으니까 중복 부분문제를 해결하는 메모이제이션
    int lvalue = (P.find(make_pair(n - 1, W)) != P.end()) ? P[make_pair(n - 1, W)] : knapsack3(n - 1, W, w, p, P);
    // rvalue: 포함 했을 때 -> P[n-1][w-wi]를  계산이 되어있으면 그냥 넣고 아니면 재귀호출해서 집어넣기
    int rvalue = (P.find(make_pair(n - 1, W - w[n])) != P.end()) ? P[make_pair(n - 1, W)] : knapsack3(n - 1, W - w[n], w, p, P);
    // w[i] > W 라면 w[i]는 제외시켜야 함 -> w[i-1]의 총 합 그대로 가야 함
    // w[i] <= W 라면 w[i]는 포함될 수도 안 될 수도 -> 담은 거랑 안 담은 것 중 최댓값 찾기
    P[make_pair(n, W)] = (w[n] > W) ? lvalue : max(lvalue, p[n] + rvalue);
    // W를 넘지 않으면서 n개의 아이템으로 얻을 수 있는 최대 이익
    return P[make_pair(n, W)];
}

int main()
{
    // 입력 1 -  첫 번째 줄에 아이템의 개수 n이 주어진다.
    cin >> n;

    // 입력 2 -  두 번째 줄에 n개의 무게 w[i]가 주어진다.
    w.resize(n + 1);
    sorted_w.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    // 입력 3 -  세 번째 줄에 n개의 이익 p[i]가 주어진다.
    p.resize(n + 1);
    sorted_p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    // 정렬
    PriorityQueue PQ;
    sorting(PQ, n, w, p);
    int i = 1;
    while (!PQ.empty())
    {
        item_ptr ptr = PQ.top();
        sorted_w[i] = ptr->weight;
        sorted_p[i++] = ptr->profit;
        PQ.pop();
    }

    // 입력 4 -  네 번째 줄에 배낭 무게의 개수 T가 주어진다.
    int T;
    cin >> T;

    // 입력 5 -  이후로 T개의 줄에 한 줄에 하나씩 배낭 무게 W가 주어진다.
    W.resize(T + 1, 0);
    for (int i = 1; i <= T; i++)
        cin >> W[i];

    cout << "***output***" << endl;

    for (int i = 1; i <= T; i++)
    {
        map<pair<int, int>, int> P;
        P[make_pair(0, 0)] = 0;
        // 출력 1 -  첫 줄에 최대 이익 maxprofit을 출력한다.
        int res = knapsack3(n, W[i], sorted_w, sorted_p, P);
        cout << "max profit: " << res << endl;
        // 출력 2 -  이후로 알고리즘의 실행과정에서 결과 테이블 P에 저장한
        // 이익이 0이 아닌 모든 항목 P[i][j]를 (i, j)의 오름차순으로 모두 출력한다
        cout << "P table" << endl;
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= W[i]; k++)
            {
                if (P.count(make_pair(j, k)) != 0)
                    cout << j << " " << k << " " << P[make_pair(j, k)] << endl;
            }
        }
    }
}