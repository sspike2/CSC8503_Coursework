#include "WorldGeneration.h"

/*
Each of the little demo scenarios used in the game uses the same 2 meshes,
and the same texture and shader. There's no need to ever load in anything else
for this module, even in the coursework, but you can add it if you like!
*/

void WorldGeneration::InitialiseAssets()
{
	auto loadFunc = [](const string& name, OGLMesh** into)
	{
		*into = new OGLMesh(name);
		(*into)->SetPrimitiveType(GeometryPrimitive::Triangles);
		(*into)->UploadToGPU();
	};

	loadFunc("cube.msh", &cubeMesh);
	loadFunc("sphere.msh", &sphereMesh);
	loadFunc("Male1.msh", &charMeshA);
	loadFunc("courier.msh", &charMeshB);
	loadFunc("security.msh", &enemyMesh);
	loadFunc("coin.msh", &bonusMesh);
	loadFunc("capsule.msh", &capsuleMesh);

	basicTex = (OGLTexture*)TextureLoader::LoadAPITexture("checkerboard.png");
	playerTex = (OGLTexture*)TextureLoader::LoadAPITexture("test.png");
	blankTex = (OGLTexture*)TextureLoader::LoadAPITexture("blank.png");
	lavaTex = (OGLTexture*)TextureLoader::LoadAPITexture("Lava.png");


	basicShader = new OGLShader("GameTechVert.glsl", "GameTechFrag.glsl");

	InitWorld();
}

WorldGeneration::~WorldGeneration()
{
	delete cubeMesh;
	delete sphereMesh;
	delete charMeshA;
	delete charMeshB;
	delete enemyMesh;
	delete bonusMesh;

	delete basicTex;
	delete basicShader;
	delete blankTex;
	delete lavaTex;

}



void WorldGeneration::InitWorld()
{
	AddFloorToWorld(Vector3(0, -4.9, 400), Vector3(200, 5, 500));

	//borders
	for (int i = 0; i < 4; i++)
	{
		AddCubeToWorld(borderPosition[i], borderScale[i], 0,
			blankTex, Vector4(.2f, .2f, .2f, 1));
	}

	//OBB obstacles
	for (int i = 0; i < 10; i++)
	{
		AddOBBToWorld(obstaclePosition[i], Vector3(5, 5, 5), Vector3(0, 45, 0), 0,
			blankTex, Vector4(.3f, .3f, .3f, 1));
	}

	//LAVA
	GameObject* lava1 = AddCubeToWorld(Vector3(-90, -3.4f, 60), Vector3(65, 4, 7),
		0, lavaTex);
	lava1->layer = Layer::Lava;

	GameObject* lava2 = AddCubeToWorld(Vector3(90, -3.4f, 60), Vector3(65, 4, 7),
		0, lavaTex);
	lava2->layer = Layer::Lava;


	//Sticky
	GameObject* sticky1 = AddCubeToWorld(Vector3(0, -3.4f, 120), Vector3(60, 4, 7),
		0, blankTex, Vector4(1, 1, 0, 1));
	sticky1->layer = Layer::Sticky;

	GameObject* sticky2 = AddCubeToWorld(Vector3(0, -3.4f, 240), Vector3(60, 4, 7),
		0, blankTex, Vector4(1, 1, 0, 1));
	sticky2->layer = Layer::Sticky;

	//Icy
	GameObject* icy = AddCubeToWorld(Vector3(0, -3.4f, 180), Vector3(150, 4, 7),
		0, blankTex, Vector4(0, 1, 0.75f, 1));
	icy->layer = Layer::Ice;


	//StateMachine

	//statemachine walls
	for (int i = 0; i < 4; i++)
	{
		AddCubeToWorld(StateMachineWallPosition[i], Vector3(5,14,5), 0,
			blankTex, Vector4(.2f, .2f, .2f, 1));
	}
	//TODO add stateMachine



}



