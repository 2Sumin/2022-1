//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

package q;

//(4) public class�� private member��
//�ٸ� package�� �ٸ� class���� ������ �� ����


import p.B;

class A {
	void f() {
		B b = new B();
		b.n = 3;
		b.g();
	}

}
