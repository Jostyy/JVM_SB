package main;

public class StaticClass {

	public static void main(final String[] args) {
		System.out.println("############ Classes #############");
		privStaticClass.getTeste();

		System.out.println("############ Metodos #############");
		privStaticClass.getTesteStatic();
	}

	public static class privStaticClass {
		public static void getTesteStatic() {
			System.out.println("This is a Static Method");
		}

		public static void getTeste() {
			System.out.println("This is a Static class");
		}
	}
	
}
