package main;

class multi
{
    public static void main(final String[] array) {
        final String[][] array2 = new String[10][10];
        array2[0][0] = "teste";
        array2[0][1] = "teste2";
        array2[9][5] = "teste4";
        System.out.println(array2[0][0]);
        System.out.println(array2[0][1]);
        System.out.println(array2[9][5]);
    }
}