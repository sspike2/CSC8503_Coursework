#pragma once
#include "../CSC8503Common/GameObject.h"


namespace NCL
{
	namespace CSC8503
	{
		class PlayerClass : public GameObject
		{
		public:
			void Update(float dt);
			PlayerClass(string name = "");

			int GetScore() const { return score; }
			void AddScore(int Ammount) { score += Ammount; }


		protected:
			int playerHealth = 100;
			int score = 0;
			int speed = 10;
			bool isGrounded;
			Vector3 velocity;

			virtual void OnCollisionBegin(GameObject* otherObject);

			void Jump();

		};
	}
}

