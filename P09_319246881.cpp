
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
Texture AdvTime_FontTexture;
Texture Marco;
Texture Puerta;


Model Juego_Pelota_M;
Model Pelota_M;
Model Piedra_M;
Model Marco_M;
Model Letrero_M;
Model PuertaDerecha_M;
Model PuertaIzquierda_M;
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
Model PeachC_M;
Model PeachT_M;
Model PeachBD_M;
Model PeachBI_M;
Model PeachPD_M;
Model PeachPI_M;
Model FinnC_M;
Model FinnT_M;
Model FinnBD_M;
Model FinnBI_M;
Model FinnPD_M;
Model FinnPI_M;


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
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

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
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
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

	unsigned int AdvTimeIndices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	GLfloat AdvTimeVertices[] = {
		//   X      Y      Z     U       V        Nx    Ny    Nz
		-0.5f, 0.0f,  0.5f,   0.1f,   0.98f,   0.0f, -1.0f, 0.0f, // arriba dere  
		 0.5f, 0.0f,  0.5f,   0.01f,     0.98f,   0.0f, -1.0f, 0.0f, // arriba izq
		 0.5f, 0.0f, -0.5f,   0.01f,     0.9f,  0.0f, -1.0f, 0.0f, // abajo izq
		-0.5f, 0.0f, -0.5f,   0.1f,   0.9f,  0.0f, -1.0f, 0.0f  // abajo der
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

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(AdvTimeVertices, AdvTimeIndices, 32, 6);
	meshList.push_back(obj5);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void setLetterUV(float* vertices, int col, int row)
{
	float uStep = 1.0f / 9.0f;  // 9 columnas
	float vStep = 1.0f / 3.0f;  // 3 filas
	float u0 = col * uStep;
	float v0 = 1.0f - (row + 1) * vStep;
	float u1 = u0 + uStep;
	float v1 = v0 + vStep;

	// Actualiza las coordenadas UV del plano
	vertices[3] = u0; vertices[4] = v1;  // arriba izq
	vertices[11] = u1; vertices[12] = v1;  // arriba der
	vertices[19] = u1; vertices[20] = v0;  // abajo der
	vertices[27] = u0; vertices[28] = v0;  // abajo izq
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);
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
	AdvTime_FontTexture = Texture("Textures/AdvTime_Font.png");
	AdvTime_FontTexture.LoadTextureA();
	Marco = Texture("Textures/Corrugated_Metal_Sheet_teendf3q_1K_BaseColor.jpg");
	Marco.LoadTextureA();
	Puerta = Texture("Textures/Wooden_Log_Wall_udlmecoew_1K_BaseColor.jpg");
	Puerta.LoadTextureA();



	//Modelos
	Juego_Pelota_M = Model();
	Juego_Pelota_M.LoadModel("Models/Juego_Pelota.obj");
	Pelota_M = Model();
	Pelota_M.LoadModel("Models/pelota.obj");
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
	BancaG_M = Model();
	BancaG_M.LoadModel("Models/banca.obj");
	BancaT_M = Model();
	BancaT_M.LoadModel("Models/Banca_Texturizada.obj");
	CalendarioA_M = Model();
	CalendarioA_M.LoadModel("Models/calendario_azteca.obj");
	Kiosco_M = Model();
	Kiosco_M.LoadModel("Models/kiosco.obj");
	Pillar_M = Model();
	Pillar_M.LoadModel("Models/pillar.obj");
	Ring_M = Model();
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
	PeachC_M = Model();
	PeachC_M.LoadModel("Models/PeachC.obj");
	PeachT_M = Model();
	PeachT_M.LoadModel("Models/PeachT.obj");
	PeachBD_M = Model();
	PeachBD_M.LoadModel("Models/PeachBD.obj");
	PeachBI_M = Model();
	PeachBI_M.LoadModel("Models/PeachBI.obj");
	PeachPD_M = Model();
	PeachPD_M.LoadModel("Models/PeachPD.obj");
	PeachPI_M = Model();
	PeachPI_M.LoadModel("Models/PeachPI.obj");
	FinnC_M = Model();
	FinnC_M.LoadModel("Models/FinnC.obj");
	FinnT_M = Model();
	FinnT_M.LoadModel("Models/FinnT.obj");
	FinnBD_M = Model();
	FinnBD_M.LoadModel("Models/FinnBD.obj");
	FinnBI_M = Model();
	FinnBI_M.LoadModel("Models/FinnBI.obj");
	FinnPD_M = Model();
	FinnPD_M.LoadModel("Models/FinnPD.obj");
	FinnPI_M = Model();
	FinnPI_M.LoadModel("Models/FinnPI.obj");
	Marco_M = Model();
	Marco_M.LoadModel("Models/Marco.f bx");
	Letrero_M = Model();
	Letrero_M.LoadModel("Models/Letrero.fbx");
	PuertaDerecha_M = Model();
	PuertaDerecha_M.LoadModel("Models/PuertaDerecha.fbx");
	PuertaIzquierda_M = Model();
	PuertaIzquierda_M.LoadModel("Models/PuertaIzquierda.fbx");

	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
	float toffsetletraU = 0.0f;
	float toffsetletraV = 0.0f;


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

	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	std::vector<glm::vec2> offsets = {
	glm::vec2(0.65f, 0.57f), // P
	glm::vec2(0.88f, 0.57f), // R
	glm::vec2(0.57f, 0.56f), // O
	glm::vec2(0.651f,0.46f), // Y
	glm::vec2(0.45f, 0.67f), // E
	glm::vec2(0.23f, 0.67f), // C
	glm::vec2(0.11f, 0.46f), // T
	glm::vec2(0.57f, 0.56f), // O
	glm::vec2(0.23f, 0.67f), // C
	glm::vec2(0.655f,0.67f), // G
	glm::vec2(0.45f, 0.67f), // E
	glm::vec2(0.86f, 0.67f), // I
	glm::vec2(0.77f, 0.67f), // H
	glm::vec2(0.23f, 0.67f)  // C
	};


	static float tiempoAcumulado = 0.0f;
	static int indiceInicio = 0;
	int letrasVisibles = 4;
	// VELOCIDAD DEL LETRERO CORREGIDA
	float intervaloCambio = 0.7f;
	glm::vec3 basePos(-12.0f, 2.5f, 9.5f);
	float separacion = 1.5f;
	glm::vec3 escalaLetras(1.5f, 2.0f, 2.0f);

	bool abierta = false;
	float ang = 0.0f;
	float vel = 90.0f;
	static bool teclaOPresionada = false;

	bool puertaDerechaAbierta = false;
	bool puertaDerechaAnimando = false;
	bool teclaPPresionada = false;

	float progresoAnim = 0.0f;
	float duracionFase = 1.0f;
	int fase = 0;
	glm::vec3 puertaDerechaPos(0.0f);

	// GRAVEDAD CORREGIDA
	float gravedad = -45.0f;
	float rotacionDado = 0.0f;
	glm::vec3 rotDadoActual(0.0f);
	glm::vec3 rotVelocidad(180.0f, 240.0f, 200.0f);

	// Variables de Animación de la Pelota 
	bool pelotaSaltando = false;
	bool teclaJPresionada = false;
	float pelotaVelocidadY = 0.0f;
	// ALTURA BASE 
	float pelotaPosBaseY = -0.5f;
	// FUERZA DE SALTO 
	float fuerzaSalto = 30.0f;



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

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		tiempoAcumulado += deltaTime;
		if (tiempoAcumulado >= intervaloCambio) {
			tiempoAcumulado = 0.0f;
			indiceInicio++;
			if (indiceInicio > (int)offsets.size() - letrasVisibles)
				indiceInicio = 0;
		}

		// Abrir/cerrar con tecla O 
		if (mainWindow.getsKeys()[GLFW_KEY_O]) {
			if (!teclaOPresionada) {
				abierta = !abierta;
				teclaOPresionada = true;
			}
		}
		else {
			teclaOPresionada = false;
		}

		// Animación 
		float targetAng = abierta ? -90.0f : 0.0f;
		if (fabs(ang - targetAng) > 0.1f) {

			float step = vel * deltaTime / 10;
			if (ang < targetAng) ang = std::min(ang + step, targetAng);
			else ang = std::max(ang - step, targetAng);
		}


		// Animación de Puerta Derecha con tecla P
		if (mainWindow.getsKeys()[GLFW_KEY_P]) {
			if (!teclaPPresionada && !puertaDerechaAnimando) {
				puertaDerechaAnimando = true;
				teclaPPresionada = true;
				if (!puertaDerechaAbierta) {
					fase = 1;
				}
				else {
					fase = 3;
				}
				progresoAnim = 0.0f;
			}
		}
		else {
			teclaPPresionada = false;
		}

		// Lógica de movimiento de la puerta 
		if (puertaDerechaAnimando) {
			progresoAnim += deltaTime / 20;
			float t = progresoAnim / duracionFase;
			if (fase == 1) {
				puertaDerechaPos.z = glm::min(t, 1.0f) * 0.5f;
				if (t >= 1.0f) { fase = 2; progresoAnim = 0.0f; }
			}
			else if (fase == 2) {
				puertaDerechaPos = glm::vec3(glm::min(t, 1.0f) * 4.0f, 0.0f, 1.0f);
				if (t >= 1.0f) {
					puertaDerechaAnimando = false;
					puertaDerechaAbierta = true;
					fase = 0;
				}
			}
			else if (fase == 3) {
				puertaDerechaPos = glm::vec3((1.0f - glm::min(t, 1.0f)) * 4.0f, 0.0f, 1.0f);
				if (t >= 1.0f) { fase = 4; progresoAnim = 0.0f; }
			}
			else if (fase == 4) {
				puertaDerechaPos.z = (1.0f - glm::min(t, 1.0f)) * 0.5f;
				if (t >= 1.0f) {
					puertaDerechaAnimando = false;
					puertaDerechaAbierta = false;
					fase = 0;
				}
			}
		}

		// Salto de Pelota (Lógica de Tecla)
		if (mainWindow.getsKeys()[GLFW_KEY_J]) {
			if (!teclaJPresionada && !pelotaSaltando) {
				teclaJPresionada = true;
				pelotaSaltando = true;
				pelotaVelocidadY = fuerzaSalto;
			}
		}
		else {
			teclaJPresionada = false;
		}

		// Salto de Pelota
		if (pelotaSaltando) {
			// Aplicar la gravedad 
			pelotaVelocidadY += gravedad * deltaTime;
			// Mover la pelota
			pelotaPosBaseY += pelotaVelocidadY * deltaTime;

			// Comprobar si tocó el suelo
			if (pelotaPosBaseY <= -0.5f) {
				pelotaPosBaseY = -0.5f;
				pelotaSaltando = false;
				pelotaVelocidadY = 0.0f;
			}
		}

		/*
		* Arco con letrero
		*/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.5f, -2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Marco.UseTexture();
		Marco_M.RenderModel(); // modelo de arco
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		// Error de sintaxis original corregido
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Letrero_M.RenderModel(); // letrero blanco


		glm::mat4 letraModel = glm::mat4(1.0f);
		letraModel = glm::rotate(letraModel, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		AdvTime_FontTexture.UseTexture();

		for (int i = 0; i < letrasVisibles; i++) {

			int idx = (indiceInicio + i) % offsets.size();

			glm::vec2 toffset = offsets[idx];
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

			glm::mat4 letraModel = glm::mat4(1.0f);
			letraModel = glm::rotate(letraModel, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			float startX = basePos.x + (letrasVisibles - 1) * separacion;
			letraModel = glm::translate(letraModel,
				glm::vec3(startX - i * separacion, basePos.y, basePos.z));

			letraModel = glm::scale(letraModel, escalaLetras);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(letraModel));

			meshList[4]->RenderMesh();
		}

		//Puertas
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.3f, 0.0f, 4.7f));
		model = glm::rotate(model, -ang * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Puerta.UseTexture();
		PuertaIzquierda_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(puertaDerechaPos.x, puertaDerechaPos.z, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Puerta.UseTexture();
		PuertaDerecha_M.RenderModel();

		// Renderizar Juego Pelota 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(180.0f, -1.5f, -180.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Juego_Pelota_Texture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Juego_Pelota_M.RenderModel();

		// Renderizar Pelota 

		// CALCULAR POSICIÓN
		float pelotaBaseX = 180.5f; // Centro del pasillo 
		float pelotaBaseZ = -180.0f;  // Centro del pasillo 

		// Parámetros de animación
		float pelotaAmplitud = 25.0f; // Límite del va y ven
		float pelotaVelocidad = 0.8f;
		float pelotaOffsetZ = glm::sin(glfwGetTime() * pelotaVelocidad) * pelotaAmplitud;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(pelotaBaseX + pelotaOffsetZ, pelotaPosBaseY, pelotaBaseZ));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));

		// RENDERIZAR EL MODELO
		PiedraTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Piedra_M.RenderModel();
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
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
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

		//Modelo base (padre de todos los Peach)
		glm::mat4 baseModelPeach = glm::mat4(1.0);
		baseModelPeach = glm::translate(baseModelPeach, glm::vec3(0.0f, -0.5f, 60.0f));
		baseModelPeach = glm::rotate(baseModelPeach, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseModelPeach = glm::scale(baseModelPeach, glm::vec3(0.2f, 0.2f, 0.2f));

		//Model PeachC
		glm::mat4 modelCPeach = baseModelPeach;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCPeach));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachC_M.RenderModel();

		//Model PeachT
		glm::mat4 modelTPeach = baseModelPeach;
		modelTPeach = glm::translate(modelTPeach, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelTPeach));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachT_M.RenderModel();

		//Model PeachBD
		glm::mat4 modelBDPeach = baseModelPeach;
		modelBDPeach = glm::translate(modelBDPeach, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBDPeach));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachBD_M.RenderModel();

		//Model PeachBI
		glm::mat4 modelBIPeach = baseModelPeach;
		modelBIPeach = glm::translate(modelBIPeach, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBIPeach));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachBI_M.RenderModel();

		//Model PeachPD
		glm::mat4 modelPDPeach = baseModelPeach;
		modelPDPeach = glm::translate(modelPDPeach, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPDPeach));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachPD_M.RenderModel();

		//Model PeachPI
		glm::mat4 modelPIPeach = baseModelPeach;
		modelPIPeach = glm::translate(modelPIPeach, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPIPeach));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PeachPI_M.RenderModel();

		//Modelo base (padre de todos los Finn)
		glm::mat4 baseModelFinn = glm::mat4(1.0);
		baseModelFinn = glm::translate(baseModelFinn, glm::vec3(0.0f, -0.5f, 10.0f));
		baseModelFinn = glm::rotate(baseModelFinn, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseModelFinn = glm::scale(baseModelFinn, glm::vec3(2.0f, 2.0f, 2.0f));

		//Model FinnC
		glm::mat4 modelCFinn = baseModelFinn;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCFinn));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FinnC_M.RenderModel();

		//Model FinnT
		glm::mat4 modelTFinn = baseModelFinn;
		modelTFinn = glm::translate(modelTFinn, glm::vec3(0.0f, 0.0f, 0.0f)); // igual posición base
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelTFinn));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FinnT_M.RenderModel();

		//Model FinnBD
		glm::mat4 modelBDFinn = baseModelFinn;
		modelBDFinn = glm::translate(modelBDFinn, glm::vec3(0.0f, 0.0f, 0.0f)); // mismo punto
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBDFinn));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FinnBD_M.RenderModel();

		//Model FinnBI
		glm::mat4 modelBIFinn = baseModelFinn;
		modelBIFinn = glm::translate(modelBIFinn, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBIFinn));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FinnBI_M.RenderModel();

		//Model FinnPD
		glm::mat4 modelPDFinn = baseModelFinn;
		modelPDFinn = glm::translate(modelPDFinn, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPDFinn));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FinnPD_M.RenderModel();

		//Model FinnPI
		glm::mat4 modelPIFinn = baseModelFinn;
		modelPIFinn = glm::translate(modelPIFinn, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPIFinn));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FinnPI_M.RenderModel();

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