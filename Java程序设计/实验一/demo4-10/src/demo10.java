/*
class Teacher {
    private String name,title,course,resourse,office;
    Teacher() {}
    Teacher(String name, String title, String course, String resourse, String office) {
        this.name = name;
        this.title = title;
        this.course = course;
        this.resourse = resourse;
        this.office = office;
    }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }
    public String getCourse() { return course; }
    public void setCourse(String course) { this.course = course; }
    public String getResourse() { return resourse; }
    public void setResourse(String resourse) { this.resourse = resourse; }
    public String getOffice() { return office; }
    public void setOffice(String office) { this.office = office; }
}
public class demo10 {
    public static void main(String[] args) {
        // 使用有参构造函数创建一个Teacher对象
        Teacher teacher = new Teacher("Tom", "教授", "Java", "人工智能", "致腾楼319");
        // 输出教师信息
        System.out.println("教师姓名: " + teacher.getName());
        System.out.println("教师职称: " + teacher.getTitle());
        System.out.println("教授课程: " + teacher.getCourse());
        System.out.println("研究方向: " + teacher.getResourse());
        System.out.println("办公地点: " + teacher.getOffice());
        System.out.println("----------------------");
        // 使用无参构造函数创建一个Teacher对象
        Teacher teacher2 = new Teacher();
        // 设置教师信息
        teacher2.setName("Jerry");
        teacher2.setTitle("讲师");
        teacher2.setCourse("Python");
        teacher2.setResourse("大数据");
        teacher2.setOffice("致腾楼320");
        // 输出教师信息
        System.out.println("教师姓名: " + teacher2.getName());
        System.out.println("教师职称: " + teacher2.getTitle());
        System.out.println("教授课程: " + teacher2.getCourse());
        System.out.println("研究方向: " + teacher2.getResourse());
        System.out.println("办公地点: " + teacher2.getOffice());
    }
}
*/

class Teacher {
    private String name,title,course,resourse,office;
    Teacher() {}
    Teacher(String name, String title, String course, String resourse, String office) {
        this.name = name;
        this.title = title;
        this.course = course;
        this.resourse = resourse;
        this.office = office;
    }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }
    public String getCourse() { return course; }
    public void setCourse(String course) { this.course = course; }
    public String getResourse() { return resourse; }
    public void setResourse(String resourse) { this.resourse = resourse; }
    public String getOffice() { return office; }
    public void setOffice(String office) { this.office = office; }

    public static void main(String[] args) {
        // 使用有参构造函数创建一个Teacher对象
        Teacher teacher = new Teacher("Tom", "教授", "Java", "人工智能", "致腾楼319");
        // 输出教师信息
        System.out.println("有参构造函数创建的教师对象:");
        System.out.println("教师姓名: " + teacher.getName());
        System.out.println("教师职称: " + teacher.getTitle());
        System.out.println("教授课程: " + teacher.getCourse());
        System.out.println("研究方向: " + teacher.getResourse());
        System.out.println("办公地点: " + teacher.getOffice());
        System.out.println("----------------------");
        // 使用无参构造函数创建一个Teacher对象
        Teacher teacher2 = new Teacher();
        // 设置教师信息
        teacher2.setName("Jerry");
        teacher2.setTitle("讲师");
        teacher2.setCourse("Python");
        teacher2.setResourse("大数据");
        teacher2.setOffice("致腾楼320");
        // 输出教师信息
        System.out.println("无参构造函数创建的教师对象:");
        System.out.println("教师姓名: " + teacher2.getName());
        System.out.println("教师职称: " + teacher2.getTitle());
        System.out.println("教授课程: " + teacher2.getCourse());
        System.out.println("研究方向: " + teacher2.getResourse());
        System.out.println("办公地点: " + teacher2.getOffice());
    }
}



