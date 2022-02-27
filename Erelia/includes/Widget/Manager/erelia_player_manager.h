#pragma once

#include "jgl.h"
#include "Enum/erelia_enum.h"

#include "Widget/Singleplayer/erelia_singleplayer_player_updater.h"
#include "Widget/Singleplayer/erelia_singleplayer_player_interacter.h"

class Player_manager : public jgl::Widget
{
private:
	static Player_manager* _instance;

	jgl::Array<jgl::Widget*> _widgets;

	void _on_geometry_change();
	void _render();
	void _change_connection_mode(Connection_mode p_mode);
	void _load_ui_file();
	Player_manager(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);

public:
	static Player_manager* instanciate(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);
	static Player_manager* instance();
};