GameObject* WorldGeneration::AddFloorToWorld(const Vector3& position, const Vector3& scale)
{
	GameObject* floor = new GameObject("Floor");

	AABBVolume* volume = new AABBVolume(scale);
	floor->SetBoundingVolume((CollisionVolume*)volume);
	floor->GetTransform()
		.SetScale(scale * 2)
		.SetPosition(position);

	floor->SetRenderObject(new RenderObject(&floor->GetTransform(), cubeMesh, basicTex, basicShader));
	floor->SetPhysicsObject(new PhysicsObject(&floor->GetTransform(), floor->GetBoundingVolume()));

	floor->GetPhysicsObject()->SetInverseMass(0);
	floor->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(floor);



	return floor;
}


GameObject* WorldGeneration::AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass,
	OGLTexture* tex, Vector4 color)
{
	GameObject* cube = new GameObject("Cube");
	AABBVolume* volume = new AABBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, tex, basicShader, color));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	return cube;
}


GameObject* WorldGeneration::AddOBBToWorld(const Vector3& position, Vector3 dimensions,
	Vector3 EulerAngles, float inverseMass, OGLTexture* tex, Vector4 color)
{
	GameObject* cube = new GameObject("Cube");
	OBBVolume* volume = new OBBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);

	//cube->GetPhysicsObject()->set

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2)
		.SetOrientation(Quaternion::EulerAnglesToQuaternion(EulerAngles.x, EulerAngles.y, EulerAngles.z))
		;


	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, tex, basicShader, color));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	return cube;
}


GameObject* WorldGeneration::AddPlayerToWorld(const Vector3& position)
{
	float meshSize = 3.0f;
	float inverseMass = 0.5f;

	GameObject* character = new GameObject();

	AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.85f, 0.3f) * meshSize);

	character->SetBoundingVolume((CollisionVolume*)volume);

	character->GetTransform()
		.SetScale(Vector3(meshSize, meshSize, meshSize))
		.SetPosition(position);

	if (rand() % 2)
	{
		character->SetRenderObject(new RenderObject(&character->GetTransform(), charMeshA, nullptr, basicShader));
	}
	else
	{
		character->SetRenderObject(new RenderObject(&character->GetTransform(), charMeshB, nullptr, basicShader));
	}
	character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

	character->GetPhysicsObject()->SetInverseMass(inverseMass);
	character->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(character);

	//lockedObject = character;

	return character;
}

GameObject* WorldGeneration::AddEnemyToWorld(const Vector3& position)
{
	float meshSize = 3.0f;
	float inverseMass = 0.5f;

	GameObject* character = new GameObject();

	AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.9f, 0.3f) * meshSize);
	character->SetBoundingVolume((CollisionVolume*)volume);

	character->GetTransform()
		.SetScale(Vector3(meshSize, meshSize, meshSize))
		.SetPosition(position);

	character->SetRenderObject(new RenderObject(&character->GetTransform(), enemyMesh, nullptr, basicShader));
	character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

	character->GetPhysicsObject()->SetInverseMass(inverseMass);
	character->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(character);

	return character;
}

StateGameObject* WorldGeneration::AddStateObjectToWorld(const Vector3& position)
{
	StateGameObject* apple = new StateGameObject();

	SphereVolume* volume = new SphereVolume(0.25f);
	apple->SetBoundingVolume((CollisionVolume*)volume);
	apple->GetTransform()
		.SetScale(Vector3(0.25, 0.25, 0.25))
		.SetPosition(position);

	apple->SetRenderObject(new RenderObject(&apple->GetTransform(), bonusMesh, nullptr, basicShader));
	apple->SetPhysicsObject(new PhysicsObject(&apple->GetTransform(), apple->GetBoundingVolume()));

	apple->GetPhysicsObject()->SetInverseMass(1.0f);
	apple->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(apple);

	return apple;
}

GameObject* WorldGeneration::AddBonusToWorld(const Vector3& position)
{
	GameObject* apple = new GameObject();

	SphereVolume* volume = new SphereVolume(0.25f);
	apple->SetBoundingVolume((CollisionVolume*)volume);
	apple->GetTransform()
		.SetScale(Vector3(0.25, 0.25, 0.25))
		.SetPosition(position);

	apple->SetRenderObject(new RenderObject(&apple->GetTransform(), bonusMesh, nullptr, basicShader));
	apple->SetPhysicsObject(new PhysicsObject(&apple->GetTransform(), apple->GetBoundingVolume()));

	apple->GetPhysicsObject()->SetInverseMass(1.0f);
	apple->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(apple);

	return apple;
}

