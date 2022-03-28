#include "Widget/Screen/Game_world/WIdget/erelia_entity_manager.h"
#include "structure/Data/Engine/erelia_engine.h"
#include "structure/Atlas/erelia_account_atlas.h"

void Entity_manager::_on_geometry_change()
{

}

jgl::Bool Entity_manager::_update()
{
	if (Server_manager::instance() != nullptr)
	{
		if (_entity_updater_timer.timeout() == true)
		{
			for (auto tmp : Engine::instance()->entities())
			{
				if (tmp.second->is_moving() == true)
				{
					tmp.second->update();
				}
			}

			static Message msg(Server_message::Entity_data);

			msg.clear();

			for (auto tmp : Engine::instance()->entities())
			{
				msg << tmp.first;
				msg << tmp.second->pos();
				msg << tmp.second->is_moving();
			}

			Server_manager::server()->send_to_all(msg);

			_entity_updater_timer.start();

			Account_atlas::instance()->actualize_player_data();
		}
	}

	return (false);
}

void Entity_manager::_receive_entity_data(Message& p_msg)
{
	if (Server_manager::instance() == nullptr)
	{
		while (p_msg.empty() == false)
		{
			jgl::Long id;
			jgl::Vector2 pos;
			jgl::Bool moving;

			p_msg >> id;
			p_msg >> pos;
			p_msg >> moving;

			Entity* tmp_entity = Engine::instance()->entity(id);

			if (tmp_entity != nullptr)
			{
				tmp_entity->place(pos);
			}
			else
			{
				tmp_entity = new Entity(id);
				tmp_entity->place(pos);
				Engine::instance()->add_entity(tmp_entity);
			}
		}
	}
}

void Entity_manager::_receive_entity_suppression_command(Message& p_msg)
{
	jgl::Long id;

	p_msg >> id;

	Engine::instance()->remove_entity(id);
}

void Entity_manager::_initialize_server()
{

}

void Entity_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Entity_data, CLIENT_ACTIVITY{
			_receive_entity_data(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_suppression, CLIENT_ACTIVITY{
			_receive_entity_suppression_command(p_msg);
		});
}

void Entity_manager::receive_entity_data(Message& p_msg)
{
	jgl::Long id;
	jgl::Vector2 pos;
	jgl::Bool moving;

	p_msg >> id;
	p_msg >> pos;
	p_msg >> moving;

	Entity* tmp_entity = Engine::instance()->entity(id);

	if (tmp_entity != nullptr)
	{
		tmp_entity->place(pos);
	}
	else
	{
		tmp_entity = new Entity(id);
		tmp_entity->place(pos);
		Engine::instance()->add_entity(tmp_entity);
	}
}


Entity_manager::Entity_manager(jgl::Widget* p_parent) : Abstract_manager(), jgl::Updater_widget(p_parent),
	_entity_updater_timer(4)
{
	_initiate();
}