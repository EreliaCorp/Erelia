#include "widget/Screen/Game_world/Widget/erelia_player_interacter.h"
#include "widget/Screen/Game_world/Widget/erelia_player_interacter_activity.h"
#include "structure/atlas/erelia_texture_atlas.h"
#include "Widget/Commun/erelia_console_manager.h"
#include "network/erelia_network_definition.h"
#include "network/erelia_client_manager.h"
#include "structure/Data/Engine/erelia_engine.h"
#include "structure/Data/Map/erelia_chunk.h"
#include "structure/Data/Map/erelia_node.h"

void Player_interacter::_render()
{
	if ((jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down ||
		jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right) == jgl::Input_status::Down) && _editor_inventory->is_pointed() == false &&
		jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Down)
	{
		jgl::Vector2Int tmp_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

		jgl::Vector2Int start = jgl::Vector2Int::compose_min(_publisher->context()->selected_first_pos, tmp_pos);
		jgl::Vector2Int end = jgl::Vector2Int::compose_max(_publisher->context()->selected_first_pos, tmp_pos) + 1;

		jgl::Vector2Int anchor = convert_world_to_screen(start);
		jgl::Vector2Int size = (end - start) * Node::size;

		jgl::draw_rectangle_color(jgl::Color(255, 255, 255, 120), anchor, size, _depth + 10);
	}
	else if (_editor_inventory->selected_item() != nullptr && _editor_inventory->selected_item()->type == Item_type::Flag)
	{
		for (auto tmp : Flag_item::pos)
		{
			Texture_atlas::instance()->UI_sprite_sheet()->draw(Flag_item::sprite(tmp.first), convert_world_to_screen(tmp.second), Node::size, Chunk::C_LAYER_LENGTH + 1, 1.0f);
		}
	}
}

void Player_interacter::_on_geometry_change()
{
	_editor_inventory->set_geometry(0, _area);
}

void Player_interacter::compose_pos(jgl::Vector3Int& p_actual, jgl::Vector3Int& p_start, jgl::Vector3Int& p_end)
{
	jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

	jgl::Vector2Int start = jgl::Vector2Int::compose_min(_publisher->context()->selected_first_pos, tmp_second_pos);
	jgl::Vector2Int end = jgl::Vector2Int::compose_max(_publisher->context()->selected_first_pos, tmp_second_pos);

	p_actual = jgl::Vector3Int(tmp_second_pos.x, tmp_second_pos.y, _editor_inventory->selected_level());
	p_start = jgl::Vector3Int(start.x, start.y, _editor_inventory->selected_level());
	p_end = jgl::Vector3Int(end.x, end.y, _editor_inventory->selected_level());
}

void Player_interacter::compose_pos(jgl::Vector2Int& p_actual, jgl::Vector2Int& p_start, jgl::Vector2Int& p_end)
{
	jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

	jgl::Vector2Int start = jgl::Vector2Int::compose_min(_publisher->context()->selected_first_pos, tmp_second_pos);
	jgl::Vector2Int end = jgl::Vector2Int::compose_max(_publisher->context()->selected_first_pos, tmp_second_pos);

	p_actual = jgl::Vector2Int(tmp_second_pos.x, tmp_second_pos.y);
	p_start = jgl::Vector2Int(start.x, start.y);
	p_end = jgl::Vector2Int(end.x, end.y);
}

void Player_interacter::_receive_brush_size_change(Message& p_msg)
{
	jgl::Uchar value;

	p_msg >> value;

	set_brush_radius(value);
}

void Player_interacter::_receive_brush_type_change(Message& p_msg)
{
	Player_interacter::Brush_type value;

	p_msg >> value;

	set_brush_type(value);
}

void Player_interacter::_receive_brush_type_data_change(Message& p_msg)
{
	jgl::String value;

	p_msg >> value;

	set_brush_type_info(value);
}

void Player_interacter::_receive_monster_area_value(Message& p_msg)
{
	jgl::Int value;

	p_msg >> value;

	set_monster_value(value);
}

jgl::Bool Player_interacter::_update()
{
	_state_machine->update();

	if (Server_manager::instance() != nullptr && jgl::Application::active_application()->keyboard().get_key(jgl::Key::F7) == jgl::Input_status::Release)
	{
		Console_manager::instance()->send_global_message("[Systm.] : Saving server's map started - This can take a while");
		Engine::instance()->save();
		Console_manager::instance()->send_global_message("[Systm.] : Saving server's map completed");
	}

	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::H) == jgl::Input_status::Release)
	{
		jgl::Array<jgl::Vector2Int> path;

		Engine::instance()->map()->find_path(path, Engine::instance()->player()->pos(), convert_screen_to_world(jgl::Application::active_application()->mouse().pos()), 50);

		jgl::cout << "Path : " << path << jgl::endl;
	}

	return (false);
}

void Player_interacter::_parse_string_block_data(jgl::Array<Block_replace_data>& p_array, jgl::String p_text)
{
	static jgl::Array<jgl::String> tab;

	p_text.split(tab, "/");

	for (jgl::Size_t i = 0; i < tab.size(); i += 2)
	{
		p_array.push_back(Block_replace_data(jgl::stoi(tab[i + 1]), jgl::stof(tab[i]) * 100));
	}
}

void Player_interacter::set_brush_type_info(jgl::String p_brush_type_info)
{
	_publisher->context()->replace_data.clear();

	static jgl::Array<jgl::String> tab;

	p_brush_type_info.split(tab, " ");

	_parse_string_block_data(_publisher->context()->replace_data.input, tab[0]);
	_parse_string_block_data(_publisher->context()->replace_data.output, tab[1]);
}

void Player_interacter::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Brush_size_message, CLIENT_ACTIVITY{
			_receive_brush_size_change(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Brush_type_message, CLIENT_ACTIVITY{
			_receive_brush_type_change(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Brush_type_data_message, CLIENT_ACTIVITY{
			_receive_brush_type_data_change(p_msg);
		});
}

void Player_interacter::_initialize_server()
{

}

Player_interacter::Player_interacter(jgl::Widget* p_parent) : Overworld_widget(p_parent)
{
	_publisher = new jgl::Publisher<Event, Context>();
	_state_machine = new jgl::State_machine<Mode>();

	_publisher->subscribe(Player_interacter::Event::Go_adventure, [&](Player_interacter::Context& p_context) {_state_machine->set_state(Player_interacter::Mode::Adventure); });
	_publisher->subscribe(Player_interacter::Event::Go_builder, [&](Player_interacter::Context& p_context) {_state_machine->set_state(Player_interacter::Mode::Builder); });
	_publisher->subscribe(Player_interacter::Event::Go_NPC_creator, [&](Player_interacter::Context& p_context) {_state_machine->set_state(Player_interacter::Mode::NPC_creator); });

	_state_machine->add_activity(Player_interacter::Mode::Adventure, new Player_interact_activity::Adventure(this));
	_state_machine->add_activity(Player_interacter::Mode::Builder, new Player_interact_activity::Builder(this));
	_state_machine->add_activity(Player_interacter::Mode::NPC_creator, new Player_interact_activity::NPC_creator(this));

	_editor_inventory = new Editor_inventory(this);
	_editor_inventory->set_depth(_depth + 100);
	_editor_inventory->desactivate();

	_npc_creator_interface = new NPC_creator_interface(this);
	_npc_creator_interface->set_depth(_depth + 100);
	_npc_creator_interface->desactivate();

	_state_machine->set_state(Player_interacter::Mode::Adventure);

	_initiate();
}