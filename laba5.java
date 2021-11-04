import java.util.ArrayList;
import java.util.List;

public class laba5 {
    public static void main(String[] args) {
        List<Integer> result = new ArrayList<>();
        for(int i = 100; i < 201; i++){
            if(ifItSimple(i)){
                result.add(findRoot(i));
            }
        }
        System.out.println(result);

    }

    public static int findRoot(int x){
        int y = 0;
        while(x != 0){
            y += x % 10;
            x /=10;
        }
        if(y % 10 != y){
            y = findRoot(y);
        }
        return y;
    }

    public static boolean ifItSimple(int x){
        for(int i = x-1; i > 1; i--){
            if(x % i == 0){ return  false;}
        }
        return true;
    }
}
