public class Main {
    static {
        /*
        Looks for file "${java.library.path}/libexample_java.so".
        `example` class is loaded from that file.
        */
        System.loadLibrary("example_java");
    }
    public static void main(String argv[]) {
        System.out.println(example.fact(4));
    }
}
