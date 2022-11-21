#include <iostream>
#include <vector>
#include <string>

//최장공통부분서열 문제 (LCS, Longest Common Subsequence)
/*
sample input
ABCBDAB
BDCABA
sample output
4
BCBA
input2
AAAA
BBB
output
0
*/

/*
문자열 X,Y가 주어졌을 때 두개에서 공통으로 나타나는 부분 문자서열의 길이가 최대가 되도록 부분 문자서열을 찾기
X=[x1,x2,...,xm-1,xm]
Y=[y1,y2,...,yn-1,yn]
Z=[z1,z2,...,zk-1,zk]

[문제 풀이 알고리즘]
if (xm==yn) { //X,Y의 가장 끝의 문자가 같다면
    zk=xm=yn //공통부분문자서열의 가장 끝 문자가 X,Y의 가장 끝 문자와 같고
    zk-1=LCS(Xm-1,Yn-1) //그 다음 부분 문자서열은 X,Y,Z에서 가장 끝 문자서열을 제외하고 그 앞에서부터 구하는 것과 같아진다
}
else if (xm!=yn) {
    if (zk!=xm) //Z의 가장 마지막 문자가 X의 가장 마지막 문자와 같지 않다면
        Z=LCS(Xm-1,Yn) //X의 가장 마지막 문자가 Y와 공통부분문자가 아니라는 말이니까
                       //X의 가장 마지막 문자 바로 앞까지의 문자열과 Y의 문자열 전체를 비교해서 LCS를 구해준다
    if (zk!=yn)
        Z=LCS(Xm,Yn-1)
}

[재귀적으로 정의하기]
1) c[i][j] : 수열 Xi와 Yj의 최장공통부분서열(LCS)의 길이
2) 재귀식:
    종료조건 : i=0 or j=0 이면 c[i][j]=0
        //X와 Y의 문자열 가장 끝문자부터 비교하다가 같은 게 없어서
        //가장 앞 인덱스를 지나 문자열의 시작 부분 (인덱스는 1부터 시작하니까 0인덱스는 문자열이 아님)에 도착했다면
        //이제 더 이상 비교할 문자가 없다는 말이니까 공통부분서열의 길이는 0

    재귀조건 :
        xi==yj 이면 c[i][j] = c[i-1][j-1] + 1 // 현재 시점에서 비교 중인 X의 가장 마지막 문자인 xi 와 Y의 가장 마지막 문자인 yj가 같다면
                                              //xi == yj 가 공통부분문자서열에 추가돼야하니까 +1을 해주고,
                                              //그 앞 문자열까지 다시 비교 (c[i-1][j-1])
        xi!=yj 이면 c[i][j] = max{c[i][j-1],c[i-1][j]} //현재 시점에서 비교 중인 X의 가장 마지막 문자인 xi 와 Y의 가장 마지막 문자인 yj가 같지 않다면
                                            //X의 가장 마지막 문자 xi나 Y의 가장 마지막 문자 yj 둘 중 하나는 공통부분문자서열에 무조건 포함되지 않는다는거니까
                                            //xi가 포함되지 않는다고 가정하면(zk!=xi) c[i-1][j]이 재귀 조건이 될 것이고,
                                            //yj가 포함되지 않는다고 가정하면(zk!=yj) c[i][j-1]이 재귀 조건이 될 것이다.

*/

using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

void lcs(string X, string Y, matrix2 &b, matrix2 &c)
{
    int m = X.size();
    int n = Y.size();

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            //가장 첫번째 배열부터 채워나감 (첫번째 문자부터 비교)
            if (X[i] == Y[j])
            // 현재 시점에서 비교 중인 X의 가장 마지막 문자인 xi 와 Y의 가장 마지막 문자인 yj가 같다면
            // xi == yj 가 공통부분문자서열에 추가돼야하니까 +1을 해주고,
            //그 앞 문자열까지 다시 비교 (c[i-1][j-1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                // c 배열이 세 군데서 오는데 현재 위치를 c[i][j]라 했을 때,
                // 왼쪽위 대각선은 c[i-1][j-1], 바로 왼쪽은 c[i][j-1], 바로 위는 c[i-1][j]
                // 이걸 이용해서 대각선 : 1, 왼쪽 :  2, 위 : 3으로 b배열에 저장해두고 나중에 이용해서 공통으로 나타난 문자열 구하기
                b[i][j] = 1;
            }
            else
            {
                //현재 시점에서 비교 중인 X의 가장 마지막 문자인 xi 와 Y의 가장 마지막 문자인 yj가 같지 않다면
                // X의 가장 마지막 문자 xi나 Y의 가장 마지막 문자 yj 둘 중 하나는 공통부분문자서열에 무조건 포함되지 않는다는거니까
                // xi가 포함되지 않는다고 가정하면(zk!=xi) c[i-1][j]이 재귀 조건이 될 것이고,
                // yj가 포함되지 않는다고 가정하면(zk!=yj) c[i][j-1]이 재귀 조건이 될 것이다.
                c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                if (c[i][j - 1] > c[i - 1][j]) // c[i][j-1]이 더 크면 c[i][j]는 왼쪽에서 온 것
                    b[i][j] = 2;
                else
                    b[i][j] = 3;
            }
        }
    }
}

string get_lcs(int i, int j, matrix2 b, string x)
{
    if (i == 0 || j == 0) //둘 중 하나 0이 될 때까지 역추적
        return "";
    else
    {
        //가장 마지막 인덱스 (c[x.length][y.length]부터 시작해서 타고 올라가기)
        if (b[i][j] == 1) //왼쪽 위 대각선
                          // 1이 되었다는 건 x[i]==y[j] 일 때이니까 x나 y 둘 중 하나에서 바로 그 인덱스의 문자 가져오면 됨
            return get_lcs(i - 1, j - 1, b, x) + x[i];
        //마지막 인덱스부터 타고올라가면서 추적 중이니까 문자열을 발견하면 제일 뒤에 붙여야 함
        //왼쪽이랑 위로 올라가야하는 건 공통 부분 문자는 아니지만 다음에 나올 1을 찾기 위해 타고 가는 과정
        else if (b[i][j] == 2) //왼쪽
            return get_lcs(i, j - 1, b, x);
        else if (b[i][j] == 3) //위
            return get_lcs(i - 1, j, b, x);
    }
}

int main()
{
    string X, Y;

    // 입력1 - 첫 번째 줄에 문자열 X가 주어진다.
    cin >> X;
    X = " " + X; // X문자열의 제일 앞에 인덱스가 0일 때를 추가 -> 문자열은 1부터 문자 시작

    // 입력2 - 두 번째 줄에 문자열 Y가 주어진다.
    cin >> Y;
    Y = " " + Y;

    // 출력1 - 첫 번째 줄에 최장공통부분서열의 길이를 출력한다.
    matrix2 b(X.size(), matrix1(Y.size(), 0)); //공통서열 (최적해)
    matrix2 c(X.size(), matrix1(Y.size(), 0)); //수열 Xi와 Yj의 최장공통부분서열(LCS)의 길이

    lcs(X, Y, b, c);

    cout << c[X.size() - 1][Y.size() - 1] << endl;

    // 출력2 - 두 번째 줄에 위 파이썬 참조 코드에서 사용한 방법대로 적용했을 때의 최장공통부분서열을 출력한다.
    // 단, 공통부분서열이 없으면 두 번째 줄은 출력하지 않는다.
    string str = get_lcs(X.size() - 1, Y.size() - 1, b, X);
    if (str.size() != 0)
        cout << str;
}