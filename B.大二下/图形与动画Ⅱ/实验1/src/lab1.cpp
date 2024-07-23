#include "lab1.h"

namespace LAB1
{
GLfloat x = 0, y = 0, rsize = 50; // 设置初始位置和大小
GLfloat dx = 1.5, dy = 1.5; // 设置初始速度
GLfloat windowWidth, windowHeight; // 窗口大小
GLfloat red = 181. / 225, green = 206. / 225, blue = 163. / 255; // 设置初始颜色为黄绿色

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
        red = 181. / 225;
        green = 206. / 225;
        blue = 163. / 255;
        break;
    case GLUT_KEY_F2:
        red = 163. / 255;
        green = 163. / 255;
        blue = 163. / 255;
        break;
    case GLUT_KEY_F3:
        red = 30. / 255;
        green = 60. / 255;
        blue = 153. / 255;
        break;
    }
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC键
        exit(0);
        break;
    case 'w': // 增加y方向的速度
        dy += 0.1;
        break;
    case 's': // 减少y方向的速度，但不小于0
        if (dy > 0)
        {
            dy -= 0.1;            
        }
        break;
    case 'a': // 减少x方向的速度，但不小于0
        if (dx > 0)
        {
            dx -= 0.1;            
        }
        break;
    case 'd': // 增加x方向的速度
        dx += 0.1;
        break;
    }
}

// 渲染函数，绘制一个单色的三角形
void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区

    glPushMatrix();

    glColor3f(red, green, blue); // 设置颜色

    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);     
    glVertex2f(x + rsize, y);
    glVertex2f(x + rsize / 2, y + rsize);
    glEnd();

    glPopMatrix();
    glutSwapBuffers(); // 设置双缓冲
}


void timer(int value)
{
    // 先更新位置
    x += dx;
    y += dy;

    // 然后检测碰撞，如果碰到边界就反弹
    if (x + rsize > windowWidth || x < -windowWidth)
    {
        dx = -dx;
        x += dx; // 稍微调整位置，防止卡在边界上
    }
    if (y + rsize > windowHeight || y < -windowHeight)
    {
        dy = -dy;
        y += dy; // 稍微调整位置，防止卡在边界上
    }

    glutPostRedisplay(); // 重绘
    glutTimerFunc(16, timer, 1); // 设置定时器
}

void changeSize(int w, int h)
{
    GLfloat aspectRatio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h); // 设置视口大小
    glMatrixMode(GL_PROJECTION); // 设置投影矩阵
    glLoadIdentity(); // 重置投影矩阵
    aspectRatio = (GLfloat)w / (GLfloat)h; // 计算窗口的宽高比
    if (w <= h)
    {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;       
    }
    else
    {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;       
    }
    glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW); // 设置模型视图矩阵
    glLoadIdentity(); // 重置模型视图矩阵
}

void setupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景颜色为黑色
}

int lab1(int argc, char** argv)
{
    glutInit(&argc, argv); // 初始化GLUT库
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 设置显示模式为双缓冲和RGB颜色模式
    glutInitWindowSize(400, 400); // 设置窗口大小
    glutInitWindowPosition(100, 100); // 设置窗口位置
    glutCreateWindow("Simple Triangle Bounce"); // 创建窗口，并设置标题
    glutDisplayFunc(renderScene); // 设置绘图函数


    glutReshapeFunc(changeSize); // 设置窗口大小变化回调函数
    glutTimerFunc(16, timer, 1); // 设置定时器


    glutSpecialFunc(processSpecialKeys); // 设置特殊键回调函数
    glutKeyboardFunc(processNormalKeys); // 设置普通键回调函数

    setupRC();

    glutMainLoop(); // 进入主循环，等待事件

    return 0;
}
} // namespace lab1