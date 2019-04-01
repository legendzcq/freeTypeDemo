

#define mark freetype2 demo

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>


int main() {

    FT_Library pFTLib = NULL;
    FT_Face pFTFace = NULL;
    FT_Error error = 0;
    //Init FreeType Lib to manage memory
    error = FT_Init_FreeType(&pFTLib);
    if (error) {
        pFTLib = 0;
        printf(" There is some error when Init Library ");
        return -1;
    }
    //create font face from font file
    error = FT_New_Face(pFTLib, "/Users/qishao/Desktop/demo2/opengldemo1/opengldemo1/default.ttf", 0, &pFTFace);
    if (!error) {
        FT_Set_Char_Size(pFTFace, 16 << 6, 16 << 6, 300, 300);
        FT_Glyph glyph;
        //  load glyph 'C'
        FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace, 24352), FT_LOAD_DEFAULT);
        error = FT_Get_Glyph(pFTFace->glyph, &glyph);
        if (!error) {
            //  convert glyph to bitmap with 256 gray
            FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
            FT_Bitmap &bitmap = bitmap_glyph->bitmap;
            for (int i = 0; i < bitmap.rows; ++i) {
                for (int j = 0; j < bitmap.width; ++j) {
                    //  if it has gray>0 we set show it as 1, o otherwise
                    printf(" %d ", bitmap.buffer[i * bitmap.width + j] ? 1 : 0);
                  
                }
                printf(" \n ");
            }
            //  free glyph
            FT_Done_Glyph(glyph);
            glyph = NULL;
        }
        //  free face
        FT_Done_Face(pFTFace);
        pFTFace = NULL;
    }

    //  free FreeType Lib
    FT_Done_FreeType(pFTLib);
    pFTLib = NULL;
}

#define mark OpenGL simplydemo

////
////  main.cpp
////  opengldemo1
////
////  Created by 奇少 on 2019/3/31.
////  Copyright © 2019 奇少. All rights reserved.
////
//
//#include "main.hpp"
//#include <stdio.h>
////glad 一定要在 glfw 上边
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stdio.h>
//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//
//int main(int argc, char **argv){
//    using std::cout;    using std::endl;
//    glfwInit();
//    //    主版本
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //    次版本
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //    告诉glfw 我们使用的是core_profile 核心模块
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //    向前兼容
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    //    创建一个GLFW 窗口   宽 高  窗口名字  后边两个暂时不用管
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    //    通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
//    glfwMakeContextCurrent(window);
//
//    //    GLAD 是用来管理openGL 的函数指针的。所以在调用任何openGL函数之前我们都需要初始化GLAD。
//    //    我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//    //    创建渲染的视口: 我们必须要告诉OpenGl 需要渲染的尺寸大小，即为视口 viewport(),这样openGL 才能知道根据窗口大小显示数据和坐标。
//    //    glViewport 前两个参数控制视口左下角位置，后两个参数控制视口的宽和高
//    //    openGL 幕后使用的是glViewport 定义的 位置和宽高进行2D转换
//    glViewport(0, 0, 800, 600);
//    //    窗口调整的时候 视口应该也被调整  对窗口注册一个回调函数每次窗口大小被调整的时候会被调用
//    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//
//
//    //   通过 glfwSetFramebufferSizeCallback glfw 函数 当窗口frame 变化时会调用。
//    //    对于视网膜屏 Retain 屏   宽度和高度明显比原输入值更高一点。
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    void processInput(GLFWwindow *window);
//
//    //   为了防止 渲染的图像一出现就退出 我们使用while 循环 。我们可以称之为Render Loop
//    //    glfwWindowShouldClose 每次循环开始前检查一次GLFW 是否被要求退出 是true 的话渲染便结束了。
//    while(!glfwWindowShouldClose(window))
//    {
//        //输出控制
//        processInput(window);
//        //        glfwSwapBuffers 会交换颜色缓冲（他是存储着GLFW 窗口每一个像素色值的大缓冲），将会作为输出显示在屏幕上
//        //        当程序退出的时候 使用一个自定义的颜色清空屏幕  在每个新的渲染迭代可是的时候我们总希望清屏否则总是看到上次渲染的结果。
//        //        我们可以使用glClear   GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。 我们清空颜色 。
//        glClearColor(0.5f, 0.1f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        glfwSwapBuffers(window);
//        //        glfwPollEvents 检查函数有没有触发什么事件 键盘输入 鼠标移动 并调用对应函数
//        glfwPollEvents();
//    }
//
//
//    glfwTerminate();
//
//    return 0;
//}
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//void processInput(GLFWwindow *window)
//{
//    //
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//












