#pragma once

#include "jgl.h"

class Abstract_console_parser : public jgl::Widget
{
protected:
	std::deque<jgl::String> _command_pool;
	Console_output* _output;

	void _render()
	{

	}

	void _on_geometry_change()
	{

	}

	jgl::Bool _update()
	{
		if (_command_pool.size() != 0)
		{
			jgl::String head = _command_pool.front();
			_command_pool.pop_front();
			_parse_command(head);
		}
		return (false);
	}

	virtual void _parse_command(jgl::String& p_text) = 0;

public:
	Abstract_console_parser(Console_output* p_output, jgl::Widget* p_parent) : jgl::Widget(p_parent)
	{
		_output = p_output;
	}

	void add_command(jgl::String p_command)
	{
		_command_pool.push_back(p_command);

	}
};