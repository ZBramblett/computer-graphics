#pragma once

#include "ISceneLoader.h"
#include "Scene.h"
#include "PerspectiveCamera.h"
#include "LambertianShader.h"
#include "BlinnPhongShader.h"
#include "MirrorShader.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"
#include <iostream>
#include <stdexcept>
#include <unordered_map>

class SceneLoader : public ISceneLoader
{
private:
  Scene &m_targetScene;// Reference to the external scene

public:
  // The caller provides the scene to be filled
  SceneLoader(Scene &sceneToPopulate, int fbWidth, int fbHeight)
    : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0), m_fbWidth(fbWidth), m_fbHeight(fbHeight) {}

  // WILL FIX THIS LATER BUT I DON'T WANT TO MAKE MY VECTORS PUBLIC (WILL ADD LIKE A GETTER FUNCTION OR SOMETHING)
  void reserveCameras(size_t count) override
  {
    // makes sure the vector has enough space
    // m_targetScene.camera.reserve(count);
  }
  void reserveLights(size_t count) override
  {
    // m_targetScene.lights.reserve(count);
  }
  void reserveShapes(size_t count) override
  {
    // m_targetScene.shapes.reserve(count);
  }
  void reserveShaders(size_t count) override { numShaders = count; }
  void reserveTextures(size_t count) override { numTextures = count; }

  void setSceneParams(const SceneParams &sparams) override
  {
    std::cout << "Setting scene params." << std::endl;
  }

  void addCamera(const std::string &name, const std::string &type, const ISceneLoader::vec &pos, const ISceneLoader::vec &viewDir, float focalLength, float imagePlaneWidth) override
  {
    std::cout << "Creating camera: " << name << ", type:" << type << std::endl;
    if (type != "perspective") {
      std::cerr << "Error: Unsupported camera type: " << type << std::endl;
      return;
    }
    vec3 viewdir(viewDir.x, viewDir.y, viewDir.z);
    point3 origin(pos.x, pos.y, pos.z);

    auto cam = make_shared<PerspectiveCamera>(viewdir, origin, m_fbHeight, m_fbWidth, imagePlaneWidth, focalLength);

    m_targetScene.setCamera(cam);
  }

  void addPointLight(const ISceneLoader::vec &pos,
    const ISceneLoader::vec &intensity) override
  {

    auto light = make_shared<PointLight>(color(intensity.x, intensity.y, intensity.z), 1.0, point3(pos.x, pos.y, pos.z));

    m_targetScene.addLight(light);
  }
  void addAreaLight(const ISceneLoader::vec &pos,
    const ISceneLoader::vec &color,
    const ISceneLoader::vec &normal,
    float width,
    float length) override
  {
    std::cout << "Creating area light." << std::endl;
  }
  void addShader(const ISceneLoader::ShaderDesc &shaderDesc) override
  {
    if (shaderDesc.type == "Lambertian" || shaderDesc.type == "Diffuse") {
      color baseColor(shaderDesc.diffuse.data.x, shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z);
      auto shader = std::make_shared<LambertianShader>(baseColor);
      shaderMap.insert({ shaderDesc.name, shader });

    } else if (shaderDesc.type == "BlinnPhong" || shaderDesc.type == "Phong") {
      color baseColor(shaderDesc.diffuse.data.x, shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z);
      color specularColor(shaderDesc.specular.data.x, shaderDesc.specular.data.y, shaderDesc.specular.data.z);
      double shininess(shaderDesc.phongExp);
      auto shader = std::make_shared<BlinnPhongShader>(baseColor, specularColor, shininess);
      shaderMap.insert({ shaderDesc.name, shader });

    } else if (shaderDesc.type == "Mirror") {
      color baseColor(1, 1, 1);
      auto shader = std::make_shared<MirrorShader>(baseColor);
      shaderMap.insert({ shaderDesc.name, shader });
    } else {
      std::cerr << "Error: Unsupported shader type: " << shaderDesc.type << std::endl;
      return;
    }
  }

  void addShape(const ISceneLoader::ShapeDesc &shapeDesc) override
  {
    std::shared_ptr<Shader> shader;
    try {
      shader = shaderMap.at(shapeDesc.shaderNameReference);
    } catch (const std::out_of_range &) {
      std::cerr << "Error: Shape '" << shapeDesc.name << "' references unknown shader '"
                << shapeDesc.shaderNameReference << "'" << std::endl;
      return;
    }

    if (shapeDesc.type == "sphere") {
      point3 center(shapeDesc.center.x, shapeDesc.center.y, shapeDesc.center.z);
      auto sphere = std::make_shared<Sphere>(center, shapeDesc.radius, shader);
      m_targetScene.addShape(sphere);
    } else if (shapeDesc.type == "triangle") {
      vec3 v0(shapeDesc.v0.x, shapeDesc.v0.y, shapeDesc.v0.z);
      vec3 v1(shapeDesc.v1.x, shapeDesc.v1.y, shapeDesc.v1.z);
      vec3 v2(shapeDesc.v2.x, shapeDesc.v2.y, shapeDesc.v2.z);
      auto triangle = std::make_shared<Triangle>(v0, v1, v2, shader);
      m_targetScene.addShape(triangle);
    } else {
      std::cerr << "Error: Unsupported shape type: " << shapeDesc.type << std::endl;
      return;
    }
  }
  void addTexture(const std::string &type, const std::string &name, const std::string &sourceFile) override
  {
    std::cout << "Creating texture: type=" << type << ", name=" << name
              << ", sourceFile=" << sourceFile << std::endl;
  }

public:
  int numShaders;
  int numTextures;

private:
  int m_fbWidth;
  int m_fbHeight;
  std::unordered_map<std::string, std::shared_ptr<Shader>> shaderMap;
};