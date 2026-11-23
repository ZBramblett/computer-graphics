#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"
#include "GLTriangle.h"
#include "GLSphere.h"

#include "PerspectiveCamera.h"

// convert ray tracer vec3 (doubles) to glm::vec3 (floats)
glm::vec3 toGlm(const vec3 &v) { return glm::vec3(v.x(), v.y(), v.z()); }

int CheckGLErrors(const char *s)
{
  int errCount = 0;
  return errCount;
}

int main(void)
{
  /* Initialize the library */
  if (!glfwInit()) {
    exit(-1);
  }
  // throw std::runtime_error("Error! initialization of glfw failed!");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  /* Create a windowed mode window and its OpenGL context */
  int winWidth = 1000;
  float aspectRatio = 1.0;// 16.0 / 9.0; // winWidth / (float)winHeight;
  int winHeight = winWidth / aspectRatio;

  GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW did not create a window!" << std::endl;

    glfwTerminate();
    return -1;
  }


  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "GLEW Error! glewInit failed, exiting." << std::endl;
    exit(EXIT_FAILURE);
  }

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(.25, .25, .25, 1.0);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  // setup Camera
  vec3 viewDir(0, 0, -1);
  vec3 origin(0, 0, 40);
  double imagePlaneWidth = .5;
  double focalLength = 1.0;

  auto pCam = std::make_shared<PerspectiveCamera>(viewDir, origin, fb_height, fb_width, imagePlaneWidth, focalLength);

  // seed local copies from the camera; m_pos changes with keyboard movement
  glm::vec3 m_pos = toGlm(pCam->getOrigin());
  glm::vec3 m_U = toGlm(pCam->getU());
  glm::vec3 m_V = toGlm(pCam->getV());
  glm::vec3 m_W = toGlm(pCam->getW());

  // Projection matrix from the camera's image plane: near plane = image plane
  float farPlane = 100.0f;
  glm::mat4 perspMat = glm::frustum<float>(pCam->getLeft(), pCam->getRight(), pCam->getBottom(), pCam->getTop(), pCam->getFocalLength(), farPlane);
  glm::vec4 lightPos(0.0f, 0.0f, 1.0f, 1.0f);
  glm::vec3 diffuseComponent(0.0f, 1.0f, 1.0f);
  glm::vec3 specularComponent(0.8f, 0.8f, 0.8f);
  float shininess(128.0f);

  glm::mat4 modelTransform = glm::mat4(1.0);
  glm::mat4 M_normal = glm::inverse(glm::transpose(modelTransform));

  glm::mat4 leftTransform = glm::translate(glm::mat4(1.0), glm::vec3(-6.5f, 0.0f, 0.0f));
  glm::mat4 rightTransform = glm::translate(glm::mat4(1.0), glm::vec3(6.5f, 0.0f, 0.0f));

  glm::mat4 M_normalLeft = glm::mat4(glm::mat3(glm::inverse(glm::transpose(leftTransform))));
  glm::mat4 M_normalRight = glm::mat4(glm::mat3(glm::inverse(glm::transpose(rightTransform))));
  glm::vec3 lambertDiffuse(0.0f, 1.0f, 1.0f);


  GLint major_version;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

  // makes the triangle
  auto triangle = std::make_shared<GLTriangle>(glm::vec3(-3.0f, -3.0f, 0.0f), glm::vec3(3.0f, -3.0f, 0.0f), glm::vec3(0.0f, 3.0f, 0.0f));

  // makes the sphere
  auto sphere = std::make_shared<GLSphere>(glm::vec3(0.0f, 6.0f, 0.0f), 2.5f);

  // Create a shader using my GLSLObject class
  sivelab::GLSLObject shader;
  shader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
  shader.addShader("fragmentShader_BlinnPhong.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
  shader.createProgram();

  GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID, lightPosWorldID, diffuseComponentID, cameraPosID, specularComponentID, shininessID;
  projMatrixID = shader.createUniform("projMatrix");
  viewMatrixID = shader.createUniform("viewMatrix");
  modelMatrixID = shader.createUniform("modelMatrix");
  normalMatrixID = shader.createUniform("normalMatrix");
  lightPosWorldID = shader.createUniform("lightPosWorld");
  diffuseComponentID = shader.createUniform("diffuseComponent");
  specularComponentID = shader.createUniform("specularComponent");
  shininessID = shader.createUniform("shininess");
  cameraPosID = shader.createUniform("cameraPos");

  // Lambertian program (left triangle)
  sivelab::GLSLObject lambertianShader;
  lambertianShader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
  lambertianShader.addShader("fragmentShader_Lambertian.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
  lambertianShader.createProgram();

  GLuint lamProjMatrixID, lamViewMatrixID, lamModelMatrixID, lamNormalMatrixID, lamLightPosWorldID, lamDiffuseComponentID;
  lamProjMatrixID = lambertianShader.createUniform("projMatrix");
  lamViewMatrixID = lambertianShader.createUniform("viewMatrix");
  lamModelMatrixID = lambertianShader.createUniform("modelMatrix");
  lamNormalMatrixID = lambertianShader.createUniform("normalMatrix");
  lamLightPosWorldID = lambertianShader.createUniform("lightPosWorld");
  lamDiffuseComponentID = lambertianShader.createUniform("diffuseComponent");

  // Normal program (right triangle)
  sivelab::GLSLObject normalShader;
  normalShader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
  normalShader.addShader("fragmentShader_Normal.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
  normalShader.createProgram();

  GLuint normProjMatrixID, normViewMatrixID, normModelMatrixID, normNormalMatrixID;
  normProjMatrixID = normalShader.createUniform("projMatrix");
  normViewMatrixID = normalShader.createUniform("viewMatrix");
  normModelMatrixID = normalShader.createUniform("modelMatrix");
  normNormalMatrixID = normalShader.createUniform("normalMatrix");

  double timeDiff = 0.0,
         startFrameTime = 0.0, endFrameTime = 0.0;


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    startFrameTime = glfwGetTime();

    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // create the view matrix from out camera data
    glm::mat4 M_view = glm::lookAt(m_pos, m_pos - m_W, m_V);
    glm::vec4 cameraPos(m_pos.x, m_pos.y, m_pos.z, 1);

    /* Render your objects here */
    shader.activate();

    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(perspMat));
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normal));
    glUniform4f(lightPosWorldID, lightPos.x, lightPos.y, lightPos.z, lightPos.w);
    glUniform3f(diffuseComponentID, diffuseComponent.x, diffuseComponent.y, diffuseComponent.z);
    glUniform3f(specularComponentID, specularComponent.x, specularComponent.y, specularComponent.z);
    glUniform4f(cameraPosID, cameraPos.x, cameraPos.y, cameraPos.z, cameraPos.w);
    glUniform1f(shininessID, shininess);

    triangle->draw();
    sphere->draw();

    shader.deactivate();

    // Left triangle: Lambertian
    lambertianShader.activate();

    glUniformMatrix4fv(lamViewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
    glUniformMatrix4fv(lamProjMatrixID, 1, GL_FALSE, glm::value_ptr(perspMat));
    glUniformMatrix4fv(lamModelMatrixID, 1, GL_FALSE, glm::value_ptr(leftTransform));
    glUniformMatrix4fv(lamNormalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normalLeft));
    glUniform4f(lamLightPosWorldID, lightPos.x, lightPos.y, lightPos.z, lightPos.w);
    glUniform3f(lamDiffuseComponentID, lambertDiffuse.x, lambertDiffuse.y, lambertDiffuse.z);

    triangle->draw();

    lambertianShader.deactivate();

    // Right triangle: Normal
    normalShader.activate();

    glUniformMatrix4fv(normViewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
    glUniformMatrix4fv(normProjMatrixID, 1, GL_FALSE, glm::value_ptr(perspMat));
    glUniformMatrix4fv(normModelMatrixID, 1, GL_FALSE, glm::value_ptr(rightTransform));
    glUniformMatrix4fv(normNormalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normalRight));

    triangle->draw();

    normalShader.deactivate();

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    float moveRatePerFrame = 0.05;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      m_pos = m_pos + m_V * moveRatePerFrame;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      m_pos = m_pos - m_U * moveRatePerFrame;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      m_pos = m_pos - m_V * moveRatePerFrame;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      m_pos = m_pos + m_U * moveRatePerFrame;
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      m_pos = m_pos + m_W * moveRatePerFrame;
    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
      m_pos = m_pos - m_W * moveRatePerFrame;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << "fps: " << 1.0 / timeDiff << std::endl;
    }
  }

  // frees the triangle before opengl shuts down
  triangle.reset();
  sphere.reset();

  glfwTerminate();
  return 0;
}
