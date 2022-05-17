#include "widget/Screen/Game_world/widget/erelia_npc_creator_interface.h"
#include "structure/Data/Engine/erelia_engine.h"

void NPC_creator_interface::_on_geometry_change()
{
	jgl::Vector2Int frame_size = jgl::Vector2Int(_area.x / 3, _area.y);
	jgl::Vector2Int space = _area.y / 30;
	jgl::Vector2Int button_size = _area.y / 15;
	jgl::Vector2Int renderer_size = frame_size.x / 6 * 3;
	jgl::Vector2Int renderer_anchor = jgl::Vector2Int((frame_size.x - renderer_size.x) / 2, space.y / 2);
	jgl::Vector2Int context_anchor_left = space / 2;
	jgl::Vector2Int context_anchor_right = renderer_anchor + jgl::Vector2Int(renderer_size.x + space.x / 2, 0);
	jgl::Vector2Int context_size = jgl::Vector2Int((frame_size.x - renderer_size.x - space.x * 2) / 2, renderer_size.y);
	jgl::Vector2Int menu_anchor = jgl::Vector2Int(space.x / 2, renderer_size.y + space.y);

	jgl::Vector2Int menu_size = jgl::Vector2Int(frame_size.x - space.x, frame_size.y - menu_anchor.y - space.y / 2);

	_slider->define_position(jgl::Vector2Int(_area.x - button_size.x, 0), jgl::Vector2Int(_area.x - frame_size.x - button_size.x, 0));

	if (_slider->is_opened() == true)
		_slider->set_geometry(_slider->opened_position(), _area);
	else
		_slider->set_geometry(_slider->closed_position(), _area);

	_slider_button->set_geometry(jgl::Vector2Int(0, 0), button_size);
	_frame->set_geometry(_slider_button->anchor() + jgl::Vector2Int(button_size.x, 0), frame_size);
	_context_menu_left->set_geometry(context_anchor_left, context_size);
	_context_menu_right->set_geometry(context_anchor_right, context_size);
	_renderer->set_geometry(renderer_anchor, renderer_size);
	_menu->set_geometry(menu_anchor, menu_size);
	_message_output->set_geometry(menu_anchor, menu_size);
}

void NPC_creator_interface::_render()
{
	if (_entity != nullptr && _entity == _new_entity)
	{
		jgl::Vector2Int pos = convert_world_to_screen(_entity->pos());
		_entity->render(pos, Node::size, _depth);
		_entity->render_name(pos, _depth);
	}
}

jgl::Bool NPC_creator_interface::_update()
{
	static jgl::Bool last_state = true;

	if (last_state != _slider->is_opened())
	{
		_slider_button->label().set_text((_slider->is_opened() == true ? ">" : "<"));
		last_state = _slider->is_opened();
	}

	if (_entity == nullptr)
	{
		if (_menu->entry_name_text() != "No Entity")
			set_entity_name("No Entity");
	}
	else if (_menu->entry_name_text() != _entity->name())
	{
		set_entity_name(_menu->entry_name_text());
	}

	State_machine::instance()->update();

	return (false);
}


