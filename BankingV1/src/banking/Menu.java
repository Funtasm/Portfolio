package banking;

public class Menu {
	protected String[] options;
	protected int choice;
	public Menu(String ...strings){
		options = strings;
	}
	
	public Menu(Menu menu, String ...strings){
		
		int length = menu.getOptions().length + strings.length;
		int i;
		String[] moreOptions = new String[length];
		
		for(i=0; i<menu.getOptions().length; i++){
			moreOptions[i] = menu.getOptions()[i];
		}
		i++;
		
		for(int j=0; j<strings.length; j++, i++){
			moreOptions[i] = strings[j];
		}
		options = moreOptions;
	}
	
	public void display(){
		for(int i=0; i<options.length; i++){
			System.out.println((i+1) + ": " + options[i]);
		}
	}
	
	public String[] getOptions(){
		return options;
	}	
	
	public void askFor(String prompt){

		System.out.println(prompt);
		this.display();
		return;
	}
}