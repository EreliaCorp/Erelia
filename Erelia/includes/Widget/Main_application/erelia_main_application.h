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

	typedef jgl::Singleton< jgl::Publisher<Event> > Publisher;
	typedef jgl::Publisher<Event>::Subscriber Subscriber;
	typedef jgl::Singleton< jgl::State_machine<Status> > State_machine;

	class Event_subscriber : public jgl::Publisher<Event>::Subscriber
	{
	public:
		void update(Event p_event, jgl::Data_contener& p_param);
	};

private:
	jgl::Array< Subscriber*> _subscriber_array;

	void _on_geometry_change();

	jgl::Bool _update();

	void _initiate_singleton();
	void _initiate_network();
public:
	Main_application(jgl::Widget* p_parent = nullptr);
	~Main_application();
};