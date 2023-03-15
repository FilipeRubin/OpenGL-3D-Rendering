#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.hpp"
#include "Shader/PointLight.hpp"
#include "Shader/PostProcessing.hpp"
#include "Shader/Class/PhongShading.hpp"
#include "Shader/Material/PhongMaterial.hpp"
#include "Render/Skybox.hpp"
#include "Render/Primitive/Plane.hpp"
#include "Render/Primitive/Cube.hpp"
#include "Render/Primitive/Pyramid.hpp"
#include "Render/Model/OBJ.hpp"
#include "Render/RenderingList.hpp"
#include "Game/Player/FreeCamera.hpp"
#include <stb/stb_image.h>

float deltaTime = 0.0f;
int windowSizeX = 800;
int windowSizeY = 600;

static void ProcessDeltaTime()
{
	static float lastFrame = 0.0f;
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

static glm::mat4 GetProjectionMatrix(GLFWwindow* pWindow)
{
	return glm::perspective(glm::radians(80.0f), (float)windowSizeX / (float)windowSizeY, 0.1f, 25.0f);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	windowSizeX = width;
	windowSizeY = height;
	glViewport(0, 0, windowSizeX, windowSizeY);
}

int main()
{
	glfwInit();

	GLFWwindow* pWindow = glfwCreateWindow(windowSizeX, windowSizeY, "OpenGL Application", nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(pWindow, window_size_callback);

	gladLoadGL();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.04f, 0.05f, 0.09f, 1.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	glm::mat4 projection(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 world(1.0f);
	glm::vec3 camPos = glm::vec3();

	PhongShading phong = PhongShading("Shaders\\Phong\\vertexShader.glsl", "Shaders\\Phong\\fragmentShader.glsl", projection, view, camPos);

	PointLight::Init(phong.GetProgram(), &projection, &view);

	phong.Use();
	phong.SetProjection(projection);
	phong.SetView(view);
	phong.SetWorld(world);
	phong.SetDirLightAmbient({ 0.50f, 0.65f, 0.70f });
	phong.SetDirLightDiffuse({ 0.92f, 0.98f, 0.99f });
	phong.SetDirLightSpecular({ 1.0f, 1.0f, 1.0f });
	phong.SetDirLightDirection({0.434987f, -0.361615f, 0.824633f});
	phong.SetFogStart(5.0f);
	phong.SetFogEnd(20.0f);
	phong.SetFogColor({ 0.75f, 0.95f, 0.99f });

	PointLight::SetFog(15.0f, 25.0f, glm::vec3(0.74f, 0.75f, 0.70f));
	PointLight::GetLight(0).LightInfo({ 0.0f, 2.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 1.0f, 0.35f, 0.44f);

	FreeCamera freeCamera = FreeCamera(pWindow, view, camPos);

	Plane plane = Plane(10.0f, 10.0f, true);
	plane.SetTranslation(0.0f, 0.0f, 0.0f);
	plane.GetMaterial().SetTextures("Assets\\Textures\\floor_diff.jpg", "Assets\\Textures\\floor_spec.jpg");

	Cube cube = Cube(1.0f, 1.0f, 1.0f);
	cube.GetMaterial().SetTextures("Assets\\Textures\\wooden_crate_diff.png", "Assets\\Textures\\wooden_crate_spec.png");
	cube.SetTranslation(-2.5f, 0.5f, 2.5f);

	Pyramid pyramid = Pyramid(1.0f, 2.0f);
	pyramid.GetMaterial().SetTextures("Assets\\Textures\\checkertexture.png");
	pyramid.SetTranslation(2.5f, 0.0f, 2.5f);

	Pyramid pyramid2 = Pyramid(2.0f, 5.0f);
	pyramid2.GetMaterial().SetTextures("Assets\\Textures\\checkertexture.png");
	pyramid2.SetTranslation(-2.5f, 0.0f, -2.5f);

	OBJ x = OBJ("Assets\\Models\\x.obj");
	x.GetMaterial().SetTextures("Assets\\Textures\\x_diff.png", "Assets\\Textures\\x_spec.png", "Assets\\Textures\\x_emis.png");
	x.SetTranslation(2.5f, 0.0f, -2.5f);

	RenderingList rl = RenderingList(phong.GetProgram());
	rl.Add(cube);
	rl.Add(plane);
	rl.Add(x);

	RenderingList rlTransparency = RenderingList(phong.GetProgram());
	rlTransparency.Add(pyramid);
	rlTransparency.Add(pyramid2);

	Skybox skybox = Skybox(
		"Assets\\Textures\\Skybox\\sides.png", 
		"Assets\\Textures\\Skybox\\sides.png", 
		"Assets\\Textures\\Skybox\\top.png", 
		"Assets\\Textures\\Skybox\\bottom.png", 
		"Assets\\Textures\\Skybox\\sides.png", 
		"Assets\\Textures\\Skybox\\sides.png", projection, view);
	
	PostProcessing postProcessing = PostProcessing(pWindow, "Shaders\\PostProcessing\\vertexShader.glsl", "Shaders\\PostProcessing\\fragmentShader.glsl");

	while (!glfwWindowShouldClose(pWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Process
		{
			ProcessDeltaTime();

			freeCamera.Process(); // This process the "view" matrix
			projection = GetProjectionMatrix(pWindow);
			phong.Process();
			x.SetRotationY(glfwGetTime());
			postProcessing.Process();
		}

		PointLight::Render();

		rl.Render();
		skybox.Render();
		rlTransparency.Render();
		postProcessing.Render();

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	PointLight::Cleanup();
	glfwDestroyWindow(pWindow);
	glfwTerminate();
	return 0;
}