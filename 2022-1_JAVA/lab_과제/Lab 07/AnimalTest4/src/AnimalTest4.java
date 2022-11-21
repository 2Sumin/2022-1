//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

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

public class AnimalTest4 {
	public static void main(String[] args) {
		Fish fish = new Fish();
		((GoldFish) fish).move(); // downcasting
		// ClsssCastException
		// 에러 발생 이유 : upcasting을 한 후에 downcasting을 해야하는데
		// fish 객체가 생성될 때 아무런 타입캐스팅이 발생하지 않았다.

	}

}
