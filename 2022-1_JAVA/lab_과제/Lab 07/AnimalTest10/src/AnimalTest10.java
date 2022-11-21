//2021113772 이수민
//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

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
		// 에러 발생 이유 : Fish 객체를 Animal 객체참조변수인 animal에 upcasting 했으니까 현재 상태로는 Animal 객체 안의 메소드만 사용 가능하다
		// Fish 객체 내의 메소드인 draw를 사용하려면 animal을 Fish로 downcasting 후 사용해야 한다.
//		((Fish) animal).draw();
		
		// case 3.
		Animal animal2 = new Fish();
		animal2.show(); //실행 시 다형적으로 호출되는 메소드
		animal2.move(); //실행 시 다형적으로 호출되는 메소드

		// case 4.
		Animal animal3 = new GoldFish();
		((Fish) animal3).draw(); //실행 시 다형적으로 호출되는 메소드
	}

}
