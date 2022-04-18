#include "Widget/Screen/Game_world/WIdget/erelia_entity_manager.h"
#include "structure/Data/Engine/erelia_engine.h"
#include "structure/Atlas/erelia_account_atlas.h"

jgl::Size_t Entity_manager::nb_render = 0;
jgl::Size_t Entity_manager::nb_update = 0;
jgl::Size_t Entity_manager::nb_pos_update = 0;

void Entity_manager::_on_geometry_change()
{

}

void Entity_manager::_render()
{
	for (auto tmp : Engine::instance()->entities())
	{
		if (tmp.second != nullptr)
		{
			jgl::Float depth = _depth + (tmp.second->is_flying() == true ? Chunk::C_LAYER_LENGTH + 1 : Chunk::C_LAYER_LENGTH / 2 + 0.5f);

			if (tmp.second->sprite_sheet() != nullptr)
				tmp.second->sprite_sheet()->draw(tmp.second->sprite(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth, 1.0f);
			else
			{
				if (tmp.second->type() == Entity::Type::Player)
					jgl::draw_rectangle_color(jgl::Color::blue(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth);
				else if (tmp.second->type() == Entity::Type::NPC)
					jgl::draw_rectangle_color(jgl::Color::green(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth);
				else if (tmp.second->type() == Entity::Type::Enemy)
					jgl::draw_rectangle_color(jgl::Color::red(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth);
			}

		}
	}
	nb_render++;
}

jgl::Bool Entity_manager::_update()
{
	if (Server_manager::instance() != nullptr)
	{
		if (_entity_updater_timer.timeout() == true)
		{
			_entity_updater_timer.start();

			Engine::instance()->update();

			_send_entity_data();

			Account_atlas::instance()->actualize_player_data();
	
			nb_update++;
		}
	}

	return (false);
}


void Entity_manager::_send_entity_data()
{
	static Message msg(Server_message::Entity_data);

	msg.clear();

	for (auto tmp : Engine::instance()->entities())
	{
		msg << tmp.first;
		msg << tmp.second->pos();
	}

	Server_manager::server()->send_to_all(msg);
}

void Entity_manager::_request_entity_info()
{
	static Message msg(Server_message::Request_entity_info);
	msg.clear();

	for (jgl::Size_t i = 0; i < _entity_to_ask.size(); i++)
	{
		msg << _entity_to_ask[i];
	}

	Client_manager::client()->send(msg);
}

void Entity_manager::_receive_request_entity_info(Connection* p_client, Message& p_msg)
{
	static Message result(Server_message::Entity_info);

	result.clear();

	jgl::Long id;

	while (p_msg.empty() == false)
	{
		p_msg >> id;

		Entity* tmp_entity = Engine::instance()->entity(id);
		if (tmp_entity != nullptr)
		{
			result << tmp_entity->name();
			result << tmp_entity->type();
			result << tmp_entity->id();
			result << tmp_entity->pos();
		}
	}

	if (result.size() != 0)
	{
		Server_manager::server()->send_to(p_client, result);
	}
}

void Entity_manager::_receive_entity_info(Message& p_msg)
{
	while (p_msg.empty() == false)
	{
		jgl::String name;
		Entity::Type type;
		jgl::Long id;
		jgl::Vector2 pos;

		p_msg >> name;
		p_msg >> type;
		p_msg >> id;
		p_msg >> pos;

		Entity* new_entity = new Entity(name, type, id);
		new_entity->place(pos);

		Engine::instance()->add_entity(new_entity);
		_entity_received[id] = false;
	}
}

void Entity_manager::_receive_entity_data(Message& p_msg)
{
	if (Server_manager::instance() == nullptr)
	{
		_entity_to_ask.clear();

		while (p_msg.empty() == false)
		{
			jgl::Long id;
			jgl::Vector2 pos;

			p_msg >> id;
			p_msg >> pos;

			Entity* tmp_entity = Engine::instance()->entity(id);

			if (tmp_entity != nullptr && tmp_entity->pos() != pos)
			{
				tmp_entity->place(pos);
			}
			else if (tmp_entity == nullptr && _entity_received[id] == false)
			{
				_entity_to_ask.push_back(id);
				_entity_received[id] = true;
			}
		}

		if (_entity_to_ask.size() != 0)
		{
			_request_entity_info();
		}
		nb_pos_update++;
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
	Server_manager::server()->add_activity(Server_message::Request_entity_info, SERVER_ACTIVITY{
			_receive_request_entity_info(p_client, p_msg);
		});
}

void Entity_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Entity_data, CLIENT_ACTIVITY{
			_receive_entity_data(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_info, CLIENT_ACTIVITY{
			_receive_entity_info(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_suppression, CLIENT_ACTIVITY{
			_receive_entity_suppression_command(p_msg);
		});	
}

Entity_manager::Entity_manager(jgl::Widget* p_parent) : Abstract_manager(), Overworld_widget(p_parent),
	_entity_updater_timer(1000 / 60)
{
	_initiate();
}