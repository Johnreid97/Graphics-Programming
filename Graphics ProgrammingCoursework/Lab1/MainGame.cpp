#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform mesh1Transform;
Transform mesh2Transform;
Transform mesh3Transform;
Transform mesh4Transform;
Transform mesh5Transform;
Transform mesh6Transform;

MainGame::MainGame()
{
	gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Mesh* mesh4();
	Mesh* mesh5();
	Mesh* mesh6();
	Shader* shaderRimToon();
	Shader* shaderFog();
	Shader* shaderExploding();
	Shader* shaderHairy();
	Shader* shaderPhong();
	Shader* shaderBlinnPhong();
	Shader* shaderGouraud();
	Shader* shaderGeneric();
	
}

MainGame::~MainGame() 
{
}

void MainGame::Start()
{
	InitialiseSystems(); 
	GameLoop();
}

void MainGame::InitialiseSystems()
{
	gameDisplay.initialiseDisplay(); 

	shaderRimToon.initialise("..\\res\\shaderRimToon.vert", "..\\res\\shaderRimToon.frag");
	shaderFog.initialise("..\\res\\shaderFog.vert", "..\\res\\shaderFog.frag");
	shaderPhong.initialise("..\\res\\shaderPhong.vert", "..\\res\\shaderPhong.frag");
	shaderBlinnPhong.initialise("..\\res\\shaderBlinnPhong.vert", "..\\res\\shaderBlinnPhong.frag");
	shaderGouraud.initialise("..\\res\\shaderGouraud.vert", "..\\res\\shaderGouraud.frag");
	shaderGeneric.initialise("..\\res\\shaderGeneric.vert", "..\\res\\shaderGeneric.frag");
	shaderExploding.initialise("..\\res\\shaderExploding.vert", "..\\res\\shaderExploding.frag", "..\\res\\shaderExploding.geom");
	shaderHairy.initialise("..\\res\\shaderHairy.vert", "..\\res\\shaderHairy.frag", "..\\res\\shaderHairy.geom");

	mesh1.loadModel("..\\res\\monkey3.obj");
	mesh2.loadModel("..\\res\\A2.obj");
	mesh3.loadModel("..\\res\\SpaceShip.obj");
	mesh4.loadModel("..\\res\\monkey3.obj");
    mesh5.loadModel("..\\res\\monkey3.obj");
	mesh6.loadModel("..\\res\\monkey3.obj");

	myCamera.initialiseCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)gameDisplay.getWidth()/gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void MainGame::GameLoop()
{
	while (gameState != GameState::EXIT)
	{
		PlayerInput();
		DrawObjectsToScreen();
	}
}

void MainGame::PlayerInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
		}
	}
	
}


void MainGame::setRimToon()
{
	shaderRimToon.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shaderRimToon.setMat4("u_vm", myCamera.GetView());
	shaderRimToon.setMat4("u_pm", myCamera.GetProjection());
	shaderRimToon.setMat4("v_pos", mesh2Transform.GetModel());


}

void MainGame::SetFog(float zPos)
{
	shaderFog.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));

	shaderFog.setMat4("u_vm", myCamera.GetView());
	shaderFog.setMat4("u_pm", myCamera.GetProjection());

	shaderFog.setVec3("fogColor", glm::vec3(0.2, 0.2, 0.2));
	shaderFog.setFloat("minDist", -5.0f);
	shaderFog.setFloat("maxDist", 5.0f);

	shaderFog.setFloat("zpos", zPos);
}

void MainGame::SetExploding()
{

	shaderExploding.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shaderExploding.setMat4("u_vm", myCamera.GetView());
	shaderExploding.setMat4("u_pm", myCamera.GetProjection());
	shaderExploding.setMat4("v_pos", mesh3Transform.GetModel());
	
	shaderExploding.setFloat("time",  0.1f + counter);
}

void MainGame::SetHairy()
{

	shaderHairy.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shaderHairy.setMat4("u_vm", myCamera.GetView());
	shaderHairy.setMat4("u_pm", myCamera.GetProjection());
	shaderHairy.setMat4("v_pos", mesh3Transform.GetModel());

}

