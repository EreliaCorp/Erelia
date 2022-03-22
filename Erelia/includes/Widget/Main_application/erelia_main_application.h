#pragma once

#include "jgl.h"

#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

#include "structure/Atlas/erelia_path_atlas.h"
#include "structure/Atlas/erelia_texture_atlas.h"
#include "structure/Atlas/erelia_translation_atlas.h"

#include "widget/Abstract_widget/erelia_abstract_manager_widget.h"
#include "widget/Abstract_widget/erelia_abstract_screen.h"

#include "widget/screen/erelia_launcher_screen.h"
#include "widget/screen/erelia_loading_screen.h"
#include "widget/screen/erelia_game_world_screen.h"
#include "widget/screen/erelia_game_battle_screen.h"

class Main_application : public Abstract_manager_widget
{
public:
	enum class Status
	{
		No_mode = -1,
		Loading = 0,
		Launcher = 1,
		World_mode = 2,
		Battle_mode = 3,
	};
	typedef Status Screen;
	enum class Event
	{
		Go_loading,
		Go_launcher,
		Go_world,
		Go_battle
	};
	struct Context
	{

	};

private:
	struct Activity
	{
	private:
		Activity() = delete;

	public:
		class No_mode : public jgl::Abstract_activity
		{
		private:
		public:
			void execute();
			void on_transition();
		};
		class Launcher_mode : public jgl::Abstract_activity
		{
		private:
		public:
			void execute();
			void on_transition();
		};
		class Loading_mode : public jgl::Abstract_activity
		{
		private:
		public:
			void execute();
			void on_transition();
		};
		class World_mode : public jgl::Abstract_activity
		{
		private:
		public:
			void execute();
			void on_transition();
		};
		class Battle_mode : public jgl::Abstract_activity
		{
		private:
		public:
			void execute();
			void on_transition();
		};
	};

	jgl::Array<Abstract_screen*> _screens;

	void _on_geometry_change();

	jgl::Bool _update();
	 
	void _initiate_singleton();
	void _initiate_network();
	void _initiate_screen();


	static Main_application* _instance;

public:
	static Main_application* instance() { return (_instance); }

	void transition_to_screen(Screen p_screen);

	Main_application(jgl::Widget* p_parent = nullptr);
	~Main_application();
};

typedef jgl::Singleton< jgl::Publisher<Main_application::Event, Main_application::Context> > Publisher;
typedef jgl::Singleton< jgl::State_machine<Main_application::Status> > State_machine;

#define ACTIVITY_PARAM [&](Context& p_context)