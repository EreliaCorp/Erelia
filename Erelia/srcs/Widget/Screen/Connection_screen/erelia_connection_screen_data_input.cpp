#include "erelia.h"

Connection_screen::Data_input::Data_input()
{
	label = nullptr;
	entry = nullptr;
}

Connection_screen::Data_input::Data_input(jgl::String p_name, jgl::String p_value, jgl::Widget* p_parent)
{
	label = new jgl::Text_label(p_name + " :", p_parent);
	label->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
	label->box().set_border_size(0);
	label->activate();
	
	entry = new jgl::Text_entry(p_value, p_parent);
	entry->box().set_color(jgl::Color(255, 255, 255, 80), jgl::Color(255, 255, 255, 80));
	entry->activate();
}

void Connection_screen::Data_input::set_geometry(jgl::Vector2Int p_anchor, jgl::Vector2Int p_area)
{
	jgl::Vector2Int label_size = jgl::Vector2Int(p_area.x / 2, (p_area.y / 3) - p_area.y / 20);
	jgl::Vector2Int entry_size = jgl::Vector2Int(p_area.x, (p_area.y / 3 * 2) - p_area.y / 20);

	jgl::Vector2Int label_pos = jgl::Vector2Int(0, 0);
	jgl::Vector2Int entry_pos = jgl::Vector2Int(0, label_size.y + p_area.y / 10);

	label->set_geometry(p_anchor + label_pos, label_size);
	entry->box().set_border_size(entry_size.y / 10);
	entry->set_geometry(p_anchor + entry_pos, entry_size);
}