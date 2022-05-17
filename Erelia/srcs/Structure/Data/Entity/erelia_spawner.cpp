#include "structure/data/entity/erelia_Spawner.h"

Spawner::Spawner(jgl::String p_name, jgl::Long p_id) : Entity(p_name, Entity::Type::Spawner, p_id)
{

}

void Spawner::update()
{

}

template<typename T>
void write_data(jgl::File& p_file, T data)
{
	p_file.write(reinterpret_cast<char*>(&(data)), sizeof(T));
}

template<typename T>
void read_data(jgl::File& p_file, T& data)
{
	p_file.read(reinterpret_cast<char*>(&(data)), sizeof(T));
}

void Spawner::save(jgl::File& p_file)
{
	write_data(p_file, _name.size());
	for (jgl::Size_t i = 0; i < _name.size(); i++)
	{
		write_data(p_file, _name[i]);
	}

	write_data(p_file, _type);
	write_data(p_file, _sprite);
	write_data(p_file, _pos);
}

Spawner* Spawner::load(jgl::File& p_file)
{
	jgl::String name;
	Entity::Type type;
	jgl::Vector2Int sprite;
	jgl::Vector2 pos;
	jgl::Size_t len;

	read_data(p_file, len);
	for (jgl::Size_t i = 0; i < len; i++)
	{
		jgl::Glyph tmp;

		read_data(p_file, tmp);
		name.push_back(tmp);
	}

	read_data(p_file, type);
	read_data(p_file, sprite);
	read_data(p_file, pos);

	Spawner* new_entity = new Spawner(name, -1);
	new_entity->place(pos);

	return (new_entity);
}