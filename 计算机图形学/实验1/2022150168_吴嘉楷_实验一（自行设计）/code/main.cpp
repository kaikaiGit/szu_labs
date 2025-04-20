#include "Angel.h"
#include <string>

const glm::vec3 WHITE(1.0, 1.0, 1.0);
const glm::vec3 BLACK(0.0, 0.0, 0.0);
const glm::vec3 RED(1.0, 0.0, 0.0);
const glm::vec3 GREEN(0.0, 1.0, 0.0);
const glm::vec3 BLUE(0.0, 0.0, 1.0); 
const glm::vec3 GREY(0.73, 0.73, 0.73); 
const glm::vec3 WHEAT(0.96, 0.87, 0.70); 

const int CIRCLE_NUM_POINTS = 100;
const int ELLIPSE_NUM_POINTS = 100;
const int TRIANGLE_LINE_NUM_POINTS = 1000;
const int TRIANGLE_NUM_POINTS  = 3;
const int SQUARE_NUM  = 1;
const int SQUARE_NUM_POINTS  = 4 * SQUARE_NUM;
const int LINE_NUM_POINTS = 2;

// 每当窗口改变大小，GLFW会调用这个函数并填充相应的参数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// 获得三角形的每个角度
double getTriangleAngle(int point)
{
	return 2 * M_PI / 3 * point;
}

// 获得正方形的每个角度
double getSquareAngle(int point)
{
	return M_PI / 4 + (M_PI / 2 * point);
}

// 计算椭圆/圆上的点
glm::vec2 getEllipseVertex(glm::vec2 center, double scale, double verticalScale, double angle, double rotate)
{
	glm::vec2 vertex(sin(angle), cos(angle));
	vertex *= scale;
	vertex.y *= verticalScale;
	// 构建旋转矩阵，用于对点进行旋转
	glm::mat2x2 rMat(cos(rotate), -sin(rotate), sin(rotate), cos(rotate));
	// 应用旋转矩阵，将点旋转到指定角度
	vertex = vertex * rMat;

	vertex += center;
	return vertex;
}

// 获得椭圆/圆的每个顶点
void generateEllipsePoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex, int numPoints,
	glm::vec2 center, double scale, double verticalScale, double rotate, glm::vec3 color = WHITE)
{
	double angleIncrement = (2 * M_PI) / numPoints;
	double currentAngle = M_PI / 2;	//从y轴正方向开始
	rotate = rotate / 180 * M_PI;	//旋转角度变弧度
	for (int i = startVertexIndex; i < startVertexIndex + numPoints; ++i) {
		vertices[i] = getEllipseVertex(center, scale, verticalScale, currentAngle, rotate);
		if (verticalScale == 1.0) {
			colors[i] = BLACK;
		} else {
			colors[i] = color;
		}
		currentAngle += angleIncrement;
	}
}

// 获得三角形的每个顶点
void generateTrianglePoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	glm::vec2 scale(0.17, 0.17);
	glm::vec2 center(0.0, -0.65);

	for (int i = 0; i < 3; ++i) {
		double currentAngle = getTriangleAngle(i);
		vertices[startVertexIndex + i] = glm::vec2(sin(currentAngle), cos(currentAngle)) * scale + center;
	}

	colors[startVertexIndex] = RED;
	colors[startVertexIndex + 1] = GREEN;
	colors[startVertexIndex + 2] = BLUE;
}

// 获得正方形的每个顶点
void generateSquarePoints(glm::vec2 vertices[], glm::vec3 colors[], int squareNumber, int startVertexIndex)
{
	glm::vec2 scale(0.60, 0.30);
	glm::vec2 center(0.0, -0.615);
	int vertexIndex = startVertexIndex;

	glm::vec3 currentColor;
	currentColor = GREY;
	for (int j = 0; j < 4; ++j) {
		double currentAngle = getSquareAngle(j);
		vertices[vertexIndex] = glm::vec2(sin(currentAngle), cos(currentAngle)) * scale + center;
		colors[vertexIndex] = currentColor;
		vertexIndex++;
	}
}

void generateLinePoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	vertices[startVertexIndex] = glm::vec2(-0.08, 0.8);
	vertices[startVertexIndex + 1] = glm::vec2(0.08, 0.8);

	colors[startVertexIndex] = BLACK;
	colors[startVertexIndex + 1] = BLACK;
}

