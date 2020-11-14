package main;

public class Fields {
	private String t;
	public String t2;
	protected String t3;
	public static final String T4 = "Final Field";
	
	public static void main(final String[] args) {
		Fields field = new Fields();
		field.setT("Private Field");
		field.t2 = "Public Field";
		field.t3 = "Protected Field";
		
		
		System.out.println(field.getT());		
		System.out.println(field.t2);		
		System.out.println(field.t3);		
		System.out.println(T4);
	}

	public String getT() {
		return t;
	}

	public void setT(String t) {
		this.t = t;
	}
    
}

