#pragma once

#include <glm/glm.hpp>

#include "Alternate/Core/Base.h"
#include "Alternate/Core/KeyCodes.h"
#include "Alternate/Core/MouseCodes.h"

namespace Alternate
{
	class  Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float  GetMouseX();
		static float GetMouseY();
	};
}
