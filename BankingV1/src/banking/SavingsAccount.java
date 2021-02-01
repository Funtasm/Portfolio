package banking;

public class SavingsAccount extends Account {

	double interest;
	
	public SavingsAccount(String accountNum, String pin,  String ssn, double balance) {
		super(accountNum, pin, ssn, balance);
		this.interest =.05;		
	}
	
	public void addInterest(){
		this.balance*= (1+interest);
	}

}