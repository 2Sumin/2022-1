//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package q;

//(7) default class의 default member에
//다른 package의 다른 class에서 접근할 수 없다


import p.B;

class A {
	void f() {
		B b = new B();
		b.n = 3;
		b.g();
	}

}
