#include "PlayerClass.h"
#include "../../Common/Window.h"





namespace NCL
{
	namespace CSC8503
	{

		void PlayerClass::Update(float dt)
		{
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::W))
			{
				physicsObject->SetLinearVelocity(Vector3(0, 0, -speed));
			}
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::S))
			{
				physicsObject->SetLinearVelocity(Vector3(0, 0, speed));
			}
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::A))
			{
				physicsObject->SetLinearVelocity(Vector3(-speed, 0, 0));
			}
			if (Window::GetKeyboard()->KeyHeld(KeyboardKeys::D))
			{
				physicsObject->SetLinearVelocity(Vector3(speed, 0, 0));
			}
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE))
			{
				physicsObject->AddForce(Vector3(0, 1000, 0));
			}
		}
	}
}