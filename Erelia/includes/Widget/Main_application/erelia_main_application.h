#pragma once

#include "jgl.h"

#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

#include "structure/Atlas/erelia_path_atlas.h"
#include "structure/Atlas/erelia_texture_atlas.h"
#include "structure/Atlas/erelia_translation_atlas.h"

#include "widget/Abstract_widget/erelia_manager_widget.h"

class Main_application : public Manager_widget
{
public:
	enum class Status
	{
		Erro = -1,
		No_mode = 0,
		Connection_mode = 1,
		Loading_mode = 2,
		Game_mode = 3,
		Battle_mode = 4
	};
	enum class Event
	{
		Connection_send = 0,
		Connection_received = 1
	};

	typedef jgl::Singleton< jgl::Publisher<Event> > Publisher;
	typedef jgl::Singleton< jgl::State_machine<Status> > State_machine;

private:
	void _on_geometry_change();

	jgl::Bool _update();

	void _initiate_singleton();
	void _initiate_network();
public:
	Main_application(jgl::Widget* p_parent = nullptr);
	~Main_application();
};