void MainGame::SetGouraud()
{
	//shaderPhong.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shaderGouraud.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderGouraud.setVec3("lightPos", lightPos);
	shaderGouraud.setVec3("viewPos", myCamera.getPos());
}

void MainGame::SetPhong()
{
	shaderPhong.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shaderPhong.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderPhong.setVec3("lightPos", lightPos);
	shaderPhong.setVec3("viewPos", myCamera.getPos());
}

void MainGame::SetBlinnPhong()
{
	shaderBlinnPhong.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shaderBlinnPhong.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderBlinnPhong.setVec3("lightPos", lightPos);
	shaderBlinnPhong.setVec3("viewPos", myCamera.getPos());
}

void MainGame::FogMisc()
{
	mesh1Transform.SetPos(glm::vec3(sinf(counter), 0.5, -sinf(counter) * 5));
	mesh1Transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	mesh1Transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shaderFog.Bind();
	SetFog(mesh1.getSpherePosition().z + 5);
	shaderFog.Update(mesh1Transform, myCamera);
	texture.Bind(0);
	mesh1.create();
	mesh1.sphereDataUpdate(*mesh1Transform.GetPos(), 0.62f);
}

void MainGame::RimToonMisc()
{
	mesh2Transform.SetPos(glm::vec3(3, -1.0, 3));
	mesh2Transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	mesh2Transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shaderRimToon.Bind();
	setRimToon();
	shaderRimToon.Update(mesh2Transform, myCamera);
	mesh2.create();
	mesh2.sphereDataUpdate(*mesh2Transform.GetPos(), 0.62f);
}

void MainGame::ExplodingMisc()
{
	mesh3Transform.SetPos(glm::vec3(3, -1, 0));
	mesh3Transform.SetRot(glm::vec3(0.0, 0, 0.0));
	mesh3Transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shaderExploding.Bind();
	SetExploding();
	shaderExploding.Update(mesh3Transform, myCamera);
	mesh3.create();
	mesh3.sphereDataUpdate(*mesh3Transform.GetPos(), 0.62f);
}

void MainGame::PhongMisc()
{
	mesh4Transform.SetPos(glm::vec3(-3.0, -1.0, 0));
	mesh4Transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	mesh4Transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	/*shaderGouraud.Bind();
	SetGouraud();
	shaderGouraud.Update(mesh4Transform, myCamera);*/
	shaderPhong.Bind();
	SetPhong();
	shaderPhong.Update(mesh4Transform, myCamera);
	mesh4.create();
	mesh4.sphereDataUpdate(*mesh4Transform.GetPos(), 0.62f);
}

void MainGame::GenericMisc()
{
	mesh5Transform.SetPos(lightPos);
	mesh5Transform.SetRot(glm::vec3(0.0, 0, 0.0));
	mesh5Transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shaderGeneric.Bind();
	shaderGeneric.Update(mesh5Transform, myCamera);
	mesh5.create();
	mesh5.sphereDataUpdate(*mesh5Transform.GetPos(), 0.62f);
}


void MainGame::BlinnPhonggMisc()
{
	mesh6Transform.SetPos(glm::vec3(-3.0, 1.0, 0));
	mesh6Transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	mesh6Transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	/*shaderGouraud.Bind();
	SetGouraud();
	shaderGouraud.Update(mesh4Transform, myCamera);*/
	shaderBlinnPhong.Bind();
	SetBlinnPhong();
	shaderBlinnPhong.Update(mesh6Transform, myCamera);
	mesh6.create();
	mesh6.sphereDataUpdate(*mesh6Transform.GetPos(), 0.62f);
}
void MainGame::DrawObjectsToScreen()
{
	gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	lightPos = glm::vec3(-1.0f, 1.0f, -sinf(counter) * 5);

	FogMisc();
	RimToonMisc();
	ExplodingMisc();
	PhongMisc();
	GenericMisc();
	BlinnPhonggMisc();

	counter = counter + 0.01f;


	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();


	gameDisplay.changeBuffer();
} 