package banking;

import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

public class BankStaff {

	public BankStaff() {

	}

	public void openAccount(String pin, String ssn, int accType, ArrayList<Account> accounts) throws InvalidCredintials {

		if(!(pin.length() == 4) || !(ssn.length() == 9)) {
			throw new InvalidCredintials();
		}
		int randomAccountHolder = (ThreadLocalRandom.current().nextInt(10000, 99999 + 1));
		String randomAccount = Integer.toString(randomAccountHolder);
		
		
		switch(accType) {
			 case 1: 
				 accounts.add(new CheckingAccount(randomAccount,pin,ssn,0));
				 System.out.println("Your Checking account number is: " + randomAccount);
				 break;	 
			 case 2: 
				 accounts.add(new SavingsAccount(randomAccount, pin, ssn, 0));
				 System.out.println("Your Savings account number is: " + randomAccount);
				 break;
		}
	}
	
	public void closeAccount(ArrayList<Account> accounts) throws AccountNotFound, InsufficientFunds {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the Account number you want to close");
		String closeAccNum = sc.next();
		Account closeACC = Main.findAccount(accounts,closeAccNum);
		closeACC.withdraw(closeACC.viewBalance());
		accounts.remove(closeACC);
		System.out.println("Account " + closeAccNum + " has been emptied and closed have a good day");
		
	}

	public boolean validatePin(String pin , Account acc){
		return acc.validatePin(pin);
	} 
}
class InvalidCredintials extends Exception{

}