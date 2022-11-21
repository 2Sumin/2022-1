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

public class AnimalTest3 {
	public static void main(String[] args) {
		Fish fish=new Fish();
		fish.move();
		// 에러 발생 이유 : Fish 객체에는 move 메소드가 없기 때문이다.
	}

}
