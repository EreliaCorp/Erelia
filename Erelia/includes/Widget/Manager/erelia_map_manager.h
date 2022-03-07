#pragma once

#include "jgl.h"

#include "Routine/erelia_map_routine.h"

#include "Widget/Commun/erelia_graphical_widget.h"

class Map_manager : public Graphical_widget
{
private:
	jgl::Map<jgl::Vector2Int, jgl::Bool> _asked_chunks;
	jgl::Array<jgl::Vector2Int> _asked_chunk_list;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	void _request_chunk_data();

	void _initialize_server();
	void _initialize_client();
	void _initiate();

	Map_manager(jgl::Widget* p_parent = nullptr);

	static Map_manager* _instance;
public:
	void receive_chunk(Chunk* p_chunk);

	static Map_manager* instanciate(jgl::Widget* p_parent = nullptr);
	static Map_manager* instance();
};