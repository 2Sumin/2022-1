//2021113772 이수민
//본인은 이 소스파일을 다름 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package Lab_01.n1;

import java.util.Scanner;

public class EmployeeTest02 {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);

		String firstName, lastName;
		double monthlySalary;

		System.out.print("Enter first name: ");
		firstName = input.next();

		System.out.print("Enter last name: ");
		lastName = input.next();
		System.out.print("Enter monthly salary: ");
		monthlySalary = input.nextDouble();
		Employee Employee1 = new Employee(firstName, lastName, monthlySalary);
		
		System.out.println();
		System.out.print("Enter first name: ");
		if (input.hasNextLine())
			input.nextLine();
		firstName = input.nextLine();

		System.out.print("Enter last name: ");
		lastName = input.next();
		System.out.print("Enter monthly salary: ");
		monthlySalary = input.nextDouble();
		Employee Employee2 = new Employee(firstName, lastName, monthlySalary);
		
		System.out.println();
		System.out.print("Employee 1: "+Employee1.getFirstName()+" "+Employee1.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee1.getMonthlySalary()*12);
		System.out.print("Employee 2: "+Employee2.getFirstName()+" "+Employee2.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee2.getMonthlySalary()*12);
		
		System.out.println();
		System.out.println("Increasing employee salaries by 10%");
		System.out.print("Employee 1: "+Employee1.getFirstName()+" "+Employee1.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee1.getMonthlySalary()*1.1*12);
		System.out.print("Employee 2: "+Employee2.getFirstName()+" "+Employee2.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee2.getMonthlySalary()*1.1*12);

	}

}
