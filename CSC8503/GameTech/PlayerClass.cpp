#include "PlayerClass.h"
#include "../../Common/Window.h"
#include "../../Common/Maths.h"




namespace NCL
{
	namespace CSC8503
	{


		PlayerClass::PlayerClass(string name)
		{
			this->name = name;
			worldID = -1;
			isActive = true;
			boundingVolume = nullptr;
			physicsObject = nullptr;
			renderObject = nullptr;
		}

		void PlayerClass::Update(float dt)
		{


			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::W))
			{
				physicsObject->AddForce(Vector3(0, 0, speed));
			}
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::S))
			{
				physicsObject->AddForce(Vector3(0, 0, -speed));
			}
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::A))
			{
				physicsObject->AddForce(Vector3(speed, 0, 0));
			}
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::D))
			{
				physicsObject->AddForce(Vector3(-speed, 0, 0));
			}
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE) && isGrounded)
			{
				Jump();
			}

			velocity = physicsObject->GetLinearVelocity();
			/*if (!isGrounded)
			{
				velocity += Vector3(0, 1.2, 0);
			}*/

			Vector3  vel = Maths::Clamp(velocity, Vector3(-200, -400, -200), Vector3(200, 400, 200));
			physicsObject->SetLinearVelocity(vel);


		}



		void PlayerClass::OnCollisionBegin(GameObject* otherObject)
		{

			
			if (otherObject->layer == Layer::Ground)
			{
				isGrounded = true;
			}
			if (otherObject->layer == Layer::Collectible)
			{
				//coins += 12;
			}
			if (otherObject->layer == Layer::Ice)
			{

			}
			if (otherObject->layer == Layer::Sticky)
			{

			}
			if (otherObject->layer == Layer::Lava)
			{

			}


		}

		void PlayerClass::Jump()
		{
			isGrounded = false;
			physicsObject->AddForce(Vector3(0, 500, 0));
		}
	}
}