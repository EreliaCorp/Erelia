#include "erelia.h"

Entity_manager* Entity_manager::_instance = nullptr;

void Entity_manager::_on_geometry_change()
{

}

void Entity_manager::_render()
{
	for (auto tmp : Engine::instance()->entities())
	{
		if (tmp.second != nullptr)
		{
			if (tmp.second->sprite_sheet() != nullptr)
				tmp.second->sprite_sheet()->draw(tmp.second->sprite(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, _depth + Chunk::C_LAYER_LENGTH / 2, 1.0f);
			else
				jgl::draw_rectangle_color(jgl::Color::blue(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, _depth + Chunk::C_LAYER_LENGTH / 2);

		}
	}
}

jgl::Bool Entity_manager::_update()
{
	if (Server_manager::instance() != nullptr)
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
	}
	return (false);
}

jgl::Bool Entity_manager::_fixed_update()
{
	return (false);
}


void Entity_manager::_initialize_server()
{

}

void Entity_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Entity_data, CLIENT_ACTIVITY{
			Routine::receive_entity_data(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Entity_suppression, CLIENT_ACTIVITY{
			Routine::receive_entity_suppression_command(p_msg);
		});
}

void Entity_manager::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
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


Entity_manager::Entity_manager(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{

	_initiate();
}

Entity_manager* Entity_manager::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Entity_manager(p_parent);
		_instance->activate();
	}
	return (_instance);
}

Entity_manager* Entity_manager::instance()
{
	return (_instance);
}