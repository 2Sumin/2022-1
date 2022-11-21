package Lab03;

//2021113772 이수민

//본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

public class Lab03_01 {
	private static int num1;
	private int num2;

	public static void show1() { //static 메소드에서는 static 메소드나 변수만 사용 가능
		System.out.println(num1);   //(1) O - num1이 static 변수이므로 static 메소드인 show1 안에서 사용 가능하다
		System.out.println(num2);   //(2) X - num2는 static 변수가 아니므로 static 메소드인 show1 안에서 사용 불가능하다
		show4(); 					//(3) O - show4는 static 메소드이므로 static 메소드인 show1 안에서 사용 가능하다
		show5(); 					//(4) X - show5는 static 메소드가 아니므로 static 메소드인 show1 안에서 사용 불가능하다
	}

	public void show2() { //non-static 메소드에서는 같은 클래스 내의 아무 메소드나 변수 사용 가능
		System.out.println(num1);   //(5) O - show2가 static 메소드가 아니므로 static 변수인 num1이 사용 가능하다.
		System.out.println(num2);   //(6) O - show2가 static 메소드가 아니므로 static 변수가 아닌 num2가 사용 가능하다.
		show4(); 					//(7) O - show2가 static 메소드가 아니므로 static 메소드인 show4가 사용 가능하다.
		show5(); 					//(8) O - show2가 static 메소드가 아니므로 static 메소드가 아닌 show5가 사용 가능하다.
	}

	public static void show4() {
	}

	public void show5() {
	}
	
}
