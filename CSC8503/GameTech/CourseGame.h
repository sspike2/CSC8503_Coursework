#pragma once
#include "GameTechRenderer.h"
#include "../CSC8503Common/PhysicsSystem.h"
#include "StateGameObject.h"
#include "PlayerClass.h"
#include "WorldGeneration.h"

namespace NCL
{
	namespace CSC8503
	{
		class WorldGeneration;

		class CourseGame
		{
		public:
			CourseGame();
			~CourseGame();

			virtual void UpdateGame(float dt);
			void UpdatePause(float dt);

			GameWorld* world;
			bool inSelectionMode;

			void SetPlayer(PlayerClass* player) { this->player = player; }
			PlayerClass* GetPlayer() { return player; }

		protected:

			
			WorldGeneration* worldGen;

			void InitCamera();
			void UpdateKeys();

			void InitWorld();


			void InitGameExamples();

			void InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius);
			void InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing);
			void InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims);
			void InitDefaultFloor();

			bool SelectObject();
			void MoveSelectedObject();
			void DebugObjectMovement();
			void LockedObjectMovement();

			
			Vector4 selectedObjColor;

			GameTechRenderer* renderer;
			PhysicsSystem* physics;

			//WorldGeneration* worldGen;

			PlayerClass* player = nullptr;

			bool useGravity;

			float		forceMagnitude;

			GameObject* selectionObject = nullptr;

			

			//Coursework Additional functionality	
			GameObject* lockedObject = nullptr;
			Vector3 lockedOffset = Vector3(0, 14, -20);
			void LockCameraToObject(GameObject* o)
			{
				lockedObject = o;
			}


		};
	}
}

