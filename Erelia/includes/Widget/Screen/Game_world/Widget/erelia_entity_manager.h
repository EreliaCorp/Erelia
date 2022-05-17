#pragma once

#include "jgl.h"

#include "Widget/Abstract_widget/erelia_abstract_manager.h"
#include "Widget/Abstract_widget/erelia_overworld_widget.h"
#include "structure/Data/Entity/erelia_entity.h"
#include "structure/Data/Entity/erelia_AI_controlled_entity.h"

class Entity_manager : public Overworld_widget, public Abstract_manager
{
private:
	std::mutex _update_mutex;
	jgl::Timer _entity_updater_timer;

	jgl::Array<jgl::Long> _entity_to_ask;
	jgl::Map<jgl::Long, jgl::Bool> _entity_received;

	void _on_geometry_change();

	void _render_sprite(Entity* p_entity, jgl::Vector2Int p_anchor, jgl::Float p_depth);
	void _render_name(Entity* p_entity, jgl::Vector2Int p_anchor, jgl::Float p_depth);
	void _render_path(AI_controlled_entity* p_entity, jgl::Float p_depth);
	void _render();

	jgl::Bool _update();

	void _send_entity_data();
	void _request_entity_info();

	void _receive_entity_data(Message& p_msg);
	void _receive_entity_suppression_command(Message& p_msg);
	void _receive_entity_info(Message& p_msg);
	void _receive_request_entity_info(Connection* p_client, Message& p_msg);

	void _initialize_server();
	void _initialize_client();

	void _receive_npc_entity_data(Connection* p_client, Message& p_msg);
	void _receive_enemy_entity_data(Connection* p_client, Message& p_msg);
	void _receive_spawner_entity_data(Connection* p_client, Message& p_msg);
	void _receive_client_entity_modification(Connection* p_client, Message& p_msg);
	void _receive_entity_modification(Message& p_msg);
	void _receive_entity_creation_confirmation(Message& p_msg);
	void _receive_client_entity_suppression(Connection* p_client, Message& p_msg);

public:
	Entity_manager(jgl::Widget* p_parent = nullptr);
	//void receive_entity_data(Message& p_msg);

	static jgl::Size_t nb_update;
	static jgl::Size_t nb_pos_update;
	static jgl::Size_t nb_render;
};