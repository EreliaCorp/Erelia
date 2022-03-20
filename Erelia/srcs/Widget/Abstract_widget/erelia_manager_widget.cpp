#include "widget/Abstract_widget/erelia_manager_widget.h"

void Manager_widget::_initialize_client()
{

}

void Manager_widget::_initialize_server()
{

}

void Manager_widget::_render()
{

}

void Manager_widget::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}

Manager_widget::Manager_widget(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}