NPC_creator_interface::NPC_creator_interface(jgl::Widget* p_parent) : Overworld_widget(p_parent)
{
	_instance = this;
	_new_entity = new AI_controlled_entity("", Entity::Type::NPC, AI_controlled_entity::Movement_info::Pattern::Static, -1);
	_entity = nullptr;

	_slider = new Slider(this);
	_slider->activate();

	_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {
			_slider->change_state();
		}, _slider);
	_slider_button->label().set_text(">");
	_slider_button->activate();

	_frame = new jgl::Frame(_slider);
	_frame->activate();

	_menu = new Menu(_frame);
	_menu->activate();

	_message_output = new Message_output(_frame);

	_renderer = new Entity_renderer(&_entity, _frame);
	_renderer->activate();

	_context_menu_left = new Contextual_menu(_frame);
	
	_context_menu_left->button(0)->label().set_text("New");
	_context_menu_left->button(0)->define_function([&](jgl::Data_contener& p_param) {
			reset_data();
		});
	_context_menu_left->button(0)->activate();

	_context_menu_left->button(1)->label().set_text("Select");
	_context_menu_left->button(1)->define_function([&](jgl::Data_contener& p_param) {
		Publisher::instance()->notify(Event::Go_selecter);
		});
	_context_menu_left->button(1)->activate();

	_context_menu_left->button(2)->label().set_text("Place");
	_context_menu_left->button(2)->define_function([&](jgl::Data_contener& p_param) {
		Publisher::instance()->notify(Event::Go_placement);
		});
	_context_menu_left->button(2)->activate();

	_context_menu_left->button(3)->label().set_text("Remove");
	_context_menu_left->button(3)->define_function([&](jgl::Data_contener& p_param) {
		Publisher::instance()->notify(Event::Go_remove);
		});
	_context_menu_left->button(3)->activate();

	_context_menu_left->activate();

	_context_menu_right = new Contextual_menu(_frame);

	_context_menu_right->button(0)->label().set_text("Confirm");
	_context_menu_right->button(0)->define_function([&](jgl::Data_contener& p_param) {
			_send_entity_modification(_entity);
		});
	_context_menu_right->button(0)->activate();

	_context_menu_right->activate();

	Publisher::instanciate();
	State_machine::instanciate();

	Publisher::instance()->subscribe(Event::Go_default, [&](Context& p_context){
			jgl::cout << "Go into default mode" << jgl::endl;
			State_machine::instance()->set_state(Mode::Default);
		});
	Publisher::instance()->subscribe(Event::Go_selecter, [&](Context& p_context) {
			jgl::cout << "Go selecter mode" << jgl::endl;
			State_machine::instance()->set_state(Mode::Selection);
		});
	Publisher::instance()->subscribe(Event::Selection_complete, [&](Context& p_context) {
			jgl::cout << "Selection complete" << jgl::endl;
			State_machine::instance()->set_state(Mode::Default);
		});
	Publisher::instance()->subscribe(Event::Go_placement, [&](Context& p_context) {
		jgl::cout << "Go placement mode" << jgl::endl;
		State_machine::instance()->set_state(Mode::Placement);
		});
	Publisher::instance()->subscribe(Event::Placement_complete, [&](Context& p_context) {
		jgl::cout << "Placement complete" << jgl::endl;
		State_machine::instance()->set_state(Mode::Default);
		});
	Publisher::instance()->subscribe(Event::Go_remove, [&](Context& p_context) {
		jgl::cout << "Go removing mode" << jgl::endl;
		State_machine::instance()->set_state(Mode::Removing);
		});
	Publisher::instance()->subscribe(Event::Remove_complete, [&](Context& p_context) {
		jgl::cout << "Removing complete" << jgl::endl;
		State_machine::instance()->set_state(Mode::Default);
		});

	State_machine::instance()->add_activity(Mode::Default, new Default_activity(this));
	State_machine::instance()->add_activity(Mode::Selection, new Selection_activity(this));
	State_machine::instance()->add_activity(Mode::Placement, new Placement_activity(this));
	State_machine::instance()->add_activity(Mode::Removing, new Removing_activity(this));

	Publisher::instance()->notify(Event::Go_default);

	_menu->desactivate();
	_message_output->activate();
	_message_output->set_text(0, "No entity selected");
}

void NPC_creator_interface::place_entity()
{
	_entity->place(convert_screen_to_world(jgl::Application::active_application()->mouse().pos()));
	_menu->set_position(_entity->pos());
}

