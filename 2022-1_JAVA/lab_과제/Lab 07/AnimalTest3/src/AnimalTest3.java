//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

class Animal {
	void show() {
		System.out.println("show : Animal()");
	}
}

class Fish extends Animal {
	void draw() {
		System.out.println("draw : Fish()");
	}
}

class GoldFish extends Fish {
	void move() {
		System.out.println("move : GoldFish()");
	}
}

public class AnimalTest3 {
	public static void main(String[] args) {
		Fish fish=new Fish();
		fish.move();
		// ���� �߻� ���� : Fish ��ü���� move �޼ҵ尡 ���� �����̴�.
	}

}