/*

Builds a game object that uses a sphere mesh for its graphics, and a bounding sphere for its
rigid body representation. This and the cube function will let you build a lot of 'simple'
physics worlds. You'll probably need another function for the creation of OBB cubes too.

*/
GameObject* WorldGeneration::AddSphereToWorld(const Vector3& position, float radius, float inverseMass)
{
	GameObject* sphere = new GameObject("Sphere");

	Vector3 sphereSize = Vector3(radius, radius, radius);
	SphereVolume* volume = new SphereVolume(radius);
	sphere->SetBoundingVolume((CollisionVolume*)volume);

	sphere->GetTransform()
		.SetScale(sphereSize)
		.SetPosition(position);

	sphere->SetRenderObject(new RenderObject(&sphere->GetTransform(), sphereMesh, basicTex, basicShader));
	sphere->SetPhysicsObject(new PhysicsObject(&sphere->GetTransform(), sphere->GetBoundingVolume()));

	sphere->GetPhysicsObject()->SetInverseMass(inverseMass);
	sphere->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(sphere);

	return sphere;
}

GameObject* WorldGeneration::AddCapsuleToWorld(const Vector3& position, float halfHeight, float radius, float inverseMass)
{
	GameObject* capsule = new GameObject("Capsule");

	CapsuleVolume* volume = new CapsuleVolume(halfHeight, radius);
	capsule->SetBoundingVolume((CollisionVolume*)volume);

	capsule->GetTransform()
		.SetScale(Vector3(radius * 2, halfHeight, radius * 2))
		.SetPosition(position);

	capsule->SetRenderObject(new RenderObject(&capsule->GetTransform(), capsuleMesh, basicTex, basicShader));
	capsule->SetPhysicsObject(new PhysicsObject(&capsule->GetTransform(), capsule->GetBoundingVolume()));

	capsule->GetPhysicsObject()->SetInverseMass(inverseMass);
	capsule->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(capsule);

	return capsule;

}



GameObject* WorldGeneration::InitPlayer()
{
	PlayerClass* player = new PlayerClass("Player");
	float radius = 1.2f;

	Vector3 sphereSize = Vector3(radius, radius, radius);
	SphereVolume* volume = new SphereVolume(radius);

	player->SetBoundingVolume((CollisionVolume*)volume);

	player->GetTransform()
		.SetScale(sphereSize)
		.SetPosition(Vector3(0, 10, 0));

	player->SetRenderObject(new RenderObject(&player->GetTransform(), sphereMesh, playerTex, basicShader));
	//player->setc
	player->SetPhysicsObject(new PhysicsObject(&player->GetTransform(), player->GetBoundingVolume()));

	player->GetPhysicsObject()->SetInverseMass(2);
	player->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(player);
	return player;
}


void WorldGeneration::BridgeConstraintTest()
{
	Vector3 cubeSize = Vector3(8, 8, 8);

	float invCubeMass = 5; // how heavy the middle pieces are
	int numLinks = 10;
	float maxDistance = 30; // constraint distance
	float cubeDistance = 20; // distance between links

	Vector3 startPos = Vector3(5, 5, 5);

	GameObject* start = AddCubeToWorld(startPos + Vector3(0, 0, 0)
		, cubeSize, 0, basicTex);
	GameObject* end = AddCubeToWorld(startPos + Vector3((numLinks + 2)
		* cubeDistance, 0, 0), cubeSize, 0, basicTex);

	GameObject* previous = start;

	for (int i = 0; i < numLinks; ++i)
	{
		GameObject* block = AddCubeToWorld(startPos + Vector3((i + 1) *
			cubeDistance, 0, 0), cubeSize, invCubeMass, basicTex);
		PositionConstraint* constraint = new PositionConstraint(previous,
			block, maxDistance);
		world->AddConstraint(constraint);
		previous = block;

	}
	PositionConstraint* constraint = new PositionConstraint(previous,
		end, maxDistance);
	world->AddConstraint(constraint);

}