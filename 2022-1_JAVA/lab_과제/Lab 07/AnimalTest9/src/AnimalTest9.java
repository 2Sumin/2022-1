//2021113772 �̼���
//������ �� �ҽ������� �ٸ� ����� �ҽ��� �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.

class Animal {
	void move() {
		System.out.println("move : Animal()");
	}	
}

class Fish extends Animal {
	@Override
	void move() {
		System.out.println("move : Fish()");
	}
}
class Frog extends Animal {
	@Override
	void move() {
		System.out.println("move : Frog()");
	}
}
class Bird extends Animal {
	@Override
	void move() {
		System.out.println("move : Bird()");
	}
}


public class AnimalTest9 {
	public static void main(String[] args) {
		Animal[] animal=new Animal[3];
		animal[0]=new Fish(); //upcasting from Fish to Animal
		animal[1]=new Frog(); //upcasting from Frog to Animal
		animal[2]=new Bird(); //upcasting from Bird to Animal
		
		for(int i=0;i<animal.length;i++)
			animal[i].move(); //���� �� ���������� ȣ��Ǵ� �޼ҵ�
	}

}
