#pragma once

#include "jgl.h"

namespace Activity
{
	class Loading : public jgl::Abstract_activity
	{
	private:

	public:
		void execute();
		void on_transition();
	};
}