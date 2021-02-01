package banking;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import banking.BankStaff;
import banking.InvalidCredintials;

public class Main {
		
	public static void main(String[] args) throws InsufficientFunds, AccountNotFound {

		Menu prompts = new Menu("Deposit", "Withdrawal", "Transfer", "View Balance", "View last deposit amount", "Close Account", "Cancel Transaction");
	    Scanner sc = new Scanner(System.in);
		ArrayList<Account> accounts = new ArrayList<Account>();
		BankStaff staffMember = new BankStaff();

		accounts.add(new CheckingAccount("00001", "5678", "123456789", 300));
		accounts.add(new CheckingAccount("00002", "4567", "234567890", 4000 ));
		accounts.add(new CheckingAccount("00003", "3456", "345678901", 70 ));
		accounts.add(new CheckingAccount("00004", "2345", "456789012", 5000));
		accounts.add(new SavingsAccount("10001", "1234", "567890123", 700));
		accounts.add(new SavingsAccount("10002", "0123", "234567890", 2000 ));
		accounts.add(new SavingsAccount("10003", "6789", "789012345", 9000 ));
		accounts.add(new SavingsAccount("10004", "7890", "890123456", 1000 ));
				
		boolean done = false;
		int choice;
		boolean pincreateflag = false;
		boolean snnCreateFlag = false;
		Account acc;

		System.out.println("If you want to open an account, please enter (1). If you want to access an existing account,  enter (0).");
		try {
			int oldOrNew = sc.nextInt();
			String pin = null;
			if(oldOrNew == 1) {
				System.out.println("Enter the desired four-digit Pin: ");
				while(!pincreateflag) {
				pin = sc.next();
				if (!RealPinChecker(pin)) {
					System.out.println("Please only input numbers for your four-digit Pin.");
					
				}
				else {
					pincreateflag =true;
				}
				}

				System.out.println("Enter Social Security Number: ");
				String ssn = null;
				while(!snnCreateFlag) {
					ssn = sc.next();
					if (!RealSnnChecker(ssn)) {
						System.out.println("Please only input numbers for your nine-digit SSN.");
						
					}
					else {
						snnCreateFlag =true;
					}
					}
				
				System.out.println("Checking(1) or Savings(2) Account:");
				int accType = sc.nextInt();

				try {
					staffMember.openAccount(pin, ssn , accType, accounts);
				}catch (InvalidCredintials e) {
					System.out.println("Please check that your credentials are correct.");
					System.exit(1);
				}
			}

			System.out.println("Enter Your Account Number:");
			String accountNum = sc.next();
			acc = findAccount(accounts, accountNum);
			
			if(validatePin(acc,staffMember)){
				do {
					prompts.askFor("\n------------Main Menu------------");
					choice = sc.nextInt();

					switch (choice) {
					case 1:
						System.out.println("How much would you like to deposit?");
						acc.deposit(sc.nextDouble());
						break;

					case 2:
						System.out.println("How much would you like to withdraw?");

						try {
							acc.withdraw(sc.nextDouble());
						} catch (InsufficientFunds e) {
							System.out.println("I'm sorry, you do not have enough funds.");
						}finally{
							break;}

					case 3:
						System.out.println("Enter account number:");
						Account acc2;
						try {
							acc2 = findAccount(accounts, sc.next());
						} catch (AccountNotFound e1) {
							System.out.println("Account not found.");
							break;
						}
						System.out.println("Enter the amount you would like to transfer to this account:");
						try {
							acc.transfer(acc2, sc.nextDouble());
						} catch (InsufficientFunds e) {
							System.out.println("I'm sorry, you do not have enough funds.");
						}finally{
							break;}

					case 4:
						System.out.println("Balance: $" + acc.viewBalance() +".");
						break;

					case 5:
						System.out.println("Last Deposit: $" + acc.getLastDeposit() + ".");
						break;

					case 6:
				        staffMember.closeAccount(accounts);
				        break;

				    case 7:
				        done = true;
					}

				} while (!done);
			}else done = true;
		} catch (AccountNotFound e2) {
			System.out.println("Account not found.");
		}
	}

	public static boolean validatePin(Account acc, BankStaff staffMember){
		Scanner sc = new Scanner(System.in);
		int attempts = 0;

		while(attempts < 3){
			System.out.println("Enter Pin:");
			if(staffMember.validatePin(sc.next(), acc)){
				//sc.close();
				return true;
			} else attempts++;
		}

		System.out.println("I'm sorry, you've entered the wrong pin too many times.\nThe transaction has been canceled.");
		return false;
	}
	public static boolean RealPinChecker(String pingiven) {
		int Placeholder;
		Scanner TestPin = new Scanner(pingiven);
		if(TestPin.hasNextInt()) {
			Placeholder=TestPin.nextInt();
		}
		else
			return false;
		if(TestPin.hasNext()) {
			return false;
		}
		else if(!(pingiven.length() ==4))
			return false;
		return true;
		
	}
	
	public static boolean RealSnnChecker(String snnGiven) {
		int Placeholder;
		Scanner testSnn = new Scanner(snnGiven);
		if(testSnn.hasNextInt()) {
			Placeholder=testSnn.nextInt();
		}
		else
			return false;
		if(testSnn.hasNext()) {
			return false;
		}
		else if(!(snnGiven.length() == 9))
			return false;
		return true;
		
	}
	
	


	public static Account findAccount(ArrayList<Account> acc, String num) throws AccountNotFound{
		System.out.println(num);
		for(int i = 0; i < acc.size(); i++) {
			if(acc.get(i).getAccountNum().equals(num)) {
				return acc.get(i);
			}
		}

		throw new AccountNotFound();
	}
}

class AccountNotFound extends Exception{

}