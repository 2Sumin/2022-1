//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package p;

//(8) default class의 private member에
//같은 package의 subclass에서 접근할 수 없다


class E extends B {
	void f() {
		n = 3;
		g();
	}

}
