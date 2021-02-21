#include "altpch.h"
#include "WindowsInput.h"

#include <SDL.h>

namespace Alternate 
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		//auto window = static_cast<SDL_Window*>(Application::Get().GetWindow().GetNativeWindow());
		const Uint8* state = SDL_GetKeyboardState(NULL);
		return state[keycode];
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		int x, y;
		Uint32 state = SDL_GetMouseState(&x, &y);
		return {(float)x,(float)y};
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

}