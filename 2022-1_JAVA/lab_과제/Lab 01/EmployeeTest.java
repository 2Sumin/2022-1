//2021113772 이수민
//본인은 이 소스파일을 다름 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package Lab_01.n1;

public class EmployeeTest {
	
	public static void main(String[] args) {
		Employee Employee1 = new Employee("Bob","Jones",34500.00);
		Employee Employee2 = new Employee("Susan","Baker",37809.00);
		
		
		System.out.print("Employee 1: "+Employee1.getFirstName()+" "+Employee1.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee1.getMonthlySalary());
		System.out.print("Employee 2: "+Employee2.getFirstName()+" "+Employee2.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee2.getMonthlySalary());
		
		System.out.println();
		System.out.println("Increasing employee salaries by 10%");
		System.out.print("Employee 1: "+Employee1.getFirstName()+" "+Employee1.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee1.getMonthlySalary()*1.1);
		System.out.print("Employee 2: "+Employee2.getFirstName()+" "+Employee2.getLastName()+"; ");
		System.out.println("Yearly Salary: "+Employee2.getMonthlySalary()*1.1);
	}

}
