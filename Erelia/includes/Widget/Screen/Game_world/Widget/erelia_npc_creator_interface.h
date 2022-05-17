#pragma once

#include "jgl.h"

#include "widget/abstract_widget/erelia_overworld_widget.h"
#include "widget/Commun/erelia_slider_widget.h"
#include "structure/data/Entity/erelia_AI_controlled_entity.h"
#include "structure/data/Entity/erelia_Spawner.h"
#include "network/erelia_client_manager.h"

class NPC_creator_interface : public Overworld_widget, public jgl::Singleton_widget<NPC_creator_interface>
{
public:
	friend class jgl::Singleton_widget<NPC_creator_interface>;
	enum class Mode
	{
		Default = 0,
		Selection = 1,
		Placement = 2,
		Removing = 3
	};
	enum class Event
	{
		Go_default = 0,
		Go_selecter = 1,
		Selection_complete = 2,
		Go_placement = 3,
		Placement_complete = 4,
		Go_remove = 5,
		Remove_complete
	};
	struct Context
	{

	};

	class Default_activity : public jgl::Abstract_activity
	{
	private:
		NPC_creator_interface* _owner;

	public:
		Default_activity(NPC_creator_interface* p_parent);
		void execute();
		void on_transition();
	};
	class Selection_activity : public jgl::Abstract_activity
	{
	private:
		NPC_creator_interface* _owner;

	public:
		Selection_activity(NPC_creator_interface* p_parent);
		void execute();
		void on_transition();
	};
	class Placement_activity : public jgl::Abstract_activity
	{
	private:
		NPC_creator_interface* _owner;

	public:
		Placement_activity(NPC_creator_interface* p_parent);
		void execute();
		void on_transition();
	};
	class Removing_activity : public jgl::Abstract_activity
	{
	private:
		NPC_creator_interface* _owner;

	public:
		Removing_activity(NPC_creator_interface* p_parent);
		void execute();
		void on_transition();
	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;
	typedef jgl::Singleton< jgl::State_machine<Mode> > State_machine;

private:
	class Contextual_menu : public jgl::Widget
	{
	private:
		jgl::Button* _buttons[4];

		void _on_geometry_change();
		void _render();

	public:
		Contextual_menu(jgl::Widget* p_parent);
		jgl::Button* button(jgl::Size_t p_index);
	};

	class Menu : public jgl::Widget
	{
	private:
		void _on_geometry_change();
		void _render();

		jgl::Text_entry* _entity_name_entry;
		jgl::Text_label* _entity_position_entry;
		jgl::Selecter<Entity::Type>* _npc_type_selecter;
		jgl::Selecter<AI_controlled_entity::Movement_info::Pattern>* _npc_movement_pattern_selecter;

	public:
		Menu(jgl::Widget* p_parent);
		
		void reset_data();
		void import_entity(Entity* p_entity);

		void set_position(jgl::Vector2Int p_pos);

		jgl::Text_entry* entity_name_entry() { return(_entity_name_entry); }

		const jgl::String& entry_name_text();
		
		jgl::Bool entry_active()
		{
			return (_entity_name_entry->is_selected());
		}

	};

	class Entity_renderer : public jgl::Widget
	{
	private:
		jgl::Widget_component::Box _box;
		Entity** _to_render;

		void _on_geometry_change();
		void _render();

	public:
		Entity_renderer(Entity** p_entity, jgl::Widget* p_parent);
	};

	class Message_output : public jgl::Widget {
	private:
		jgl::Text_label* _messages_output[10];

		void _on_geometry_change()
		{
			jgl::Float space = _area.y / 90;
			jgl::Float line_size = (_area.y - space * 9) / 10;

			for (jgl::Size_t i = 0; i < 10; i++)
			{
				_messages_output[i]->set_geometry(jgl::Vector2Int(0, line_size + space) * i, jgl::Vector2Int(_area.x, line_size));
			}
		}
		void _render()
		{

		}

	public:
		Message_output(jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			for (jgl::Size_t i = 0; i < 10; i++)
			{
				_messages_output[i] = new jgl::Text_label("", this);
				_messages_output[i]->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
				_messages_output[i]->label().set_text_color(jgl::Color::red());
				_messages_output[i]->activate();
			}
		}

		void set_text(jgl::Size_t index, jgl::String p_text)
		{
			if (index < 10)
				_messages_output[index]->label().set_text(p_text);
		}
	};

	void _on_geometry_change();
	void _render();
	jgl::Bool _update();

	Entity* _new_entity;
	Entity* _entity;

	Slider* _slider;

	jgl::Button* _slider_button;	
	jgl::Frame* _frame;

	Contextual_menu* _context_menu_left;
	Contextual_menu* _context_menu_right;
	Entity_renderer* _renderer;
	Message_output* _message_output;
	Menu* _menu;
	
	NPC_creator_interface(jgl::Widget* p_parent);

	void _send_entity_modification_AI_controlled_entity(Message& p_msg, AI_controlled_entity* p_entity);
	void _send_entity_modification_Spawner(Message& p_msg, Spawner* p_entity);
	void _send_entity_modification(Entity* p_entity);
	void _send_entity_suppression_request(jgl::Long p_id);

public:
	jgl::Bool entry_active()
	{
		return (_menu->entry_active());
	}

	jgl::Bool is_pointed()
	{
		return (_slider_button->is_pointed() || _frame->is_pointed());
	}

	Entity* entity() { return (_entity); }

	void place_entity();
	void select_entity();
	void remove_entity();

	void reset_data();

	void set_entity_id(jgl::Long p_id);
	void set_entity_name(jgl::String p_name);
	void set_entity_type(Entity::Type& p_type);
	void set_movement_pattern(AI_controlled_entity::Movement_info::Pattern& p_type);
};
