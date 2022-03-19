#pragma once

#include "jgl.h"

#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

#include "structure/Atlas/erelia_path_atlas.h"
#include "structure/Atlas/erelia_texture_atlas.h"
#include "structure/Atlas/erelia_translation_atlas.h"

class Main_application : public jgl::Widget
{
private:
	void _on_geometry_change();
	void _render();

	void _start_server();
	void _start_client();

	void _initialize_client();
	void _initialize_server();

	void _initiate();

	jgl::Bool _update();

	Main_application(jgl::Widget* p_parent = nullptr);

	static Main_application* _instance;
public:

	static Main_application* instanciate(jgl::Widget* p_parent);
	static Main_application* instance() { return (_instance); }

	~Main_application();
};