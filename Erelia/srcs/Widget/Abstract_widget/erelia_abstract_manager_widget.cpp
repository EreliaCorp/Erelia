#include "widget/Abstract_widget/erelia_abstract_manager.h"

void Abstract_manager::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}

Abstract_manager::Abstract_manager()
{

}