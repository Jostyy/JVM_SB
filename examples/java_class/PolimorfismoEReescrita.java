package jvm;

public class PolimorfismoEReescrita {

	public static void main (String arg []){
		polymorph(4);
		polymorph(4.0);
		polymorph("String");
		polymorph(true);
	}

    public static void polymorph(int obj){   
		System.out.println("Is a int: " + obj);
    }
    

    public static void polymorph(boolean obj){   
		System.out.println("Is a boolean: " + obj);
    }

    public static void polymorph(String obj){   
		System.out.println("Is a string: " + obj);
    }

    public static void polymorph(Double obj){   
		System.out.println("Is a float: " + obj);
    }
    
}

