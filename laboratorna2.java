import java.util.InputMismatchException;
import java.util.Scanner;

public class laboratorna2 {
    public static void main(String[] args) {
        try {


            Scanner in = new Scanner(System.in);
            System.out.println("Введіть перше число");
            int a = in.nextInt();
            System.out.println("Введіть друге число");
            int b = in.nextInt();
            System.out.println("Введіть третє число");
            int c = in.nextInt();
            System.out.print("Наявність парної суми : ");
            System.out.println(parneChiNe(a, b, c));

        }catch (InputMismatchException e){
            System.out.println("Данні введено невірно : " + e.toString());
        }
    }
    public static boolean parneChiNe(int a, int b, int c){
        if((a + b) % 2 == 0 ){ return true; }
        if((a + c) % 2 == 0){ return true; }
        if ((b + c) % 2 == 0){ return true; }
        return false;
    }
}
