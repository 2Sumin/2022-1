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
}

class GoldFish extends Fish {
	@Override
	void move() {
		System.out.println("move : GoldFish()");
	}
}
public class AnimalTest8 {
	public static void main(String[] args) {
		Fish fish=new GoldFish(); //upcasting
		fish.move(); //실행 시 다형적으로 호출되는 메소드
	}

}
