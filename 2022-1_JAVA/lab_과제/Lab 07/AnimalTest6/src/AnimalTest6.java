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

public class AnimalTest6 {
	public static void main(String[] args) {
		Fish fish=new GoldFish(); //upcasting
		
		if (fish instanceof GoldFish)
			((GoldFish)fish).move(); //downcasting
	}

}
