#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Start();

private:

	void InitialiseSystems();
	void PlayerInput();
	void GameLoop();
	void DrawObjectsToScreen();

	void FogMisc();
	void SetFog(float zPos);

	void RimToonMisc();
	void setRimToon();

	void SetExploding();
	void ExplodingMisc();

	void SetHairy();
	void HairyMisc();

	void SetPhong();
	void PhongMisc();

	void SetGouraud();
	void GenericMisc();

	void SetBlinnPhong();
	void BlinnPhonggMisc();


	Display gameDisplay;
	GameState gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Mesh mesh4;
	Mesh mesh5;
	Mesh mesh6;
	Texture texture;
	Texture texture1;
	Overlay overlay;
	Shader shaderPass;
	Shader shaderBlur;
	Shader shaderPhong;
	Shader shaderFog;
	Shader shaderRimToon;
	Shader shaderExploding;
	Shader shaderHairy;
	Shader shaderGeneric;
	Shader shaderGouraud;
	Shader shaderBlinnPhong;

	glm::mat4 modelView;
	glm::vec3 lightPos;


	Camera myCamera;
	Audio audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;
};

