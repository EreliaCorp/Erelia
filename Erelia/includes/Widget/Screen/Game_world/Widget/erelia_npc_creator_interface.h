#pragma once

#include "jgl.h"

class NPC_creator_interface : public jgl::Widget
{
private:
	void _on_geometry_change();
	void _render();

public:
	NPC_creator_interface(jgl::Widget* p_parent);
};