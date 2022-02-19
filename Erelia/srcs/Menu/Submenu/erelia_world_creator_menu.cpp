#include "erelia.h"

void World_creator_menu::_on_geometry_change()
{
	jgl::Int space = _area.x / 50;
	jgl::Vector2Int label_size = jgl::Vector2Int(_area.x / 12, _area.y / 18);
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / 6, _area.y / 18);
	jgl::Vector2Int entry_size = jgl::Vector2Int(_area.x - space - (space * 3) * 4 - label_size.x, label_size.y);
	jgl::Vector2Int randomizer_size = jgl::Vector2Int(_area.x / 12, _area.y / 18);
	jgl::Vector2Int anchor = (space * 3) * 2;

	_world_name_label->box().set_border_size(label_size.y / 10);
	_world_name_label->set_geometry(anchor + jgl::Vector2Int(0, label_size.y + space) * 0, label_size);

	_world_name_entry->box().set_border_size(entry_size.y / 10);
	_world_name_entry->set_geometry(_world_name_label->anchor() + jgl::Vector2Int(_world_name_label->area().x + space, 0), entry_size);

	_world_seed_label->box().set_border_size(label_size.y / 10);
	_world_seed_label->set_geometry(anchor + jgl::Vector2Int(0, label_size.y + space) * 1, label_size);

	_world_seed_entry->box().set_border_size(entry_size.y / 10);
	_world_seed_entry->set_geometry(_world_seed_label->anchor() + jgl::Vector2Int(_world_seed_label->area().x + space, 0), entry_size - jgl::Vector2Int(randomizer_size.x + space, 0));

	_world_seed_randomizer_button->selected_box().set_border_size(button_size.y / 10);
	_world_seed_randomizer_button->unselected_box().set_border_size(button_size.y / 10);
	_world_seed_randomizer_button->set_geometry(_world_seed_entry->anchor() + jgl::Vector2Int(_world_seed_entry->area().x + space, 0), randomizer_size);

	_cancel_world_creation_button->selected_box().set_border_size(button_size.y / 10);
	_cancel_world_creation_button->unselected_box().set_border_size(button_size.y / 10);
	_confirm_world_creation_button->set_geometry(_area - anchor - button_size, button_size);

	_cancel_world_creation_button->selected_box().set_border_size(button_size.y / 10);
	_cancel_world_creation_button->unselected_box().set_border_size(button_size.y / 10);
	_cancel_world_creation_button->set_geometry(_area - anchor - button_size - jgl::Vector2Int(button_size.x * 1.2f, 0), button_size);
}

void World_creator_menu::_render()
{

}

void World_creator_menu::start()
{
	_world_name_entry->set_text("New World");

	jgl::Int seed = jgl::generate_nbr(100000000, 999999999);
	_world_seed_entry->set_text(jgl::itoa(seed));
}

World_creator_menu::World_creator_menu(std::function< void(jgl::Data_contener&) > p_funct_confirm, std::function< void(jgl::Data_contener&) > p_funct_cancel, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_world_name_label = new jgl::Text_label("World name : ", this);
	_world_name_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_world_name_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_world_name_label->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_world_name_label->activate();

	_world_name_entry = new jgl::Text_entry("", this);
	_world_name_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_world_name_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_world_name_entry->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_world_name_entry->activate();

	_world_seed_label = new jgl::Text_label("World seed :", this);
	_world_seed_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_world_seed_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_world_seed_label->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_world_seed_label->activate();

	_world_seed_entry = new jgl::Text_entry("", this);
	_world_seed_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_world_seed_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_world_seed_entry->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_world_seed_entry->activate();

	_world_seed_randomizer_button = new jgl::Button([&](jgl::Data_contener& p_param) {
		jgl::Int seed = jgl::generate_nbr(100000000, 999999999);
		_world_seed_entry->set_text(jgl::itoa(seed));
		},
		this);
	_world_seed_randomizer_button->label().set_text("Randomize");
	_world_seed_randomizer_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_world_seed_randomizer_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_world_seed_randomizer_button->activate();

	_confirm_world_creation_button = new jgl::Button(p_funct_confirm, this);
	_confirm_world_creation_button->label().set_text("Confirm");
	_confirm_world_creation_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_confirm_world_creation_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_confirm_world_creation_button->activate();

	_cancel_world_creation_button = new jgl::Button(p_funct_cancel, this);
	_cancel_world_creation_button->label().set_text("Cancel");
	_cancel_world_creation_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_cancel_world_creation_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_cancel_world_creation_button->activate();
}