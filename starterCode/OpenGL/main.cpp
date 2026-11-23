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
#include "GLTriangleMesh.h"
#include "OBJLoader.h"

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
  glClearColor(0.5, 0.7, 1.0, 1.0);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  // setup Camera
  vec3 viewDir(0, -0.3, -1.0);
  vec3 origin(0, 2.0, 1.0);
  double imagePlaneWidth = 1.0;
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
  // the two lights
  glm::vec4 lightPositions[2] = { glm::vec4(4.0f, 4.0f, 0.0f, 1.0f), glm::vec4(-4.0f, 2.0f, -1.0f, 1.0f) };
  glm::vec3 lightIntensities[2] = { glm::vec3(0.8f, 0.68f, 0.56f), glm::vec3(0.14f, 0.21f, 0.35f) };

  glm::mat4 modelTransform = glm::mat4(1.0);
  glm::mat4 M_normal = glm::inverse(glm::transpose(modelTransform));

  // materials
  glm::vec3 cyan(0.0f, 0.8f, 0.8f);
  glm::vec3 floorGray(0.5f, 0.5f, 0.5f);
  glm::vec3 satinSpecular(0.6f, 0.6f, 0.6f);
  float satinShininess = 16.0f;
  glm::vec3 glossySpecular(1.0f, 1.0f, 1.0f);
  float glossyShininess = 200.0f;


  GLint major_version;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

  // build scene here

  // zbramblett scene
  auto floorSphere = std::make_shared<GLSphere>(glm::vec3(0.0f, -100.5f, -5.0f), 100.0f, 5);
  auto leftSphere = std::make_shared<GLSphere>(glm::vec3(-1.2f, 0.0f, -4.0f), 0.5f, 4);
  auto middleSphere = std::make_shared<GLSphere>(glm::vec3(0.0f, 0.0f, -4.0f), 0.5f, 4);
  auto rightSphere = std::make_shared<GLSphere>(glm::vec3(1.2f, 0.0f, -4.0f), 0.5f, 4);

  // bunny code
  // std::vector<glm::vec3> bunnyVert = loadOBJ("../../OpenGL/Models/stanford-bunny.obj");
  // auto bunny = std::make_shared<GLTriangleMesh>(bunnyVert);
  // glm::mat4 bunnyTransform = glm::scale(glm::mat4(1.0f), glm::vec3(40.0f));
  // glm::mat4 M_normalBunny = glm::mat4(glm::mat3(glm::inverse(glm::transpose(bunnyTransform))));


  // horse code
  // std::vector<glm::vec3> horseVert = loadOBJ("../../OpenGL/Models/horse.obj");
  // auto horse = std::make_shared<GLTriangleMesh>(horseVert);

  // glm::mat4 horseTransform = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1, 0));
  // horseTransform = glm::rotate(horseTransform, glm::radians(-90.0f), glm::vec3(1, 0, 0));
  // horseTransform = glm::scale(horseTransform, glm::vec3(40.0f));
  // glm::mat4 M_normalHorse = glm::mat4(glm::mat3(glm::inverse(glm::transpose(horseTransform))));


  // Create a shader using my GLSLObject class
  sivelab::GLSLObject shader;
  shader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
  shader.addShader("fragmentShader_BlinnPhong.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
  shader.createProgram();

  GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID, lightPosWorldID, lightIntensityID, diffuseComponentID, cameraPosID, specularComponentID, shininessID;
  projMatrixID = shader.createUniform("projMatrix");
  viewMatrixID = shader.createUniform("viewMatrix");
  modelMatrixID = shader.createUniform("modelMatrix");
  normalMatrixID = shader.createUniform("normalMatrix");
  lightPosWorldID = shader.createUniform("lightPosWorld");
  lightIntensityID = shader.createUniform("lightIntensity");
  diffuseComponentID = shader.createUniform("diffuseComponent");
  specularComponentID = shader.createUniform("specularComponent");
  shininessID = shader.createUniform("shininess");
  cameraPosID = shader.createUniform("cameraPos");

  // Lambertian program (left triangle)
  sivelab::GLSLObject lambertianShader;
  lambertianShader.addShader("vertexShader_PrepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
  lambertianShader.addShader("fragmentShader_Lambertian.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
  lambertianShader.createProgram();

  GLuint lamProjMatrixID, lamViewMatrixID, lamModelMatrixID, lamNormalMatrixID, lamLightPosWorldID, lamLightIntensityID, lamDiffuseComponentID;
  lamProjMatrixID = lambertianShader.createUniform("projMatrix");
  lamViewMatrixID = lambertianShader.createUniform("viewMatrix");
  lamModelMatrixID = lambertianShader.createUniform("modelMatrix");
  lamNormalMatrixID = lambertianShader.createUniform("normalMatrix");
  lamLightPosWorldID = lambertianShader.createUniform("lightPosWorld");
  lamLightIntensityID = lambertianShader.createUniform("lightIntensity");
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
    glUniform4fv(lightPosWorldID, 2, glm::value_ptr(lightPositions[0]));
    glUniform3fv(lightIntensityID, 2, glm::value_ptr(lightIntensities[0]));
    glUniform4f(cameraPosID, cameraPos.x, cameraPos.y, cameraPos.z, cameraPos.w);

    // draw blinn-phong shapes here

    // satin
    glUniform3fv(diffuseComponentID, 1, glm::value_ptr(cyan));
    glUniform3fv(specularComponentID, 1, glm::value_ptr(satinSpecular));
    glUniform1f(shininessID, satinShininess);
    middleSphere->draw();

    // glossy
    glUniform3fv(diffuseComponentID, 1, glm::value_ptr(cyan));
    glUniform3fv(specularComponentID, 1, glm::value_ptr(glossySpecular));
    glUniform1f(shininessID, glossyShininess);
    rightSphere->draw();

    shader.deactivate();

    // Lambertian
    lambertianShader.activate();

    glUniformMatrix4fv(lamViewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
    glUniformMatrix4fv(lamProjMatrixID, 1, GL_FALSE, glm::value_ptr(perspMat));
    glUniformMatrix4fv(lamModelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(lamNormalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normal));
    glUniform4fv(lamLightPosWorldID, 2, glm::value_ptr(lightPositions[0]));
    glUniform3fv(lamLightIntensityID, 2, glm::value_ptr(lightIntensities[0]));

    // draw lambertian shapes here

    // matte
    glUniform3fv(lamDiffuseComponentID, 1, glm::value_ptr(cyan));
    leftSphere->draw();

    // floor
    glUniform3fv(lamDiffuseComponentID, 1, glm::value_ptr(floorGray));
    floorSphere->draw();

    // glUniformMatrix4fv(lamModelMatrixID, 1, GL_FALSE, glm::value_ptr(horseTransform));
    // glUniformMatrix4fv(lamNormalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normalHorse));
    // horse->draw();

    // glUniformMatrix4fv(lamModelMatrixID, 1, GL_FALSE, glm::value_ptr(bunnyTransform));
    // glUniformMatrix4fv(lamNormalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normalBunny));
    // bunny->draw();


    lambertianShader.deactivate();

    // Normal
    normalShader.activate();

    glUniformMatrix4fv(normViewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
    glUniformMatrix4fv(normProjMatrixID, 1, GL_FALSE, glm::value_ptr(perspMat));
    glUniformMatrix4fv(normModelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(normNormalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normal));

    // draw normal shapes here

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
    float turnRatePerFrame = 0.02f;
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

    // turns left and right
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      m_W = glm::mat3(glm::rotate(glm::mat4(1.0f), turnRatePerFrame, worldUp)) * m_W;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      m_W = glm::mat3(glm::rotate(glm::mat4(1.0f), -turnRatePerFrame, worldUp)) * m_W;
    }

    // looks up and down, stops before straight up or down
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      glm::vec3 newW = glm::mat3(glm::rotate(glm::mat4(1.0f), turnRatePerFrame, m_U)) * m_W;
      if (std::abs(newW.y) < 0.99f) {
        m_W = newW;
      }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      glm::vec3 newW = glm::mat3(glm::rotate(glm::mat4(1.0f), -turnRatePerFrame, m_U)) * m_W;
      if (std::abs(newW.y) < 0.99f) {
        m_W = newW;
      }
    }

    // rebuilds the camera axes
    m_W = glm::normalize(m_W);
    m_U = glm::normalize(glm::cross(worldUp, m_W));
    m_V = glm::cross(m_W, m_U);

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << "fps: " << 1.0 / timeDiff << std::endl;
    }
  }

  // free your shapes here before opengl shuts down
  // horse.reset();
  // bunny.reset();
  floorSphere.reset();
  leftSphere.reset();
  middleSphere.reset();
  rightSphere.reset();

  glfwTerminate();
  return 0;
}
