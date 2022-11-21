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

	@Override
	void show() {
		System.out.println("show : Fish()");
	}

	@Override
	void move() {
		System.out.println("move : Fish()");
	}

}

class GoldFish extends Fish {

	@Override
	void draw() {
		System.out.println("draw : GoldFish()");
	}

	@Override
	void move() {
		System.out.println("move : GoldFish()");
	}

}

public class AnimalTest10 {
	public static void main(String[] args) {
		// case 1.
		GoldFish goldFish = new GoldFish();
		goldFish.show();

		// case 2.
		Animal animal = new Fish();
		animal.draw(); // error
		// ���� �߻� ���� : Fish ��ü�� Animal ��ü���������� animal�� upcasting �����ϱ� ���� ���·δ� Animal ��ü ���� �޼ҵ常 ��� �����ϴ�
		// Fish ��ü ���� �޼ҵ��� draw�� ����Ϸ��� animal�� Fish�� downcasting �� ����ؾ� �Ѵ�.
//		((Fish) animal).draw();
		
		// case 3.
		Animal animal2 = new Fish();
		animal2.show(); //���� �� ���������� ȣ��Ǵ� �޼ҵ�
		animal2.move(); //���� �� ���������� ȣ��Ǵ� �޼ҵ�

		// case 4.
		Animal animal3 = new GoldFish();
		((Fish) animal3).draw(); //���� �� ���������� ȣ��Ǵ� �޼ҵ�
	}

}
