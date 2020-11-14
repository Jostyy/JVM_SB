package main;

public class NonStaticClass {

	public static void main(final String[] args) {
		NonStaticClass classe = new NonStaticClass();
		System.out.println("############ Classes #############");
		classe.getTeste();

		System.out.println("############ Metodos #############");
		classe.getTesteStatic();
	}

	public  void getTesteStatic() {
		System.out.println("This isn't a Static Method");
	}

	public  void getTeste() {
		System.out.println("This isn't a Static class");
	}

}
