#include "Camera.h"

Camera::Camera() { updateCamera(); };
Camera::~Camera() {};

// 获取观察矩阵
glm::mat4 Camera::getViewMatrix()
{
	return this->lookAt(eye, at, up);
}

// 获取投影矩阵
glm::mat4 Camera::getProjectionMatrix(bool isOrtho)
{
	// 使用正交
	if (isOrtho) {
		return this->ortho(-scale, scale, -scale, scale, this->zNear, this->zFar);
	}
	// 使用透视
	else {
		return this->perspective(fov, aspect, this->zNear, this->zFar);
	}
}


glm::mat4 Camera::lookAt(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up)
{
	// @TODO: Task1:请按照实验课内容补全相机观察矩阵的计算
	// 计算相机的观察方向(从eye到at的方向)
	glm::vec3 forward = glm::normalize(glm::vec3(eye - at));
	// 计算相机的右向量（与forward和up向量垂直）
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(up), forward));
	// 计算相机的新上向量（与forward和right向量垂直）
	glm::vec3 newUp = glm::cross(forward, right);
	// 初始化观察矩阵
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	// 设置观察矩阵的各个分量
	viewMatrix[0][0] = right.x;
	viewMatrix[1][0] = right.y;
	viewMatrix[2][0] = right.z;
	viewMatrix[0][1] = newUp.x;
	viewMatrix[1][1] = newUp.y;
	viewMatrix[2][1] = newUp.z;
	viewMatrix[0][2] = forward.x;
	viewMatrix[1][2] = forward.y;
	viewMatrix[2][2] = forward.z;
	// 更新观察矩阵的平移部分
	viewMatrix[3][0] = -glm::dot(right, glm::vec3(eye));
	viewMatrix[3][1] = -glm::dot(newUp, glm::vec3(eye));
	viewMatrix[3][2] = -glm::dot(forward, glm::vec3(eye));
	// 返回观察矩阵
	return viewMatrix;
}

glm::mat4 Camera::ortho(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{	
	// @TODO: Task1:请按照实验课内容补全
	// 创建一个单位矩阵作为正交投影矩阵的初始值
	glm::mat4 orthoMatrix = glm::mat4(1.0f);
	// 设置正交投影矩阵的各个分量
	orthoMatrix[0][0] = 2.0f / (right - left);
	orthoMatrix[1][1] = 2.0f / (top - bottom);
	orthoMatrix[2][2] = -2.0f / (zFar - zNear);
	orthoMatrix[3][0] = -(right + left) / (right - left);
	orthoMatrix[3][1] = -(top + bottom) / (top - bottom);
	orthoMatrix[3][2] = -(zFar + zNear) / (zFar - zNear);
	// 返回正交投影矩阵
	return orthoMatrix;
}

glm::mat4 Camera::perspective(const GLfloat fovy, const GLfloat aspect,
	const GLfloat zNear, const GLfloat zFar)
{
	// @TODO: Task1:请按照实验课内容补全
	// 创建一个单位矩阵作为透视投影矩阵的初始值
	glm::mat4 perspectiveMatrix = glm::mat4(1.0f);
	// 计算透视投影矩阵的元素值
	float f = 1.0f / tan(glm::radians(fov / 2.0f)); // 计算焦距
	perspectiveMatrix[0][0] = f / aspect;  // X 缩放因子
	perspectiveMatrix[1][1] = f;           // Y 缩放因子
	perspectiveMatrix[2][2] = (zFar + zNear) / (zNear - zFar); // Z 缩放因子
	perspectiveMatrix[2][3] = -1.0f;       // Z 平移因子（注意为负值）
	perspectiveMatrix[3][2] = (2.0f * zFar * zNear) / (zNear - zFar); // Z 平移因子
	perspectiveMatrix[3][3] = 0.0f;        // W 缩放因子
	// 返回透视投影矩阵
	return perspectiveMatrix;
}

glm::mat4 Camera::frustum(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	// 任意视锥体矩阵
	glm::mat4 c = glm::mat4(1.0f);
	c[0][0] = 2.0 * zNear / (right - left);
	c[0][2] = (right + left) / (right - left);
	c[1][1] = 2.0 * zNear / (top - bottom);
	c[1][2] = (top + bottom) / (top - bottom);
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0 * zFar * zNear / (zFar - zNear);
	c[3][2] = -1.0;
	c[3][3] = 0.0;

	c = glm::transpose(c);
	return c;
}


void Camera::updateCamera()
{
	// 使用相对于at的角度控制相机的时候，注意在upAngle大于90的时候，相机坐标系的u向量会变成相反的方向，
	// 要将up的y轴改为负方向才不会发生这种问题

	// 也可以考虑直接控制相机自身的俯仰角，
	// 保存up，eye-at 这些向量，并修改这些向量方向来控制
	// 看到这里的有缘人可以试一试
	up = glm::vec4(0.0, 1.0, 0.0, 0.0);
	if (upAngle > 90){
		up.y = -1;
	}
	else if (upAngle < -90){
		up.y = -1;
	}
	float eyex = radius * cos(upAngle * M_PI / 180.0) * sin(rotateAngle * M_PI / 180.0);
	float eyey = radius * sin(upAngle * M_PI / 180.0);
	float eyez = radius * cos(upAngle * M_PI / 180.0) * cos(rotateAngle * M_PI / 180.0);

	eye = glm::vec4(eyex, eyey, eyez, 1.0);
	at = glm::vec4(0.0, 0.0, 0.0, 1.0);
	// up = vec4(0.0, 1.0, 0.0, 0.0);

}

void Camera::keyboard(int key, int action, int mode)
{
	// 键盘事件处理

	if(key == GLFW_KEY_U && action == GLFW_PRESS && mode == 0x0000) 
	{
		rotateAngle += 5.0;
	}
	else if(key == GLFW_KEY_U && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		rotateAngle -= 5.0;
	}
	else if(key == GLFW_KEY_I && action == GLFW_PRESS && mode == 0x0000) 
	{
		upAngle += 5.0;
		if (upAngle > 180)
			upAngle = 180;
	}
	else if(key == GLFW_KEY_I && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		upAngle -= 5.0;
		if (upAngle < -180)
			upAngle = -180;
	}
	else if(key == GLFW_KEY_O && action == GLFW_PRESS && mode == 0x0000) 
	{
		scale += 0.1;
	}
	else if(key == GLFW_KEY_O && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT) 
	{
		scale -= 0.1;
	}
	else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS && mode == 0x0000) 
	{
		radius = 4.0;
		rotateAngle = 0.0;
		upAngle = 30.0;
		fov = 45.0;
		aspect = 1.0;
		scale = 1.5;
	}
}
