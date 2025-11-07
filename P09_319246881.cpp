
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture lamparaTexture;
Texture lampara2Texture;
Texture lampara3Texture;
Texture lampara4Texture;
Texture lampara5Texture;
Texture lampara6Texture;
Texture Juego_Pelota_Texture;
Texture PiedraTexture;


Model Juego_Pelota_M;
Model Piedra_M;
Model PiramideT_M;
Model PiramideS_M;
Model lampara_M;
Model Globo_M;
Model Chozas_M;
Model arbol_M;
Model BancaG_M;
Model BancaT_M;
Model CalendarioA_M;
Model Kiosco_M;
Model Pillar_M;
Model Ring_M;
Model PisoRing_M;
Model Cuerdas_M;
Model Coronas_M;
Model EstatuaLuchador_M;
Model MickeyC_M;
Model MickeyT_M;
Model MickeyBD_M;
Model MickeyBI_M;
Model MickeyPD_M;
Model MickeyPI_M;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights1[MAX_POINT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];
PointLight pointLights3[MAX_POINT_LIGHTS];

//Luces spot
SpotLight spotLights1[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci n de calculo de normales por promedio de v rtices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
	 -10.0f, 0.0f, -10.0f,   0.0f, 0.0f,      0.0f, -1.0f, 0.0f,
	 10.0f, 0.0f, -10.0f,  30.0f, 0.0f,      0.0f, -1.0f, 0.0f,
	-10.0f, 0.0f,  10.0f,   0.0f, 30.0f,     0.0f, -1.0f, 0.0f,
	 10.0f, 0.0f,  10.0f,  30.0f, 30.0f,     0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/pasto.png");
	pisoTexture.LoadTextureA();
	lamparaTexture = Texture("Textures/StreetLamp1.png");
	lamparaTexture.LoadTextureA();
	lampara2Texture = Texture("Textures/StreetLamp2BaseColor.png");
	lampara2Texture.LoadTextureA();
	lampara3Texture = Texture("Textures/StreetLamp3Metallic.png");
	lampara3Texture.LoadTextureA();
	lampara4Texture = Texture("Textures/StreetLamp4Normal.png");
	lampara4Texture.LoadTextureA();
	lampara5Texture = Texture("Textures/StreetLamp5Opacity.png");
	lampara5Texture.LoadTextureA();
	lampara6Texture = Texture("Textures/StreetLamp6Roughness.png");
	lampara6Texture.LoadTextureA();
	Juego_Pelota_Texture = Texture("Textures/Juego_Pelota.png");
	Juego_Pelota_Texture.LoadTextureA();
	PiedraTexture = Texture("Textures/piedra.png");
	PiedraTexture.LoadTextureA();


	//Modelos
	Juego_Pelota_M = Model();
	Juego_Pelota_M.LoadModel("Models/Juego_Pelota.obj");
	Piedra_M = Model();
	Piedra_M.LoadModel("Models/pelota.fbx");
	PiramideT_M = Model();
	PiramideT_M.LoadModel("Models/PiramideT.obj");
	PiramideS_M = Model();
	PiramideS_M.LoadModel("Models/PiramideSol.obj");
	lampara_M = Model();
	lampara_M.LoadModel("Models/lampara.fbx");
	Globo_M = Model();
	Globo_M.LoadModel("Models/globo.obj");
	Chozas_M = Model();
	Chozas_M.LoadModel("Models/Chozas.obj");
	arbol_M = Model();
	arbol_M.LoadModel("Models/arboles.obj");
	BancaG_M = Model ();
	BancaG_M.LoadModel("Models/banca.obj");
	BancaT_M = Model();
	BancaT_M.LoadModel("Models/Banca_Texturizada.obj");
	CalendarioA_M = Model();
	CalendarioA_M.LoadModel("Models/calendario_azteca.obj");
	Kiosco_M = Model();
	Kiosco_M.LoadModel("Models/kiosco.obj");
	Pillar_M = Model();
	Pillar_M.LoadModel("Models/pillar.obj");
	Ring_M= Model();
	Ring_M.LoadModel("Models/Ring.obj");
	PisoRing_M = Model();
	PisoRing_M.LoadModel("Models/PisoRing.obj");
	Cuerdas_M = Model();
	Cuerdas_M.LoadModel("Models/Cuerdas.obj");
	Coronas_M = Model();
	Coronas_M.LoadModel("Models/Coronas.obj");
	EstatuaLuchador_M = Model();
	EstatuaLuchador_M.LoadModel("Models/luchadores.obj");
	MickeyC_M = Model();
	MickeyC_M.LoadModel("Models/MickeyC.obj");
	MickeyT_M = Model();
	MickeyT_M.LoadModel("Models/MickeyT.obj");
	MickeyBD_M = Model();
	MickeyBD_M.LoadModel("Models/MickeyBD.obj");
	MickeyBI_M = Model();
	MickeyBI_M.LoadModel("Models/MickeyBI.obj");
	MickeyPD_M = Model();
	MickeyPD_M.LoadModel("Models/MickeyPD.obj");
	MickeyPI_M = Model();
	MickeyPI_M.LoadModel("Models/MickeyPI.obj");



	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//Luces

	//luz direccional, s lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f, // intensidad ambiental (radiacion de la luz), intensidad difusa
		0.0f, -1.0f, 0.0f);

	//luces puntuales (pointlight)
	unsigned int pointLightCount = 0; //contador de luces puntuales

	//Declaraci n de primer luz puntual
	//Luz blanca
	pointLights1[0] = PointLight(1.0f, 1.0f, 1.0f,
		1.0f, 2.0f,
		0.0f, 5.4f, 1.0f,
		0.1f, 0.7f, 0.05f);
	pointLightCount++;

	pointLights2[0] = PointLight(0.255f, 0.255f, 0.0f,
		0.4f, 3.0f,
		10.0f, -0.1f, -4.0,
		1.0f, 0.09f, 0.032f);
	pointLightCount++;

	pointLights3[0] = pointLights1[0];
	pointLights3[1] = pointLights2[0];


	// luces spotlight
	unsigned int spotLightCount = 0;

	////Capo
	//spotLights1[0] = SpotLight(0.899989, 0.2f, 0.965540f,
	//	1.0f, 2.0f,
	//	0.0f, 0.0f, 0.0f,
	//	-1.0f, 0.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	15.0f);
	//spotLightCount++;

	////Luz adelante
	//spotLights1[1] = SpotLight(0.998766f, 0.987878f, 0.0f,
	//	1.0f, 2.0f,
	//	0.0f, 0.0f, 0.0f,
	//	-1.0f, 0.0f, 0.0f,
	//	1.0f, 0.007f, 0.0002f,
	//	12.5f);
	//spotLightCount++;

	//// luz atras
	//spotLights1[2] = SpotLight(1.0f, 0.0f, 0.0f,
	//	1.0f, 2.0f,
	//	0.0f, 0.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	1.0f, 0.007f, 0.0002f,
	//	12.5f);
	//spotLightCount++;

	spotLights2[0] = spotLights1[0];
	spotLights2[1] = spotLights1[2];
	spotLights2[2] = spotLights1[1];

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	bool avanza = true;
	bool lightsA[2] = { false, false };
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//informaci n al shader de fuentes de iluminaci n
		shaderList[0].SetDirectionalLight(&mainLight);

		if (mainWindow.getActivar_tecla() == GLFW_KEY_1) {
			lightsA[0] = true;
		}
		if (mainWindow.getActivar_tecla() == GLFW_KEY_2) {
			lightsA[0] = false;
		}

		if (mainWindow.getActivar_tecla() == GLFW_KEY_3) {
			lightsA[1] = true;
		}
		if (mainWindow.getActivar_tecla() == GLFW_KEY_4) {
			lightsA[1] = false;
		}

		if (lightsA[0] && !lightsA[1]) {
			shaderList[0].SetPointLights(pointLights1, 1);
		}
		if (lightsA[1] && !lightsA[0]) {
			shaderList[0].SetPointLights(pointLights2, 1);
		}
		if (lightsA[0] && lightsA[1]) {
			shaderList[0].SetPointLights(pointLights3, pointLightCount);
		}
		if (!lightsA[0] && !lightsA[1]) {
			shaderList[0].SetPointLights(pointLights3, 0);
		}

		if (mainWindow.getActivar_tecla() == GLFW_KEY_Y) {
			shaderList[0].SetSpotLights(spotLights2, spotLightCount - 1);
			avanza = false;
		}
		else {
			shaderList[0].SetSpotLights(spotLights1, spotLightCount - 1);
			avanza = true;
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//Piramide Chichen
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(180.5f, -1.5f, 180.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.8f, 1.8f, 1.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego_Pelota_Texture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiramideT_M.RenderModel();

		//PiramideSol
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-180.0f, -1.0f, -180.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiramideS_M.RenderModel();

		//JuegoPelota
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(180.0f, -1.5f, -180.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(14.0f, 14.0f, 14.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego_Pelota_Texture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Juego_Pelota_M.RenderModel();

		//Globo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 50.5f, -180.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(14.0f, 14.0f, 14.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Globo_M.RenderModel();

		//Chozas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Chozas_M.RenderModel();

		//Arboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.2f, 4.2f, 2.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		arbol_M.RenderModel();

		//Banca 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.2f, 4.2f, 2.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BancaG_M.RenderModel();

		//BancaT
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.2f, 4.2f, 2.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BancaT_M.RenderModel();

		//Kiosco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.2f, 4.2f, 2.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Kiosco_M.RenderModel();

		//Pillar
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.2f, 4.2f, 2.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pillar_M.RenderModel();


		//Ring
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ring_M.RenderModel();


		//Model PisoRing
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PisoRing_M.RenderModel();
	
		//Model Cuerdas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuerdas_M.RenderModel();
		Model Cuerdas_M;

		//Model Coronas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coronas_M.RenderModel();
		Model Coronas_M;

		//Model EstatuaLuchador
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(45.0f, -0.5f, 60.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.2f, 4.2f, 2.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		EstatuaLuchador_M.RenderModel();
		Model EstatuaLuchador_M;


		//Calendario
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -0.5f, 180.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CalendarioA_M.RenderModel();
		
		//Modelo base (padre de todos los Mickey)
		glm::mat4 baseModel = glm::mat4(1.0);
		baseModel = glm::translate(baseModel, glm::vec3(0.0f, -0.5f, 60.0f));
		baseModel = glm::rotate(baseModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseModel = glm::scale(baseModel, glm::vec3(0.2f, 0.2f, 0.2f));

		//Model MickeyC
		glm::mat4 modelC = baseModel;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelC));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MickeyC_M.RenderModel();

		//Model MickeyT
		glm::mat4 modelT = baseModel;
		modelT = glm::translate(modelT, glm::vec3(0.0f, 0.0f, 0.0f)); // igual posición base
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelT));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MickeyT_M.RenderModel();

		//Model MickeyBD
		glm::mat4 modelBD = baseModel;
		modelBD = glm::translate(modelBD, glm::vec3(0.0f, 0.0f, 0.0f)); // mismo punto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBD));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MickeyBD_M.RenderModel();

		//Model MickeyBI
		glm::mat4 modelBI = baseModel;
		modelBI = glm::translate(modelBI, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBI));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MickeyBI_M.RenderModel();

		//Model MickeyPD
		glm::mat4 modelPD = baseModel;
		modelPD = glm::translate(modelPD, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPD));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MickeyPD_M.RenderModel();

		//Model MickeyPI
		glm::mat4 modelPI = baseModel;
		modelPI = glm::translate(modelPI, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPI));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MickeyPI_M.RenderModel();

		
		//Lampara
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 5.8f, 5.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.006f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamparaTexture.UseTexture();
		lampara2Texture.UseTexture();
		lampara3Texture.UseTexture();
		lampara4Texture.UseTexture();
		lampara5Texture.UseTexture();
		lampara6Texture.UseTexture();
		lampara_M.RenderModel();


		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}