GLuint vao[14], program; // feat: 顶点数组对象，用于存储二维图形的数据
void init()
{
	// 定义三角形的点
	glm::vec2 triangle_vertices[TRIANGLE_NUM_POINTS];
	glm::vec3 triangle_colors[TRIANGLE_NUM_POINTS];
	// 定义矩形的点
	glm::vec2 square_vertices[SQUARE_NUM_POINTS];
	glm::vec3 square_colors[SQUARE_NUM_POINTS];
	// 定义双眼间的线的点
	glm::vec2 line_vertices[LINE_NUM_POINTS];
	glm::vec3 line_colors[LINE_NUM_POINTS];
	// feat: 定义圆的点
	// 左眼
	glm::vec2 circle_vertices[CIRCLE_NUM_POINTS];
	glm::vec3 circle_colors[CIRCLE_NUM_POINTS];
	// 右眼
	glm::vec2 circle_vertices2[CIRCLE_NUM_POINTS];
	glm::vec3 circle_colors2[CIRCLE_NUM_POINTS];
	// feat: 定义头部的点
	glm::vec2 ellipse_vertices[ELLIPSE_NUM_POINTS];
	glm::vec3 ellipse_colors[ELLIPSE_NUM_POINTS];
	glm::vec2 headLine_vertices[TRIANGLE_LINE_NUM_POINTS]; //生成头部边框的点
	glm::vec3 headLine_colors[TRIANGLE_LINE_NUM_POINTS]; //生成头部边框的颜色
	// feat: 定义身体的点
	glm::vec2 body_vertices[ELLIPSE_NUM_POINTS];
	glm::vec3 body_colors[ELLIPSE_NUM_POINTS];
	glm::vec2 bodyLine_vertices[TRIANGLE_LINE_NUM_POINTS]; //生成身体边框的点
	glm::vec3 bodyLine_colors[TRIANGLE_LINE_NUM_POINTS]; //生成身体边框的颜色
	// feat: 定义四肢的点
	// 左手臂
	glm::vec2 leftHand_vertices[ELLIPSE_NUM_POINTS];
	glm::vec3 leftHand_colors[ELLIPSE_NUM_POINTS];
	// 右手臂
	glm::vec2 rightHand_vertices[ELLIPSE_NUM_POINTS];
	glm::vec3 rightHand_colors[ELLIPSE_NUM_POINTS];
	// 左腿
	glm::vec2 leftLeg_vertices[ELLIPSE_NUM_POINTS];
	glm::vec3 leftLeg_colors[ELLIPSE_NUM_POINTS];
	// 右腿
	glm::vec2 rightLeg_vertices[ELLIPSE_NUM_POINTS];
	glm::vec3 rightLeg_colors[ELLIPSE_NUM_POINTS];

	// 调用生成形状顶点位置的函数
	generateTrianglePoints(triangle_vertices, triangle_colors, 0); // 生成三角形的顶点位置
	generateSquarePoints(square_vertices, square_colors, SQUARE_NUM, 0); // 生成长方形的顶点位置
	//feat: 调用生成左眼、右眼的顶点位置的函数
	generateEllipsePoints(circle_vertices, circle_colors, 0, CIRCLE_NUM_POINTS, glm::vec2(-0.1, 0.80), 0.035, 1,0);
	generateEllipsePoints(circle_vertices2, circle_colors2, 0, CIRCLE_NUM_POINTS, glm::vec2(0.1, 0.80), 0.035, 1,0);
	generateLinePoints(line_vertices, line_colors, 0); // 生成线的顶点位置
	// 头部
	generateEllipsePoints(ellipse_vertices, ellipse_colors, 0, ELLIPSE_NUM_POINTS, glm::vec2(0.0, 0.80), 0.24, 0.74,0); // 生成头部的顶点位置
	generateEllipsePoints(headLine_vertices, headLine_colors, 0, TRIANGLE_LINE_NUM_POINTS, glm::vec2(0.0, 0.80), 0.24, 0.74, 0, BLACK); // 生成头部的边框的顶点位置
	// 身体
	generateEllipsePoints(body_vertices, body_colors, 0, ELLIPSE_NUM_POINTS, glm::vec2(0.0, 0.25), 0.4, 1.1,0); // 生成身体的顶点位置
	generateEllipsePoints(bodyLine_vertices, bodyLine_colors, 0, TRIANGLE_LINE_NUM_POINTS, glm::vec2(0.0, 0.25), 0.4, 1.1, 0, BLACK); // 生成身体的边框的顶点位置
	// feat: 生成四肢的顶点位置
	// 生成左手臂的顶点位置
	generateEllipsePoints(leftHand_vertices, leftHand_colors, 0, ELLIPSE_NUM_POINTS, glm::vec2(-0.3, 0.34), 0.35, 0.5,230);
	// 生成右手臂的顶点位置
	generateEllipsePoints(rightHand_vertices, rightHand_colors, 0, ELLIPSE_NUM_POINTS, glm::vec2(0.3, 0.34), 0.35, 0.5,130);
	// 生成左腿的顶点位置
	generateEllipsePoints(leftLeg_vertices, leftLeg_colors, 0, ELLIPSE_NUM_POINTS, glm::vec2(-0.157, -0.15), 0.25, 0.6,97);
	// 生成右腿的顶点位置
	generateEllipsePoints(rightLeg_vertices, rightLeg_colors, 0, ELLIPSE_NUM_POINTS, glm::vec2(0.157, -0.15), 0.25, 0.6,263);

	// 读取着色器并使用
	std::string vshader, fshader;
	vshader = "shaders/vshader.glsl";
	fshader = "shaders/fshader.glsl";
	program = InitShader(vshader.c_str(), fshader.c_str());
	glUseProgram(program);

	// 创建顶点缓存对象，vbo[2]是因为我们将要使用两个缓存对象
	GLuint vbo[2];

	/*
	* 初始化三角形的数据
	*/

	glGenVertexArrays(1, &vao[12]);		
	glBindVertexArray(vao[12]);			

	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	GLuint location  = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);
	GLuint cLocation  = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));

	/*
	* 初始化长方形的数据
	*/  

	glGenVertexArrays(1, &vao[11]);      
	glBindVertexArray(vao[11]);         

	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
	location  = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_colors), square_colors, GL_STATIC_DRAW);
	cLocation  = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));

	/*
	* 初始化线的数据
	*/

	glGenVertexArrays(1, &vao[8]);
	glBindVertexArray(vao[8]);

	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_STATIC_DRAW);
	location = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_colors), line_colors, GL_STATIC_DRAW);
	cLocation = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));

	/*
	* feat: 初始化圆的数据
	*/
	// 左眼
	glGenVertexArrays(1, &vao[9]); //生成一个顶点数组对象，并将其ID存储在vao[9]中，用于存储圆的数据
	glBindVertexArray(vao[9]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_vertices), circle_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_colors), circle_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	// 右眼
	glGenVertexArrays(1, &vao[10]); //生成一个顶点数组对象，并将其ID存储在vao[9]中，用于存储圆的数据
	glBindVertexArray(vao[10]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_vertices2), circle_vertices2, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_colors2), circle_colors2, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	/*
	* feat: 初始化椭圆的数据
	*/
	// 头部
	glGenVertexArrays(1, &vao[6]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[6]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(ellipse_vertices), ellipse_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(ellipse_colors), ellipse_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	// 头部边框
	glGenVertexArrays(1, &vao[7]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[7]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(headLine_vertices), headLine_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(headLine_colors), headLine_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	// 身体
	glGenVertexArrays(1, &vao[4]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[4]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(body_vertices), body_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(body_colors), body_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	// 身体边框
	glGenVertexArrays(1, &vao[5]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[5]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(bodyLine_vertices), bodyLine_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(bodyLine_colors), bodyLine_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	// 左手臂
	glGenVertexArrays(1, &vao[0]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[0]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftHand_vertices), leftHand_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftHand_colors), leftHand_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	// 右手臂
	glGenVertexArrays(1, &vao[1]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[1]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightHand_vertices), rightHand_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightHand_colors), rightHand_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	// 左腿
	glGenVertexArrays(1, &vao[2]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[2]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftLeg_vertices), leftLeg_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftLeg_colors), leftLeg_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	// 右腿
	glGenVertexArrays(1, &vao[3]); //生成一个顶点数组对象，并将其ID存储在vao[10]中，用于存储椭圆的数据
	glBindVertexArray(vao[3]); //绑定顶点数组对象
	glGenBuffers(1, &vbo[0]); //生成一个缓冲区对象，并将其ID存储在vbo[0]中,用于存储顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeg_vertices), rightLeg_vertices, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	location = glGetAttribLocation(program, "vPosition"); //获取vPosition的位置
	glEnableVertexAttribArray(location); //启用vPosition
	glVertexAttribPointer( //指定vPosition的数据格式
		location, //vPosition的位置
		2, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec2), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量
	glGenBuffers(1, &vbo[1]); //生成一个缓冲区对象，并将其ID存储在vbo[1]中,用于存储颜色数据
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //绑定缓冲区对象,表示下面的数据将会存储在这个缓冲区对象中
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeg_colors), rightLeg_colors, GL_STATIC_DRAW); //将数据拷贝到缓冲区对象中
	cLocation = glGetAttribLocation(program, "vColor"); //获取vColor的位置
	glEnableVertexAttribArray(cLocation); //启用vColor
	glVertexAttribPointer( //指定vColor的数据格式
		cLocation, //vColor的位置
		3, //每个顶点属性的分量个数
		GL_FLOAT, //数据类型
		GL_FALSE, //是否希望数据被标准化
		sizeof(glm::vec3), //相邻两个顶点属性的字节间隔
		BUFFER_OFFSET(0)); //第一个顶点属性在缓冲区中的偏移量

	glClearColor(0.96, 0.87, 0.70, 1.0); // 设置背景颜色
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glEnable(GL_LINE_SMOOTH);// 启用线段平滑
	glEnable(GL_BLEND);// 启用混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// 设置混合函数

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 设置为填充模式
	// feat: 绘制大白的四肢
	glBindVertexArray(vao[0]);// 左手臂
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSE_NUM_POINTS); //绘制椭圆
	glBindVertexArray(vao[1]);// 右手臂
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSE_NUM_POINTS); //绘制椭圆
	glBindVertexArray(vao[2]);// 左腿
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSE_NUM_POINTS); //绘制椭圆
	glBindVertexArray(vao[3]);// 右腿
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSE_NUM_POINTS); //绘制椭圆
	// feat: 绘制大白的身体
	glBindVertexArray(vao[4]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSE_NUM_POINTS); //绘制椭圆
	glLineWidth(0.1f);//设置线宽
	glBindVertexArray(vao[5]);// 身体边框
	glDrawArrays(GL_LINE_LOOP, 0, TRIANGLE_LINE_NUM_POINTS); //绘制椭圆
	// feat: 绘制大白的头
	glBindVertexArray(vao[6]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, ELLIPSE_NUM_POINTS); //绘制椭圆
	glBindVertexArray(vao[7]);// 头部边框
	glDrawArrays(GL_LINE_LOOP, 0, TRIANGLE_LINE_NUM_POINTS); //绘制椭圆
	// feat: 绘制大白的眼睛和嘴巴
	glLineWidth(4.0f);//设置线宽
	glBindVertexArray(vao[8]);// 绘制嘴巴
	glDrawArrays(GL_LINES, 0, LINE_NUM_POINTS);
	glBindVertexArray(vao[9]);// 绘制左眼
	glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_NUM_POINTS); //绘制圆
	glBindVertexArray(vao[10]);// 绘制右眼
	glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_NUM_POINTS); //绘制圆
	// feat: 绘制站台
	glBindVertexArray(vao[11]);// 绘制长方形
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 切换为线条模式
	glLineWidth(3.0f);  // 设置描边宽度
	glBindVertexArray(vao[12]);// 绘制三角形
	glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_NUM_POINTS);

	glFlush();
}

int main(int argc, char **argv)
{
	// 初始化GLFW库
	glfwInit();

	// 配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// 配置窗口属性
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "2022150168_吴嘉楷_实验一", NULL, NULL);//feat: 修改窗口标题
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 调用任何OpenGL的函数之前初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();

	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Supported GLSL version is: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	
	while (!glfwWindowShouldClose(window))
	{	
		display();
		// 交换颜色缓冲 以及 检查有没有触发什么事件（比如键盘输入、鼠标移动等）
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
