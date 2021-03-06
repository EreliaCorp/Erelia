#pragma once

#include "jgl.h"

#include "widget/Abstract_widget/erelia_abstract_manager.h"

class Player_manager : public Abstract_manager, public jgl::Updater_widget
{
private:
	jgl::Bool _motion_command_send;

	void _on_geometry_change();

	void _send_motion_command(jgl::Vector2Int p_delta);
	void _treat_player_motion(Connection* p_client, Message& p_msg);
	void _receive_movement_treated(Message& p_msg);

	jgl::Bool _update();

	void _initialize_client();
	void _initialize_server();

public:
	Player_manager(jgl::Widget* p_parent);
};