void NPC_creator_interface::select_entity()
{
	jgl::Vector2Int mouse_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

	Entity* tmp_entity = Engine::instance()->entity_collision(nullptr, mouse_pos);

	if (tmp_entity != _entity)
	{
		//delete _entity;
		_entity = reinterpret_cast<AI_controlled_entity*>(tmp_entity);
	
		if (_entity == nullptr)
		{
			_menu->desactivate();
			_message_output->activate();
			_message_output->set_text(0, "No entity selected");
		}
		else
		{
			_menu->import_entity(_entity);
			_menu->activate();
			_message_output->desactivate();
		}
	}
}

void NPC_creator_interface::_send_entity_suppression_request(jgl::Long p_id)
{
	static Message msg(Server_message::Entity_suppression_request);

	msg.clear();

	msg << p_id;

	Client_manager::client()->send(msg);
}

void NPC_creator_interface::remove_entity()
{
	jgl::Vector2Int mouse_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

	Entity* tmp_entity = Engine::instance()->entity_collision(nullptr, mouse_pos);

	if (tmp_entity != nullptr)
	{
		_send_entity_suppression_request(tmp_entity->id());
	}
}

void NPC_creator_interface::reset_data()
{
	_new_entity->set_name("New entity");
	_new_entity->set_id(-1);
	_entity = _new_entity;
	_entity->place(Engine::instance()->player()->pos() + jgl::Vector2(0, 1));
	_menu->reset_data();
	_menu->entity_name_entry()->set_text(_entity->name());
	_menu->set_position(_entity->pos());
	_menu->activate();
	_message_output->desactivate();
}

void NPC_creator_interface::_send_entity_modification_AI_controlled_entity(Message& p_msg, AI_controlled_entity* p_entity)
{
	p_msg << p_entity->movement_info().pattern;

	if (p_entity->movement_info().pattern == AI_controlled_entity::Movement_info::Pattern::Wander)
	{
		p_msg << p_entity->movement_info().data.range;
	}
	else if (p_entity->movement_info().pattern == AI_controlled_entity::Movement_info::Pattern::Path)
	{
		for (jgl::Size_t i = 0; i < p_entity->movement_info().data.path.size(); i++)
		{
			p_msg << p_entity->movement_info().data.path[i];
		}
	}
}

void NPC_creator_interface::_send_entity_modification_Spawner(Message& p_msg, Spawner* p_entity)
{

}

void NPC_creator_interface::_send_entity_modification(Entity* p_entity)
{
	static Message result(Server_message::Entity_modification);

	if (p_entity == nullptr)
		return;

	result.clear();

	result << p_entity->type();
	result << p_entity->id();
	result << p_entity->name();
	result << p_entity->pos();

	if (p_entity->type() == Entity::Type::NPC || p_entity->type() == Entity::Type::Enemy)
	{
		_send_entity_modification_AI_controlled_entity(result, reinterpret_cast<AI_controlled_entity* > (p_entity));
	}
	else if (p_entity->type() == Entity::Type::Spawner)
	{
		_send_entity_modification_Spawner(result, reinterpret_cast<Spawner*> (p_entity));
	}

	Client_manager::instance()->client()->send(result);
}

void NPC_creator_interface::set_entity_id(jgl::Long p_id)
{
	_entity = reinterpret_cast<AI_controlled_entity *>(Engine::instance()->entity_collision(nullptr, _entity->pos()));
}

void NPC_creator_interface::set_entity_name(jgl::String p_name)
{
	if (_entity != nullptr)
	{
		_entity->set_name(p_name);
		if (_entity->id() != -1)
			_send_entity_modification(_entity);
	}
}

void NPC_creator_interface::set_entity_type(Entity::Type& p_type)
{
	if (_entity != nullptr)
	{
		_entity->set_type(p_type);
		if (_entity->id() != -1)
			_send_entity_modification(_entity);
	}
}

void NPC_creator_interface::set_movement_pattern(AI_controlled_entity::Movement_info::Pattern& p_type)
{
	if (_entity != nullptr)
	{
		static_cast<AI_controlled_entity *>(_entity)->movement_info().pattern = p_type;
		if (_entity->id() != -1)
			_send_entity_modification(_entity);
	}
}