#pragma once

#include "jgl.h"
#include "widget/Abstract_widget/erelia_abstract_manager.h"
#include "widget/Abstract_widget/erelia_overworld_widget.h"
#include "network/erelia_network_definition.h"
#include "structure/Data/Map/erelia_map.h"

class Map_manager : public Overworld_widget, public Abstract_manager
{
private:
	std::mutex _map_mutex;
	jgl::Map<jgl::Vector2Int, jgl::Bool> _asked_chunks;
	jgl::Array<jgl::Vector2Int> _asked_chunk_list;

	void _on_geometry_change();
	void _render();
	jgl::Bool _update();

	void _receive_chunk_data(Message& p_msg);
	void _request_chunk_data();
	void _received_chunk_modification(Message& p_msg);
	void _treat_request_chunk_data(Connection* p_client, Message& p_msg);
	void _treat_chunk_modification(Connection* p_client, Message& p_msg);

	void _initialize_client();
	void _initialize_server();

public:
	Map_manager(jgl::Widget* p_parent);
};