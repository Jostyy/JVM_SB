package jvm;

public class Classes {
	public static void main (String arg []){
		TesteStatic testStatic = new TesteStatic();
		Teste test = new Teste();
		
		testStatic.getTeste();
		test.getTeste();
	}
    

    public static class TesteStatic{  
    	
    	public TesteStatic() {
    		
    	}
    	
        public void getTeste(){   
    		System.out.println("This is a Static class");
        }
    }
}

