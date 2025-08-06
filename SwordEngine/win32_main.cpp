#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include </Programming/SwordEngine/SwordEngine/shader_s.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {

    //glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); -- needed for Mac

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(1280, 720, "WINDOW", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //unable to create glfw window
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //GLAD opengl functions

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1; //failed to initialize glad
    }

    Shader ourShader("E:/Programming/SwordEngine/SwordEngine/Shaders/vertex_shader.vert", "E:/Programming/SwordEngine/SwordEngine/Shaders/fragment_shader.frag");
    //vertex input
    float vertices[] = {
        // position          // colors
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,//top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,//bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,//top left
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,//bottom left
    };

    unsigned int indices[] = {
        0, 1, 2, // first triangle
        2, 3, 1  //second
    };

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //wireframe 
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int nrAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, & nrAttribs);
    std::cout << "Max attribs: " << nrAttribs << std::endl;


    
    //render loop
    while (!glfwWindowShouldClose(window)) {

        //input
        processInput(window);

        //render
        glClearColor(191.f/255.f, 170.f/255.f, 170.f / 255.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activate shader
        ourShader.use();
        
        
        //draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //buffer check and swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}