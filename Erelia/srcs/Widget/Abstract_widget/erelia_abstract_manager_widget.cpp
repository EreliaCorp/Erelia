#include "widget/Abstract_widget/erelia_abstract_manager_widget.h"

void Abstract_manager_widget::_initialize_client()
{

}

void Abstract_manager_widget::_initialize_server()
{

}

void Abstract_manager_widget::_render()
{

}

void Abstract_manager_widget::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}

Abstract_manager_widget::Abstract_manager_widget(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}