package main;

public class StaticClass {

	public static void main(final String[] args) {
		System.out.println("############ Classes #############");
		System.out.println("This is a " + StaticClass.obj);

		System.out.println("############ Metodos #############");
		StaticClass.getTesteStatic();
	}

	public static String obj = "Field in static class";


	public static void getTesteStatic() {
		System.out.println("This is a Static Method");
	}
	
}
