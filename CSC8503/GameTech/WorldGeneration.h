#pragma once
#include "CourseGame.h"
#include "../../Common/TextureLoader.h"
#include "../CSC8503Common/PositionConstraint.h"

using namespace NCL;
using namespace CSC8503;

class WorldGeneration
{
public:
	WorldGeneration(GameWorld* world)
	{
		this->world = world;
		InitialiseAssets();
	}
	~WorldGeneration();



protected:

	GameWorld* world;

	//Coursework Meshes

	OGLMesh* capsuleMesh   = nullptr;
	OGLMesh* cubeMesh      = nullptr;
	OGLMesh* sphereMesh    = nullptr;
	OGLMesh* charMeshA     = nullptr;
	OGLMesh* charMeshB     = nullptr;
	OGLMesh* enemyMesh     = nullptr;
	OGLMesh* bonusMesh     = nullptr;

	OGLShader* basicShader = nullptr;



	OGLTexture* basicTex   = nullptr;
	OGLTexture* playerTex  = nullptr;
	OGLTexture* blankTex   = nullptr;
	OGLTexture* lavaTex    = nullptr;

	const Vector3 borderPosition[4] = { Vector3(-180,-37.4,400),
										Vector3(180,-37.4,400),
										Vector3(0,-37.4,-120),
										Vector3(0,-37.4,900) };

	const Vector3 borderScale[4] = { Vector3(50,85,500),
									 Vector3(50,85,500),
									 Vector3(230,85,20),
									 Vector3(230,85,20) };


	const Vector3 obstaclePosition[10] = {   Vector3(26   ,5  ,60),
											 Vector3(-26  ,5  ,60),
											 Vector3(60   ,5  ,120),
											 Vector3(0    ,5  ,120),
											 Vector3(-60  ,5  ,120),
											 Vector3(26   ,5  ,180),
											 Vector3(-26  ,5  ,180),
											 Vector3(60   ,5  ,240),
											 Vector3(0    ,5  ,240),
											 Vector3(-60  ,5  ,240), };


	const Vector3 StateMachineWallPosition[4] = { Vector3(-40,0,550),
												  Vector3(40,0,550),
												  Vector3(-40,0,640),
												  Vector3(40,0,640) };





	void InitialiseAssets();
	void InitWorld();

	// Gameobjs
	GameObject* AddFloorToWorld(const Vector3& position, const Vector3& scale);
	GameObject* AddCubeToWorld(const Vector3& position, Vector3 dimensions,	float inverseMass, 
								OGLTexture* tex,  Vector4 color = Vector4(1, 1, 1, 1));

	GameObject* AddOBBToWorld(const Vector3& position, Vector3 dimensions,Vector3 eulerAngles, float inverseMass,
									OGLTexture* tex, Vector4 color = Vector4(1, 1, 1, 1));

	//TODO
	GameObject* AddSphereToWorld(const Vector3& position, float radius, float inverseMass = 10.0f);
	GameObject* AddCapsuleToWorld(const Vector3& position, float halfHeight, float radius, float inverseMass = 10.0f);
	GameObject* AddPlayerToWorld(const Vector3& position);
	GameObject* AddEnemyToWorld(const Vector3& position);
	GameObject* AddBonusToWorld(const Vector3& position);

	StateGameObject* AddStateObjectToWorld(const Vector3& position);
	StateGameObject* testStateObject;

	GameObject* InitPlayer();

	void BridgeConstraintTest();


};

