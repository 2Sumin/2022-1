//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

package q;

//(2) public class�� protected member��
//�ٸ� package�� �ٸ� class���� ������ �� ����


import p.B;

class A {
	void f() {
		B b = new B();
		b.n = 3;
		b.g();
	}

}
