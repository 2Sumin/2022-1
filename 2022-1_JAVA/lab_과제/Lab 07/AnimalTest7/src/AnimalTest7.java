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
	void move() {
		System.out.println("move : Fish()");
	}
}

class GoldFish extends Fish {
	@Override
	void move() {
		System.out.println("move : GoldFish()");
	}
}
public class AnimalTest7 {
	public static void main(String[] args) {
		Fish fish=new GoldFish(); //upcasting
		fish.move(); //���� �� ���������� ȣ��Ǵ� �޼ҵ�
	}

}
