package banking;

public class CheckingAccount extends Account {
	
	double lastDeposit;

	public CheckingAccount(String accountNum, String pin,  String ssn, double balance) {
		super(accountNum, pin, ssn, balance);
		lastDeposit = balance;
	}
}