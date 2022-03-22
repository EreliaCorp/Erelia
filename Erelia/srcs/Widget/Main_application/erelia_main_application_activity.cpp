#include "erelia.h"

void Main_application::Activity::No_mode::execute()
{
	THROW_INFORMATION("No mode execute");
}

void Main_application::Activity::No_mode::on_transition()
{
	THROW_INFORMATION("Initialize application");
	Publisher::instance()->notify(Event::Go_loading);
}

void Main_application::Activity::Loading_mode::execute()
{
	THROW_INFORMATION("Loading execute");
	/*
		Do the loading
	*/
	Publisher::instance()->notify(Event::Go_launcher);
}

void Main_application::Activity::Loading_mode::on_transition()
{
	THROW_INFORMATION("Transition to loading mode");
	Main_application::instance()->transition_to_screen(Main_application::Screen::No_mode);
}

void Main_application::Activity::Launcher_mode::execute()
{
	THROW_INFORMATION("Launcher mode execute");
}

void Main_application::Activity::Launcher_mode::on_transition()
{
	THROW_INFORMATION("Transition to launcher");
	Main_application::instance()->transition_to_screen(Main_application::Screen::Launcher);
}

void Main_application::Activity::World_mode::execute()
{
	THROW_INFORMATION("World execute");
}

void Main_application::Activity::World_mode::on_transition()
{
	THROW_INFORMATION("Transition to World");
	Main_application::instance()->transition_to_screen(Main_application::Screen::World_mode);
}

void Main_application::Activity::Battle_mode::execute()
{
	THROW_INFORMATION("Battle execute");
}

void Main_application::Activity::Battle_mode::on_transition()
{
	THROW_INFORMATION("Transition to Battler");
	Main_application::instance()->transition_to_screen(Main_application::Screen::Battle_mode);
}