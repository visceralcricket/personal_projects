import java.util.Scanner;

public class Src {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        System.out.print("Please introduce a user\n< ");
        String user = scanner.nextLine();

        Locker locker = new Locker();
        System.out.println("Hello, " + user + "! Your generated key is: " + locker.getKey());
    }

}