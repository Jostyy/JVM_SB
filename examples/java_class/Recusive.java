package jvm;

public class Recusive {

	public static void main (String arg []){
		System.out.println(recursiveM(4));
	}

    public static int recursiveM(int num){        
        if(num == 0){
            return 1;
        }

        int newNum = num * recursiveM(num-1);
        return newNum;
    }
}

