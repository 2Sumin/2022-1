//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
class Animal {
	void show() {
		System.out.println("show : Animal()");
	}

	void move() {
		System.out.println("move : Animal()");
	}

}

class Fish extends Animal {
	void draw() {
		System.out.println("draw : Fish()");
	}

}

public class AnimalTest1 {
	public static void main(String[] args) {
		Fish fish = new Fish();
		fish.move();
	}

}
