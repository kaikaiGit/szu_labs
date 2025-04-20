public class Test {
    public static void main(String[] args) {
        // 使用matches方法检查字符串是否以"ABC "开头
        System.out.println("Hi, ABC, good".matches("ABC "));
        // 使用matches方法检查字符串是否包含"ABC"
        System.out.println("Hi, ABC, good".matches(".*ABC.*"));
        // 使用replaceAll方法将字符串中的逗号和分号替换为"#"
        System.out.println("A,B;C".replaceAll(",;","#" ));
        // 使用replaceAll方法将字符串中的逗号和分号替换为"#"
        System.out.println("A,B;C".replaceAll("[,;]","#"));

        // 使用split方法将字符串按照逗号和分号分割为数组
        String[] tokens = "A,B;C".split("[,;]");
        // 遍历分割得到的数组并输出
        for (int i = 0; i < tokens.length; i++)
            System.out.print(tokens[i] + " ");
    }
}
