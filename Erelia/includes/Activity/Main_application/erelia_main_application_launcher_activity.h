#pragma once

#include "jgl.h"

namespace Activity
{
	class Launcher : public jgl::Abstract_activity
	{
	private:

	public:
		void execute();
		void on_transition();
	};
}