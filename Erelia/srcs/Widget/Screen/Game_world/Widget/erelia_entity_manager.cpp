#include "Widget/Screen/Game_world/WIdget/erelia_entity_manager.h"
#include "structure/Data/Engine/erelia_engine.h"
#include "structure/Atlas/erelia_account_atlas.h"
#include "widget/screen/game_world/erelia_game_world_screen.h"
#include "structure/Atlas/erelia_texture_atlas.h"

jgl::Size_t Entity_manager::nb_render = 0;
jgl::Size_t Entity_manager::nb_update = 0;
jgl::Size_t Entity_manager::nb_pos_update = 0;

void Entity_manager::_on_geometry_change()
{

}

void Entity_manager::_render_sprite(Entity* p_entity, jgl::Vector2Int p_anchor, jgl::Float p_depth)
{
	if (p_entity != nullptr)
		p_entity->render(p_anchor, Node::size, p_depth);
}

void Entity_manager::_render_name(Entity* p_entity, jgl::Vector2Int p_anchor, jgl::Float p_depth)
{
	if (p_entity != nullptr)
		p_entity->render_name(p_anchor, p_depth);
}

void Entity_manager::_render_path(AI_controlled_entity* p_entity, jgl::Float p_depth)
{
	jgl::Vector2 pos = p_entity->destination();

	for (jgl::Size_t i = p_entity->movement_info().data.path_index; i < p_entity->movement_info().data.path.size(); i++)
	{
		jgl::Vector2Int anchor = convert_world_to_screen((pos.ceiling() + p_entity->movement_info().data.path[i]).ceiling() + 0.5f) - Node::size / 4;
		pos += p_entity->movement_info().data.path[i];

		jgl::draw_rectangle_color(jgl::Color::red(), anchor, Node::size / 2, p_depth);
	}
}

void Entity_manager::_render()
{
	Engine::instance()->lock_mutex();
	for (auto tmp : Engine::instance()->entities())
	{
		if (tmp.second != nullptr)
		{
			jgl::Vector2Int anchor = convert_world_to_screen(tmp.second->pos());
			jgl::Float depth = _depth + (tmp.second->is_flying() == true ? Chunk::C_LAYER_LENGTH + 1 : Chunk::C_LAYER_LENGTH / 2 + 0.5f);

			_render_sprite(tmp.second, anchor, depth);

			_render_name(tmp.second, anchor, depth);

			if (tmp.second->type() == Entity::Type::NPC || tmp.second->type() == Entity::Type::Enemy)
				_render_path(reinterpret_cast<AI_controlled_entity*>(tmp.second), depth);
		}
	}
	Engine::instance()->unlock_mutex();
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

		Entity* tmp_entity = new AI_controlled_entity(name, type, id);

		tmp_entity->place(pos);

		Engine::instance()->add_entity(tmp_entity);
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

void Entity_manager::_receive_client_entity_modification(Connection* p_client, Message& p_msg)
{
	jgl::Long id;
	jgl::String name;
	jgl::Vector2 pos;
	Entity::Type type;
	AI_controlled_entity::Movement_info movement_info;

	p_msg >> id;
	p_msg >> name;
	p_msg >> pos;
	p_msg >> type;
	p_msg >> movement_info.pattern;

	if (movement_info.pattern == AI_controlled_entity::Movement_info::Pattern::Wander)
	{
		p_msg >> movement_info.data.range;
	}
	else if (movement_info.pattern == AI_controlled_entity::Movement_info::Pattern::Path)
	{
		for (jgl::Size_t i = 0; i < movement_info.data.path.size(); i++)
		{
			p_msg >> movement_info.data.path[i];
		}
	}

	if (id == -1)
	{
		AI_controlled_entity* tmp_entity = nullptr;

		if (type == Entity::Type::NPC)
			tmp_entity = new NPC(name, Engine::instance()->request_id());
		else if (type == Entity::Type::Spawner)
			tmp_entity = new AI_controlled_entity(name, type, movement_info.pattern, Engine::instance()->request_id());
		else if (type == Entity::Type::Enemy)
			tmp_entity = new AI_controlled_entity(name, type, movement_info.pattern, Engine::instance()->request_id());

		if (tmp_entity != nullptr)
		{
			tmp_entity->place(pos);

			jgl::cout << "Creating new entity [" << tmp_entity->id() << "] - (" << tmp_entity->name() << ")" << jgl::endl;
			Engine::instance()->add_entity(tmp_entity);

			static Message result(Server_message::Entity_creation_confirmation);

			result << tmp_entity->id();

			Server_manager::server()->send_to(p_client, result);
		}
	}
	else
	{
		AI_controlled_entity* tmp_entity = static_cast<AI_controlled_entity *>(Engine::instance()->entity(id));

		if (tmp_entity != nullptr)
		{
			tmp_entity->set_name(name);
			tmp_entity->set_type(type);
			tmp_entity->set_movement_info(movement_info);
			tmp_entity->place(pos);

			static Message result(Server_message::Entity_modification);
			result.clear();

			result << id;
			result << name;
			result << type;

			Server_manager::server()->send_to_all(result, nullptr);
		}
	}
}

void Entity_manager::_receive_entity_modification(Message& p_msg)
{
	jgl::Long id;
	jgl::String name;
	jgl::Vector2 pos;
	Entity::Type type;

	p_msg >> id;

	if (id != -1)
	{
		AI_controlled_entity* tmp_entity = static_cast<AI_controlled_entity*>(Engine::instance()->entity(id));

		p_msg >> name;
		p_msg >> type;

		tmp_entity->set_name(name);
		tmp_entity->set_type(type);
	}
}

void Entity_manager::_receive_entity_creation_confirmation(Message& p_msg)
{
	jgl::Long id;

	p_msg >> id;

	NPC_creator_interface::instance()->set_entity_id(id);
}

void Entity_manager::_receive_client_entity_suppression(Connection* p_client, Message& p_msg)
{
	p_msg.header.id = Server_message::Entity_suppression;

	jgl::Long id;

	p_msg >> id;

	p_msg.header.readed = 0;

	Server_manager::server()->send_to_all(p_msg, nullptr);
}

void Entity_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Request_entity_info, SERVER_ACTIVITY{
			_receive_request_entity_info(p_client, p_msg);
		});
	Server_manager::server()->add_activity(Server_message::Entity_modification, SERVER_ACTIVITY{
			_receive_client_entity_modification(p_client, p_msg);
		});

	Server_manager::server()->add_activity(Server_message::Entity_suppression_request, SERVER_ACTIVITY{
			_receive_client_entity_suppression(p_client, p_msg);
		});
}

void Entity_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Entity_modification, CLIENT_ACTIVITY{
			_receive_entity_modification(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_data, CLIENT_ACTIVITY{
			_receive_entity_data(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_info, CLIENT_ACTIVITY{
			_receive_entity_info(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_suppression, CLIENT_ACTIVITY{
			_receive_entity_suppression_command(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_creation_confirmation, CLIENT_ACTIVITY{
			_receive_entity_creation_confirmation(p_msg);
		});
}

Entity_manager::Entity_manager(jgl::Widget* p_parent) : Abstract_manager(), Overworld_widget(p_parent),
	_entity_updater_timer(1000 / 60)
{
	_initiate();
}