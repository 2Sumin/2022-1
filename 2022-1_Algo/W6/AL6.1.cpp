#include <iostream>
#include <vector>
#include <string.h>

//연쇄 행렬 곱셈 문제

/*
sample input1
6
5 2 3 4 6 7 8
sample output
0 30 64 132 226 348
0 24 72 156 268
0 72 198 366
0 168 392
0 336
0
0 1 1 1 1 1
0 2 3 4 5
0 3 4 5
0 4 5
0 5
0
348
((A1)(((((A2)(A3))(A4))(A5))(A6)))
input2
1
3 5
output
0
0
0
(A1)
*/

using namespace std;

#define INF 999999

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

int minimum(int i, int j, int &mink, matrix1 &d, matrix2 &M)
{
    // M[i][j]=minValue, P[i][j]=minK
    //최적해는 리턴값 (minValue)안에 넣어주고,
    //최적값 (mink) 는 mink안에 저장해두기
    int minValue = INF, value;
    for (int k = i; k <= j - 1; k++)
    {
        // 각 부분 행렬의 곱셈 횟수    + 두 행렬의 곱셈 횟수
        value = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
        if (minValue > value)
        {
            minValue = value;
            mink = k;
        }
    }
    return minValue;
}

void minmult(int n, vector<int> &d, matrix2 &M, matrix2 &P)
{
    // 1. main diagonal -> M[i][i] : 그냥 행렬 그 자체 (곱하거나 따로 처리할 것 없음) -> 0 (bottom)
    // M[i][i]이면 Ai 행렬 하나만 있는 거니까 곱하는 횟수가 없음
    for (int i = 1; i <= n; i++)
        M[i][i] = 0;

    //곱셈 횟수 구할 때 일단 두 부분으로 쪼개서 각 부분의 곱셈 횟수 + 합쳐서 다시 곱하는 곱셈횟수
    // diagonal=2일 때
    // M[4][6] = M[4][k] + M[k+1][6] -> k=4,5 테스트해보고 둘 중 더 작은 값
    // k=4이면 A4(A5*A6), k=5이면 (A4*A5)A6 -> 이 때 알아야 하는 A5*A6, A4*A5는 이 전 단계의 diagonal=1일 때 구해서 저장되어있음

    // 2. diagonal =1 부터 구해야 함 (ex. diagonal2 에서 main dia, diagonal1 이용함)
    for (int diagonal = 1; diagonal <= n - 1; diagonal++)
        // dia 1 일 때, M[1][2],M[2][3], ... ,M[5][6] 까지
        // -> i는 1 ~ 5 , j 는 i+1(dia)
        // dia 2 일 때, M[1][3],M[2][4], ... ,M[4][6] 까지 -> 행과 열의 사이즈가 2(dia)차이
        // -> i는 1 ~ 4 , j는 i+2(dia)
        // i = 1 ~ n-dia  , j = i + dia
        for (int i = 1; i <= n - diagonal; i++)
        {
            int j = i + diagonal, k;
            // M[i][j] 의 값 (M[i][j]를 어디서 반 갈라서 곱하는 게 계산이 빠른지)
            // min (M[i][k] + M[k+1][j] + di-1*dk*dj) (k : 최적해)
            M[i][j] = minimum(i, j, k, d, M); //최적값
            P[i][j] = k;                      //최적해
            // (Ai*...*Ak)(Ak+1*...*Aj)
        }
}

void order(int i, int j, matrix2 &P, string &s)
{
    // s string에 출력할 순서대로 다 넣어두고 마지막에 s 출력하기

    // inorder traversal
    if (i == j) // 곱하는 거 아니고 그냥 혼자 두는 거 ex. (A1)
    {
        s += string("(");
        s += string("A") + to_string(i);
        s += string(")");
    }
    else
    {
        int k = P[i][j];
        s += string("(");
        order(i, k, P, s);
        order(k + 1, j, P, s);
        s += string(")");
    }
}

int main()
{
    // 입력1 - 첫 번째 줄에 행렬의 개수 n이 주어진다.
    int n;
    cin >> n;
    // d는 d0 ~ dn
    matrix1 d(n + 1, 0);                 // 행과 열 크기 저장 ex. A1 = d0*d1, A2=d1*d2
    matrix2 M(n + 1, matrix1(n + 1, 0)); //최적값 저장 ex. M[1][4]=132 -> A1*A2*A3*A4 최적 곱셈 횟수, M[1][1]=0 -> 자기자신만 있으면 곱할 필요 없음
    matrix2 P(n + 1, matrix1(n + 1, 0)); //최적해 저장 ex. P[1][4]=1

    // 입력2 - 두 번째 줄부터 행렬의 크기 값의 배열 d가 주어진다.
    for (int i = 0; i <= n; i++)
        cin >> d[i];

    minmult(n, d, M, P);

    // 출력1 - 먼저 행렬 M의 윗 부분 삼각형을 출력한다. (0을 포함)
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (j == n)
                cout << M[i][j] << endl;
            else
                cout << M[i][j] << " ";
        }
    }

    // 출력2 - 다음으로 행렬 P의 윗 부분 삼각형을 출력한다. (0을 포함)
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (j == n)
                cout << P[i][j] << endl;
            else
                cout << P[i][j] << " ";
        }
    }

    // 출력3 - M과 P를 출력한 후에 최적값을 출력한다.
    cout << M[1][n] << endl;

    // 출력4 - 다음 줄에 행렬 곱셈의 순서를 괄호로 묶어 출력한다.
    string s;
    order(1, n, P, s);
    cout << s << endl;
}