#define mark OpenGL ClionDemo



//#define STB_IMAGE_IMPLEMENTATION
//
//
//#include "Shader.h"
//#include "stb_image.h"
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
//
//bool firstMouse = true;
//float yaw   = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch =  0.0f;
//float lastX =  800.0f / 2.0;
//float lastY =  600.0 / 2.0;
//float fov   =  45.0f;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    Shader ourShader("./4.1.texture.vs",
//                     "./4.1.texture.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//    // world space positions of our cubes
//    glm::vec3 cubePositions[] = {
//        glm::vec3( 0.0f,  0.0f,  0.0f),
//        glm::vec3( 2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3 (2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3( 1.3f, -2.0f, -2.5f),
//        glm::vec3( 1.5f,  2.0f, -2.5f),
//        glm::vec3( 1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // texture coord attribute
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//
//    // load and create a texture
//    // -------------------------
//    unsigned int texture1, texture2;
//    // texture 1
//    // ---------
//    glGenTextures(1, &texture1);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//    unsigned char *data = stbi_load("./wall.jpg", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//    // texture 2
//    // ---------
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    data = stbi_load("./awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//    // -------------------------------------------------------------------------------------------
//    ourShader.use();
//    ourShader.setInt("texture1", 0);
//    ourShader.setInt("texture2", 1);
//
//    //    glm::mat4 projection = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    //    ourShader.setMat4("projection", projection);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//        // bind textures on corresponding texture units
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        // activate shader
//        ourShader.use();
//
//
//        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        ourShader.setMat4("projection", projection);
//
//        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//        ourShader.setMat4("view", view);
//
//
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//
//
//
//
//
//
//
//
//
//
//        //        glm::mat4 view = glm::mat4(1.0f);
//        //        float  radius = 10.0f;
//        //        float  camX = sin(glfwGetTime()) * radius;
//        //        float  camZ = cos(glfwGetTime()) * radius;
//        //        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//        //        ourShader.setMat4("view",view);
//        //
//        //        glBindVertexArray(VAO);
//        //        for (unsigned int i = 0; i < 10; ++i) {
//        //            glm::mat4 model = glm::mat4(1.0f);
//        //            model = glm::translate(model,cubePositions[i]);
//        //            float angle = 20.0f * i;
//        //            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
//        //            ourShader.setMat4("model",model);
//        //
//        //            glDrawArrays(GL_TRIANGLES,0,36);
//        //        }
//
//
//
//
//
//        //        // create transformations
//        //        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        //        glm::mat4 view          = glm::mat4(1.0f);
//        //        glm::mat4 projection    = glm::mat4(1.0f);
//        //        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//        //        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//        //        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        //        // retrieve the matrix uniform locations
//        //        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//        //        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
//        //        // pass them to the shaders (3 different ways)
//        //        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//        //        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//        //        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//        //        ourShader.setMat4("projection", projection);
//        //
//        //        // render container
//        //        glBindVertexArray(VAO);
//        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    float cameraSpeed = 2.5 * deltaTime;
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.1f; // change this value to your liking
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    // make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    if (fov >= 1.0f && fov <= 45.0f)
//        fov -= yoffset;
//    if (fov <= 1.0f)
//        fov = 1.0f;
//    if (fov >= 45.0f)
//        fov = 45.0f;
//}
