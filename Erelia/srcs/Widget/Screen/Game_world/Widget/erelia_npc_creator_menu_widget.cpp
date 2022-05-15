#include "widget/Screen/game_world/widget/erelia_npc_creator_interface.h"

void NPC_creator_interface::Menu::_on_geometry_change()
{
	jgl::Float space = _area.y / 90;
	jgl::Float line_size = (_area.y - space * 9) / 10;
	jgl::Vector2 pos = 0;
	jgl::Vector2 entry_size = jgl::Vector2(_area.x, line_size);

	_entity_name_entry->set_geometry(pos, entry_size);
	pos.y += line_size + space;

	_entity_position_entry->set_geometry(pos, entry_size);
	pos.y += line_size + space;

	_npc_type_selecter->set_geometry(pos, entry_size);
	pos.y += line_size + space;

	_npc_movement_pattern_selecter->set_geometry(pos, entry_size);
}

void NPC_creator_interface::Menu::_render()
{

}

void NPC_creator_interface::Menu::set_position(jgl::Vector2Int p_pos)
{
	_entity_position_entry->label().set_text("Position : " + p_pos.text());
}

void NPC_creator_interface::Menu::reset_data()
{
	_entity_name_entry->set_text("New entity");
	_npc_type_selecter->set_index(0);
	_npc_movement_pattern_selecter->set_index(0);
}

void NPC_creator_interface::Menu::import_entity(Entity* p_entity)
{
	_entity_name_entry->set_text(p_entity->name());
	set_position(p_entity->pos());
	_npc_type_selecter->set_index(static_cast<jgl::Int>(p_entity->type()));
	if (p_entity->type() == Entity::Type::NPC || p_entity->type() == Entity::Type::Enemy)
	{
		_npc_movement_pattern_selecter->set_index(static_cast<jgl::Int>(reinterpret_cast<AI_controlled_entity*>(p_entity)->movement_info().pattern));
	}
}

const jgl::String& NPC_creator_interface::Menu::entry_name_text()
{
	return (_entity_name_entry->text());
}

NPC_creator_interface::Menu::Menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_entity_name_entry = new jgl::Text_entry("New entity", this);
	_entity_name_entry->activate();

	_entity_position_entry = new jgl::Text_label("Position : ", this);
	_entity_position_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_entity_position_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_entity_position_entry->activate();

	_npc_type_selecter = new jgl::Selecter<Entity::Type>([&](Entity::Type& p_type) {
		NPC_creator_interface::instance()->set_entity_type(p_type);
			if (p_type == Entity::Type::NPC)
				return ("NPC");
			else if (p_type == Entity::Type::Enemy)
				return ("Enemy");
			else if (p_type == Entity::Type::Spawner)
				return ("Spawner");
			else
				return ("Undefined");
		}, this);
	_npc_type_selecter->add_value(Entity::Type::NPC);
	_npc_type_selecter->add_value(Entity::Type::Spawner);
	_npc_type_selecter->add_value(Entity::Type::Enemy);
	_npc_type_selecter->activate();

	_npc_movement_pattern_selecter = new jgl::Selecter<AI_controlled_entity::Movement_info::Pattern>([&](AI_controlled_entity::Movement_info::Pattern& p_type) {
			NPC_creator_interface::instance()->set_movement_pattern(p_type);
			if (p_type == AI_controlled_entity::Movement_info::Pattern::Static)
				return ("Static");
			else if (p_type == AI_controlled_entity::Movement_info::Pattern::Wander)
				return ("Wander");
			else if (p_type == AI_controlled_entity::Movement_info::Pattern::Path)
				return ("Path");
			else
				return ("Undefined");
		}, this);
	_npc_movement_pattern_selecter->add_value(AI_controlled_entity::Movement_info::Pattern::Static);
	_npc_movement_pattern_selecter->add_value(AI_controlled_entity::Movement_info::Pattern::Wander);
	_npc_movement_pattern_selecter->add_value(AI_controlled_entity::Movement_info::Pattern::Path);
	_npc_movement_pattern_selecter->activate();
}