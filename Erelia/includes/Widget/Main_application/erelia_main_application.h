#pragma once

#include "jgl.h"

#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

#include "structure/Atlas/erelia_path_atlas.h"
#include "structure/Atlas/erelia_texture_atlas.h"
#include "structure/Atlas/erelia_translation_atlas.h"

#include "widget/Abstract_widget/erelia_manager_widget.h"

#include "Activity/Main_application/erelia_main_application_no_mode_activity.h"
#include "Activity/Main_application/erelia_main_application_loading_activity.h"
#include "Activity/Main_application/erelia_main_application_launcher_activity.h"

class Main_application : public Manager_widget
{
public:
	enum class Status
	{
		Error = -1,
		No_mode = 0,
		Loading = 1,
		Launcher = 2
	};
	enum class Event
	{
		Initialize,
		Start_loading,
		Loading_completed,
		Transition_launcher
	};
	struct Context
	{

	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;
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

#define ACTIVITY_PARAM [&](Context& p_context)