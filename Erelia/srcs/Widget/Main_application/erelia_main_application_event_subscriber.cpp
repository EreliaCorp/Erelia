#include "erelia.h"


Main_application::Event_subscriber::Event_subscriber(jgl::Size_t p_nb_event, ...)
{
	va_list list;
	va_start(list, p_nb_event);

	for (jgl::Size_t i = 0; i < p_nb_event; i++)
	{
		Event tmp_event = (Event)va_arg(list, Event);
		Publisher::instance()->subscribe(tmp_event, this);
	}
}

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