#pragma once

#include "jgl.h"

namespace Launcher
{
	class Message_output : public jgl::Widget
	{
	private:
		void _on_geometry_change();
		void _render();

		jgl::Text_label* _messages_output[3];

	public:
		Message_output(jgl::Widget* p_parent);
		void set_text(jgl::String p_text_a, jgl::String p_text_b = "", jgl::String p_text_c = "");
	};
}