import java.util.Random;

class Locker {

    private String key;
    private int length = 8;

    public Locker() {
        key = generateKey();
    }

    private String generateKey() {
        Random random = new Random();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length; i++) {
            sb.append(random.nextInt(10));
        }
        return sb.toString();
    }

    public String getKey() {
        return key;
    }

}