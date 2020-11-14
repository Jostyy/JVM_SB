package main;

public class Recursive {

	public static void main(final String[] args) {
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

