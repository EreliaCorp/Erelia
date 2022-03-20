#include "erelia.h"

void Main_application::Event_subscriber::update(Event p_event, jgl::Data_contener& p_param)
{
	switch (p_event)
	{
		case Event::Initialize:
		{
			Publisher::instance()->notify(Event::Start_loading);
			break;
		}
		case Event::Start_loading:
		{
			State_machine::instance()->set_state(Status::Loading);
			break;
		}
		case Event::Loading_completed:
		{
			Publisher::instance()->notify(Event::Transition_launcher);
			break;
		}
		case Event::Transition_launcher:
		{
			State_machine::instance()->set_state(Status::Launcher);
			break;
		}
		default:
			break;
	}
}