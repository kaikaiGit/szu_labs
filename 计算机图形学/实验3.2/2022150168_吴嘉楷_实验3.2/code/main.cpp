#include "Angel.h"
#include "TriMesh.h"
#include "Camera.h"

#include <vector>
#include <string>

int WIDTH = 600;
int HEIGHT = 600;
int mainWindow;

struct openGLObject
{
	// 顶点数组对象
	GLuint vao;
	// 顶点缓存对象
	GLuint vbo;

	// 着色器程序
	GLuint program;
	// 着色器文件
	std::string vshader;
	std::string fshader;
	// 着色器变量
	GLuint pLocation;
	GLuint cLocation;

	// 投影变换变量
	GLuint modelLocation;
	GLuint viewLocation;
	GLuint projectionLocation;

	// 阴影变量
	GLboolean shadowLocation;
};

// 全局变量光源位置
glm::vec3 light_position = glm::vec3(0.0, 1.5, 1.0);

// 全局变量键盘控制光源移动的参数
float move_step_size = 0.2;

openGLObject tri_object;
openGLObject plane_object;

TriMesh* triangle = new TriMesh();
TriMesh *plane = new TriMesh();
Camera* camera = new Camera();


void bindObjectAndData(TriMesh* mesh, openGLObject& object, const std::string &vshader, const std::string &fshader) {

	// 创建顶点数组对象
    glGenVertexArrays(1, &object.vao);  
	glBindVertexArray(object.vao);  

	// 创建并初始化顶点缓存对象
	glGenBuffers(1, &object.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, object.vbo);
	glBufferData(GL_ARRAY_BUFFER, 
		mesh->getPoints().size() * sizeof(glm::vec3) + mesh->getColors().size() * sizeof(glm::vec3),
		NULL, 
		GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, mesh->getPoints().size() * sizeof(glm::vec3), &mesh->getPoints()[0]);
	glBufferSubData(GL_ARRAY_BUFFER, mesh->getPoints().size() * sizeof(glm::vec3), mesh->getColors().size() * sizeof(glm::vec3), &mesh->getColors()[0]);

	object.vshader = vshader;
	object.fshader = fshader;
	object.program = InitShader(object.vshader.c_str(), object.fshader.c_str());

	// 从顶点着色器中初始化顶点的位置
	object.pLocation = glGetAttribLocation(object.program, "vPosition");
	glEnableVertexAttribArray(object.pLocation);
	glVertexAttribPointer(object.pLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// 从顶点着色器中初始化顶点的颜色
	object.cLocation = glGetAttribLocation(object.program, "vColor");
	glEnableVertexAttribArray(object.cLocation);
	glVertexAttribPointer(object.cLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(mesh->getPoints().size() * sizeof(glm::vec3)));

	// 获得矩阵位置
	object.modelLocation = glGetUniformLocation(object.program, "model");
	object.viewLocation = glGetUniformLocation(object.program, "view");
	object.projectionLocation = glGetUniformLocation(object.program, "projection");

	// 获得阴影标识的位置
	object.shadowLocation = glGetUniformLocation(object.program, "isShadow");
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void init()
{
	std::string vshader, fshader;
	// 读取着色器并使用
	vshader = "shaders/vshader.glsl";
	fshader = "shaders/fshader.glsl";

	// 创建三角形，颜色设置为红色
	triangle->generateTriangle( glm::vec3( 1.0, 0.0, 0.0 ) );
	
	// 设置三角形的位置和旋转
	triangle->setRotation(glm::vec3(90, 0, 0));
	triangle->setTranslation(glm::vec3(0, 0.3, 0));
	triangle->setScale(glm::vec3(0.5, 0.5, 0.5));

	bindObjectAndData(triangle, tri_object, vshader, fshader);

	// 创建正方形平面，设置为黄绿色
	plane->generateSquare(glm::vec3(0.6, 0.8, 0.0));

	// 设置正方形的位置和旋转，注意这里我们将正方形平面下移了一点点距离，
	// 这是为了防止和阴影三角形重叠在同个平面上导致颜色交叉
	plane->setRotation(glm::vec3(90, 0, 0));
	plane->setTranslation(glm::vec3(0, -0.001, 0));
	plane->setScale(glm::vec3(3, 3, 3));

	bindObjectAndData(plane, plane_object, vshader, fshader);

	glClearColor(1.0, 1.0, 1.0, 1.0);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->updateCamera();

	// 计算视图变换矩阵
	camera->viewMatrix = camera->getViewMatrix();
	// 计算相机投影矩阵
	camera->projMatrix = camera->getProjectionMatrix(true);

	// 绘制三角形
    glBindVertexArray(tri_object.vao);
	glUseProgram(tri_object.program);
	// 三角形物体的变换矩阵，注意初始三角形是与Z轴垂直的
	glm::mat4 modelMatrix = triangle->getModelMatrix();

	// 传递投影变换矩阵
	glUniformMatrix4fv(tri_object.modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(tri_object.viewLocation, 1, GL_FALSE, &camera->viewMatrix[0][0]);
	glUniformMatrix4fv(tri_object.projectionLocation, 1, GL_FALSE, &camera->projMatrix[0][0]);
	// 将isShadow设置为1，表示正常绘制的颜色，如果是0则表示阴影
	glUniform1i(tri_object.shadowLocation, 1);
	glDrawArrays(GL_TRIANGLES, 0, triangle->getPoints().size());

	// 绘制三角形阴影
	// @TODO: Task2：根据光源位置，计算阴影投影矩阵
	// 计算阴影的模型变换矩阵。
	glm::mat4 shadowModelMatrix = glm::mat4(0.0f); // 初始化阴影的模型变换矩阵。
	shadowModelMatrix[0][0] = -light_position[1];
	shadowModelMatrix[1][0] = light_position[0];
	shadowModelMatrix[1][2] = light_position[2];
	shadowModelMatrix[2][2] = -light_position[1];
	shadowModelMatrix[1][3] = 1;
	shadowModelMatrix[3][3] = -light_position[1];

	modelMatrix = shadowModelMatrix * modelMatrix; // 更新阴影的模型变换矩阵。
	
	// 传递 isShadow 变量。
	glUniform1i(tri_object.shadowLocation, 0);
	// 传递 unifrom 关键字的矩阵数据。
	glUniformMatrix4fv(tri_object.modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(tri_object.viewLocation, 1, GL_FALSE, &camera->viewMatrix[0][0]);
	glUniformMatrix4fv(tri_object.projectionLocation, 1, GL_FALSE, &camera->projMatrix[0][0]);
	// 绘制
	glDrawArrays(GL_TRIANGLES, 0, triangle->getPoints().size());

	// 绘制平面
    glBindVertexArray(plane_object.vao);
	glUseProgram(plane_object.program);

	modelMatrix = plane->getModelMatrix();

	glUniformMatrix4fv(plane_object.modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(plane_object.viewLocation, 1, GL_FALSE, &camera->viewMatrix[0][0]);
	glUniformMatrix4fv(plane_object.projectionLocation, 1, GL_FALSE, &camera->projMatrix[0][0]);
	// 将isShadow设置为1，表示正常绘制的颜色，如果是0则表示阴影
	glUniform1i(plane_object.shadowLocation, 1);
	glDrawArrays(GL_TRIANGLES, 0, plane->getPoints().size());
}


void printHelp()
{
	std::cout << "Keyboard Usage" << std::endl;
	std::cout <<
		"[Window]" << std::endl <<
		"ESC:		Exit" << std::endl <<
		"h:		Print help message" << std::endl <<
		std::endl <<
		"[Light]" << std::endl <<
		"r:		Reset light parameters" << std::endl <<
		"x/(shift+x):		move the light along X positive/negative axis" << std::endl <<
		"y/(shift+y):		move the light along Y positive/negative axis" << std::endl <<
		"z/(shift+z):		move the light along Z positive/negative axis" << std::endl <<
		"a/(shift+a):		Increase/Decrease move_step_size" << std::endl <<
		std::endl <<
		"[Camera]" << std::endl <<
		"SPACE:		Reset camera parameters" << std::endl <<
		"u/(shift+u):		Increase/Decrease the rotate angle" << std::endl <<
		"i/(shift+i):		Increase/Decrease the up angle" << std::endl <<
		"o/(shift+o):		Increase/Decrease the scale" << std::endl;

}

void mainWindow_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 'ESC键退出'
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if(key == GLFW_KEY_H && action == GLFW_PRESS) 
	{
		printHelp();
	}
	else if(key == GLFW_KEY_R && action == GLFW_PRESS) 
	{
		light_position = glm::vec3(0.0, 1.5, 1.0);
		move_step_size = 0.2;
	}
	else if(key == GLFW_KEY_X && action == GLFW_PRESS && mode == 0x0000) 
	{
		light_position[0] += move_step_size;
	}
	else if(key == GLFW_KEY_X && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		light_position[0] -= move_step_size;
	}
	else if(key == GLFW_KEY_Y && action == GLFW_PRESS && mode == 0x0000) 
	{
		light_position[1] += move_step_size;
	}
	else if(key == GLFW_KEY_Y && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		light_position[1] -= move_step_size;
		if (light_position[1] <= 1.0 ) {
			light_position[1] += move_step_size;
		}
	}
	else if(key == GLFW_KEY_Z && action == GLFW_PRESS && mode == 0x0000) 
	{
		light_position[2] += move_step_size;
	}
	else if(key == GLFW_KEY_Z && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		light_position[2] -= move_step_size;
	}
	else if(key == GLFW_KEY_A && action == GLFW_PRESS && mode == 0x0000) 
	{
		move_step_size += 0.1;
	}
	else if(key == GLFW_KEY_A && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		move_step_size -= 0.1;
	}
	
	else
	{
		camera->keyboard(key,action,mode);
	}
}


void cleanData() {
	triangle->cleanData();
	plane->cleanData();

	delete camera;
	camera = NULL;

	// 释放内存
	delete triangle;
	triangle = NULL;

	delete plane;
	plane = NULL;

	// 删除绑定的对象
	glDeleteVertexArrays(1, &tri_object.vao);
	glDeleteVertexArrays(1, &plane_object.vao);

	glDeleteBuffers(1, &tri_object.vbo);
	glDeleteProgram(tri_object.program);

	glDeleteBuffers(1, &plane_object.vbo);
	glDeleteProgram(plane_object.program);
}


int main(int argc, char **argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* mainwindow = glfwCreateWindow(700, 700, "2022150168_吴嘉楷_实验3.2", NULL, NULL);
	if (mainwindow == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainwindow);
	glfwSetFramebufferSizeCallback(mainwindow, framebuffer_size_callback);
	glfwSetKeyCallback(mainwindow,mainWindow_key_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
	glEnable(GL_DEPTH_TEST);
	init();
    printHelp();
	while (!glfwWindowShouldClose(mainwindow))
    {
        
        display();
        glfwSwapBuffers(mainwindow);
        glfwPollEvents();
		
    }
    glfwTerminate();
    return 0;
}
