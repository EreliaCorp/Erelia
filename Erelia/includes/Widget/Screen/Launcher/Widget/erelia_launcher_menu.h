#pragma once

#include "jgl.h"

namespace Launcher
{
	class Menu : public jgl::Widget
	{
	private:
		struct Data_input
		{
			jgl::Text_label* label;
			jgl::Text_entry* entry;

			Data_input();
			Data_input(jgl::String p_name, jgl::String p_value, jgl::Widget* p_parent);

			void set_geometry(jgl::Vector2Int p_anchor, jgl::Vector2Int p_area);
		};

		jgl::Frame* _layout;
		jgl::Frame* _logo;
		Data_input _username_input;
		Data_input _password_input;

		void _on_geometry_change();
		void _render();

		jgl::Bool _update();

	public:
		Menu(jgl::Widget* p_parent);

		const jgl::String& username() { return (_username_input.entry->label().text()); }
		const jgl::String& password() { return (_password_input.entry->label().text()); }
	};
}