#include "altpch.h"
#include "Alternate/Core/Input.h"

#include <SDL.h>

namespace Alternate 
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		//auto window = static_cast<SDL_Window*>(Application::Get().GetWindow().GetNativeWindow());
		const Uint8* state = SDL_GetKeyboardState(NULL);
		return state[key];
	}

	bool Input::IsMouseButtonPressed(MouseButtonCode button)
	{
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		int x, y;
		Uint32 state = SDL_GetMouseState(&x, &y);
		return {(float)x,(float)y};
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}
}