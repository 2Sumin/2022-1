//2021113772 이수민
//본인은 이 소스파일을 다름 사람의 소스를 복사하지 않고 직접 작성하였습니다.

package Lab_01.n1;

public class Employee {
	private String firstName, lastName;
	private double monthlySalary;
	
	

	public Employee(String firstName, String lastName, double monthlySalary) {
		super();
		this.firstName = firstName;
		this.lastName = lastName;
		this.monthlySalary = monthlySalary;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public double getMonthlySalary() {
		return monthlySalary;
	}

	public void setMonthlySalary(double monthlySalary) {
		if (monthlySalary > 0)
			this.monthlySalary = monthlySalary;
	}

}
