package banking;

public class Account {
	protected String accountNum;
	protected String ssn;
	protected double balance;
	protected String pin;
	protected double lastDeposit;
	public Account(String accountNum, String pin2,  String ssn2, double balance){
		this.accountNum = accountNum;
		this.pin = pin2;
		this.ssn = ssn2;
		this.balance = balance;
		lastDeposit = balance;
	}
	
	public boolean validatePin(String pin){
		return (pin.equals(this.pin));
	} 
	
	public void withdraw(double amount) throws InsufficientFunds{
		if(amount < 0 || amount > balance){
			throw new InsufficientFunds();
		}
		balance-= amount;
		System.out.println("You withdrew $" + amount+".");
	}
	
	public void deposit(double amount){
		if(amount > 0){
			balance += amount;
			lastDeposit = amount;
		}
	}
	
	public void transfer(Account dest, double amount) throws InsufficientFunds{
		this.withdraw(amount);
		dest.deposit(amount);
	}
	
	public String getAccountNum() {
		return accountNum;
	}

	public void setAccountNum(String accountNum) {
		this.accountNum = accountNum;
	}

	public double viewBalance(){
		return balance;
	}
	
	public double getLastDeposit(){
		return lastDeposit;
	}
}

class InsufficientFunds extends Exception{
	
}