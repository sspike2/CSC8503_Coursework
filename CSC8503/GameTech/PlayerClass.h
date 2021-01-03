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
			//PlayerClass();
		protected:
			int playerHealth = 100;
			int score = 0;
			int speed = 10;
			bool isGrounded;
		};
	}
}

