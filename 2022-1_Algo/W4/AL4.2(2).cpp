#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> LargeInteger;

int threshold, cnt = 0;

void roundup_carry(LargeInteger &v)
{
    //자릿수끼리 더했는데 10 넘어서 올려줘야하는 거 있을 때 처리하는 함수 (올림수 처리)
    int carry = 0;
    for (int i = 0; i < v.size(); i++)
    {
        v[i] += carry;
        //올림수 처리
        carry = v[i] / 10;
        //나머지
        v[i] = v[i] % 10;
    }
    //다른 자릿수 생기면
    if (carry != 0)
        v.push_back(carry);
}

void ladd(LargeInteger a, LargeInteger b, LargeInteger &c)
{
    // c의 크기는 둘 중 더 자릿수가 많은 것
    c.resize(max(a.size(), b.size()));
    // c를 0으로 자릿수 초기화
    fill(c.begin(), c.end(), 0);

    //일의 자릿수부터 계산
    for (int i = 0; i < c.size(); i++)
    {
        if (i < a.size())
            c[i] += a[i];
        if (i < b.size())
            c[i] += b[i];
    }
    //뒤에 carry 발생하면 append (c의 자릿수 많아짐)
    roundup_carry(c);
}

void lmult(LargeInteger a, LargeInteger b, LargeInteger &c)
{
    //전통적인 방법의 곱셈
    // 1. 일반적으로 크기는 두 개 배열 사이즈 더해서 1뺌(겹치는 거 한자리 있음)
    c.resize(a.size() + b.size() - 1);
    fill(c.begin(), c.end(), 0);
    // 곱셈 실제로 세로연산으로 적어서 해보면
    // a[0]*b[0]=c[0]
    // a[1]*b[0] + a[0]*b[1] = c[1]
    // a[2]*b[0] + a[1]*b[1] + a[0]*b[2] = c[2]  -> 겹치는 한자리
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    }
    roundup_carry(c);
}

void pow_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    // u=567832, m=3
    // u*10^m = 567832 000

    if (u.size() == 0)
        v.resize(0);
    else
    {
        // 1. m 크기만큼 숫자 자릿수가 늘어나니까 resize
        v.resize(u.size() + m);
        // 2. 0으로 초기화
        fill(v.begin(), v.end(), 0);
        // 3. 뒤에는 0이어야 하니까 v.begin()~v.begin().m-1까지 m개는 0으로 그대로 두고
        // 그 뒤에 v.begin() 부터 원래 숫자 (u) 채우기
        copy(u.begin(), u.end(), v.begin() + m);
    }
}

void remove_leading_zeros(LargeInteger &v)
{
    while (v.size() != 0 && v.back() == 0)
        v.pop_back();
}

void div_by_exp(LargeInteger &u, int m, LargeInteger &v)
{
    // u=567832, m=3
    // u divide 10^m = 567 (뒤에 832 삭제) -> v=567
    // u.size()가 m보다 작으면 그냥 지워버려야 함
    // (m개만큼 지워야하는데 u.size()가 m보다 작으면 다 지워지니까)

    /*if (u.size() == 0)
        v.resize(0);
    else
    {
        // 1. 크기가 ceil(n/2)이니까 m(2/n)이랑 u.size() 중에 더 큰 걸로
        int k = m > u.size() ? m : u.size();
        v.resize(k);
        // 2. 몫이니까 뒤에꺼 삭제해야함
        //   입력했을 때 배열에 숫자를 반대로 집어넣어서 일의자리 숫자의 인덱스가 0부터 시작하니까
        //  나머지에서 가져간 인덱스 다음부터 복사
        copy(u.begin() + m, u.end(), v.begin());
        remove_leading_zeros(v);
    }*/
    if (u.size() <= m)
        v.resize(0);
    else
    {
        v.resize(u.size() - m);
        copy(u.begin() + m, u.end(), v.begin());
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    // u=567832, m=3
    // u rem 10^m = 832 (앞에 567 삭제) -> v=832

    if (u.size() == 0)
        v.resize(0);
    else
    {
        // 1. 크기가 floor(n/2)이니까 m(n/2)이랑 u.size() 중에 더 작은 걸로
        int k = m < u.size() ? m : u.size();
        // v.resize(k);
        v.resize(m < u.size() ? m : u.size());
        // 2. 나머지니까 앞에꺼 삭제해야함
        //  입력했을 때 배열에 숫자를 반대로 집어넣어서 일의자리 숫자의 인덱스가 0부터 시작하니까
        //  u에서 인덱스 0인것부터 k만큼 만 복사해서 가져오기
        copy(u.begin(), u.begin() + k, v.begin());
        remove_leading_zeros(v);
    }
}

void prod(LargeInteger u, LargeInteger v, LargeInteger &r)
{
    cnt++;
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    // n = v와 u 중 더 큰 자릿수
    int n = max(u.size(), v.size());
    // 0*뭐면 0되니까
    if (u.size() == 0 || v.size() == 0)
        r.resize(0);
    //더이상 분할정복 안 하고 그냥 곱하기
    else if (n <= threshold)
        lmult(u, v, r);

    else
    {
        // u = x * 10^m + y
        // v = w * 10^m + z

        // 1. divide
        int m = n / 2;
        div_by_exp(u, m, x); // u 몫
        rem_by_exp(u, m, y); // u 나머지
        div_by_exp(v, m, w);
        rem_by_exp(v, m, z);

        // 2. conquer
        // uv = (x * 10^m + y)*(w * 10^m + z)
        // xw * 10^2m + (xz + wy) * 10^m + yz

        // t2 = prod(x,w) * 10^(2*m)
        // t2 = t1 * 10^(2*m)
        prod(x, w, t1);
        pow_by_exp(t1, 2 * m, t2);
        // t6 = (prod(x,z)+prod(w,y)) * 10^m
        // t6 = ( t3 + t4 ) * 10^m
        // t6 =      t5     * 10^m
        prod(x, z, t3);
        prod(w, y, t4);
        ladd(t3, t4, t5);
        pow_by_exp(t5, m, t6);
        // r = ( t2 + t6 ) + prod(y,z)
        // r =     t8      +    t7
        prod(y, z, t7);
        ladd(t2, t6, t8);
        ladd(t8, t7, r);
    }
}

int main(void)
{
    int x;
    // 입력1) 첫 번째 줄에 threshold의 값이 주어진다.
    cin >> threshold;

    // 입력2) 두 번째 줄에 정수 A가 주어진다.
    LargeInteger A, B;
    string strA, strB;
    cin >> strA;
    cin >> strB;

    //뒤에서부터 숫자 저장함
    // ex. 5310 저장하려면
    // 3 2 1 0
    // 5 3 1 0
    // 5가 가장 나중에 저장됨
    for (int i = strA.size() - 1; i >= 0; i--)
    {
        x = strA[i] - '0';
        A.push_back(x);
    }

    for (int i = strB.size() - 1; i >= 0; i--)
    {
        x = strB[i] - '0';
        B.push_back(x);
    }

    LargeInteger C;
    prod(A, B, C);

    cout << cnt << endl;

    for (int i = C.size() - 1; i >= 0; i--)
        cout << C[i];
    cout << endl;
}