#pragma once

#include "jgl.h"

class Console_output : public jgl::Widget
{
private:
	struct Line
	{
		struct Line_value
		{
			jgl::String data;
			jgl::Vector2Int size;

			Line_value(jgl::String p_data)
			{
				data = p_data;
				size = 0;
			}
		};
		static jgl::Size_t text_size;
		jgl::String _text;
		jgl::Vector2Int _size;
		std::deque<Line_value> _parts;
		jgl::Bool _computed;

		Line(jgl::String p_text);
		void compute(jgl::Vector2Int p_area);
		jgl::Vector2Int render(jgl::Vector2Int p_size, jgl::Vector2Int p_anchor, jgl::Float p_depth, jgl::Size_t& p_nb_line_to_dodge);

		jgl::Size_t nb_line() { return (_parts.size()); }
		jgl::Vector2Int size() { return (_size); }
		jgl::Bool computed() { return (_computed); }
		void uncompute() { _computed = false; }
	};
	jgl::Widget_component::Box _box;
	std::deque<Line> _messages;
	jgl::Size_t _total_nb_line;
	jgl::Size_t _nb_line_to_dodge;

	void _render();
	void _on_geometry_change();

	jgl::Bool _update();

public:
	Console_output(jgl::Widget* p_parent);
	void add_message(jgl::String p_msg);
	std::deque<Line>& messages() { return (_messages); }
};