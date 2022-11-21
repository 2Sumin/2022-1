#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;
typedef vector<bool> matrixbool;

/*
input-1
4 16
2 5 10 5
40 30 50 10
output-1
0 0 0 115 0
1 2 40 115 40
2 7 70 115 70
3 17 120 115 70
3 7 70 80 70
4 12 80 80 80
4 7 70 70 80
2 2 40 98 80
3 12 90 98 90
4 17 100 98 90
4 12 90 90 90
3 2 40 50 90
1 0 0 82 90
90
2 40
10 50

input-2
4 16
5 2 5 10
30 40 10 50
output-2
0 0 0 115 0
1 2 40 115 40
2 7 70 115 70
3 17 120 115 70
3 7 70 80 70
4 12 80 80 80
4 7 70 70 80
2 2 40 98 80
3 12 90 98 90
4 17 100 98 90
4 12 90 90 90
3 2 40 50 90
1 0 0 82 90
90
2 40
10 50
*/

/*
<0-1 knapsack - backtracking>
상태공간트리 구성 -> 부분집합의 합 문제와 동일한 방식으로 (최적해 집합 찾기)


*/

//  As usual, 𝑛, 𝑊, 𝑤, 𝑝, 𝑚𝑎𝑥𝑝𝑟𝑜𝑓𝑖𝑡, 𝑖𝑛𝑐𝑙𝑢𝑑𝑒, 𝑏𝑒𝑠𝑡𝑠𝑒𝑡 are defined globally.
int n, W, maxprofit;
matrix1 w, p, sorted_w, sorted_p;
matrixbool include, bestset;

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
n=4, W=16
pi    = 40  30  50  10
wi    = 2   5   10  5
pi/wi = 20  6   5   2  (정렬 먼저 시키기 - fractional knapsack할 때처럼)
12
*/
int save;
bool promising(int i, int profit, int weight)
{
    // k-1번째 아이템을 얻은 이익 + 남은 k번째 아이템의 용량 (W-totweight) * 단위무게당 이익
    // bound : 남은 이익 + 현재 담은 이익 -> bound<=maxprofit이면 리턴 (nonpromising)
    int j, k, totweight, bound;

    //  [nonpromising 1] - 최대 무게를 넘었을 때 (용량 초과)
    // weight(현재 배낭에 담은 무게)가 W(최대용량)보다 크거나 같음
    // -> 더 이상 아래 노드 탐색 불필요
    if (weight >= W)
    {
        cout << i << " " << weight << " " << profit << " " << save << " " << maxprofit << endl;
        return false;
    }
    else
    {
        j = i + 1;
        bound = profit;
        totweight = weight;
        //총 아이템 개수 이하의 아이템을 포함하면서 최대용량을 초과하지 않는 k 찾기

        while (j <= n && totweight + sorted_w[j] <= W)
        {
            totweight += sorted_w[j];
            bound += sorted_p[j];
            j++;
        }
        k = j;
        // bound : 배낭에 담은 아이템과 남아있는 아이템으로 얻을 수 있는 한계 이익
        // 현재 노드에서 앞으로 얻을 수 있는 최대 이익
        if (k <= n)
            bound += (W - totweight) * ((float)sorted_p[k] / sorted_w[k]);
        save = bound;
        cout << i << " " << weight << " " << profit << " " << bound << " " << maxprofit << endl;
        // [nonpromising 2] - 남은 것 이익 다 더해도 maxprofit보다 적을 때
        // 현재까지 찾은 최적해의 이익이 현재 노드에서 앞으로 얻을 수 있는 최대 이익보다 더 크다면
        return bound > maxprofit;
    }
}

void array_copy(matrixbool include, matrixbool &bestset)
{
    for (int i = 1; i <= n; i++)
    {
        bestset[i] = include[i];
    }
}

void knapsack4(int i, int profit, int weight)
// i: SST의 depth -> 0
// profit :  0
// weight : 0
{

    if (weight <= W && profit > maxprofit)
    {
        maxprofit = profit;
        // copy from include to bestset.
        array_copy(include, bestset);
    }
    if (promising(i, profit, weight))
    {
        // 포함 시키는 경우
        include[i + 1] = true;
        knapsack4(i + 1, profit + sorted_p[i + 1], weight + sorted_w[i + 1]);
        // 포함 안 시키는 경우
        include[i + 1] = false;
        knapsack4(i + 1, profit, weight);
    }
}

int main()
{
    // 입력 1 - 첫번째 줄에 아이템의 개수 n과 배낭의 무게 W가 주어진다.
    cin >> n >> W;
    // 입력 2 - 두번째 줄에 n개의 아이템 무게 w[i]가 주어진다.
    w.resize(n + 1);
    sorted_w.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    // 입력 3 - 세번째 줄에 n개의 아이템 이익 p[i]가 주어진다.
    p.resize(n + 1);
    sorted_p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    include.resize(n + 1);
    bestset.resize(n + 1);

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

    cout << "***output***" << endl;

    // 출력 1 - 첫 번째 줄부터 한 줄에 하나씩 상태공간트리를 방문하는 노드의 상태를 출력하시오.
    // i weight profit bound maxprofit 순서로 노드를 출력한다
    cout << "print SST _ i weight profit bound maxprofit" << endl;
    maxprofit = 0;
    knapsack4(0, 0, 0);

    // 출력 2 - 노드의 상태 출력이 끝나는 다음 줄에 최대이익을 출력한다.
    cout << "max profit: " << maxprofit << endl;
    // 출력 3 - 이후로 배낭에 담은 아이템을 한 줄에 하나씩 무게와 이익 순서로 출력한다.
    // 아이템을 출력하는 순서는 처음에 단위무게당 이익으로 정렬한 순서대로 출력함에 주의할 것.
    cout << "items in knapsack" << endl;
    for (int i = 1; i <= n; i++)
        if (bestset[i])
            cout << "weight: " << sorted_w[i] << " profit: " << sorted_p[i] << endl;
}
