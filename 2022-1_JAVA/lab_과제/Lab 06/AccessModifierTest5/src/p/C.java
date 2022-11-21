//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package p;

//(5) default class의 public member에
//같은 package의 다른 class에서 접근할 수 있다.


class C {
	public void k() {
		B b = new B();
		b.n = 7;
		b.g();
	}

}
