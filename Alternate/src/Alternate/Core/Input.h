#pragma once

#include "Alternate/Core/Base.h"
#include "Alternate/Core/KeyCodes.h"
#include "Alternate/Core/MouseButtonCodes.h"

namespace Alternate
{
	class  Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseButtonCode button);
		static std::pair<float, float> GetMousePosition();
		static float  GetMouseX();
		static float GetMouseY();
	};
}