#pragma once

#include "jgl.h"

namespace Activity
{
	class No_mode : public jgl::Abstract_activity
	{
	private:

	public:
		void execute();
		void on_transition();
	};
}