package main;

public class Arrays {

    public static void main(final String[] array) {
        final String[] array1 = new String[10];
        System.out.println("############ Arrays #############");
        System.out.println("############ Simples #############");
        array1[0] = "teste";
        array1[1] = "teste2";
        array1[2] = "teste4";
        System.out.println(array1[0]);
        System.out.println(array1[1]);
        System.out.println(array1[2]);

        System.out.println("############ Multidimensionais #############");
        final String[][] array2 = new String[10][10];
        array2[0][0] = "teste";
        array2[0][1] = "teste2";
        array2[9][5] = "teste4";
        System.out.println(array2[0][0]);
        System.out.println(array2[0][1]);
        System.out.println(array2[9][5]);
        

        System.out.println("############ Tamanho #############");
        System.out.println(array1[0].length());
        
        System.out.println("############ Referencia #############");
        System.out.println(array1);
    }
}
