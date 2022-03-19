#include "erelia.h"

Account* Player_file::load(jgl::String p_path)
{
	Account* tmp_account = new Account();

	jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

	static jgl::Array<jgl::String> tab;

	tmp_account->username = jgl::get_str(file);
	tmp_account->password = jgl::get_str(file);

	tab = jgl::get_strsplit(file, "/");

	tmp_account->pos = jgl::Vector2(jgl::stof(tab[0]), jgl::stof(tab[1]));

	for (jgl::Size_t i = 0; i < 6; i++)
	{
		jgl::String line = jgl::get_str(file);

		if (line == "-1")
			tmp_account->monsters[i] = nullptr;
		else
		{
			jgl::cout << "Line : " << line << jgl::endl;
			line.split(tab, ";");
			jgl::cout << "Tab : " << line << jgl::endl;

			jgl::Int id = jgl::stoi(tab[0]);
			jgl::String name = tab[1];
			jgl::Size_t level = jgl::stoi(tab[2]);

			jgl::cout << "Asking for " << id << " (" << name << ")" << jgl::endl;

			Monster* tmp_monster = Monster_atlas::instance()->monster(id);

			if (tmp_monster != nullptr)
			{
				jgl::cout << "Monster found !" << jgl::endl;
				jgl::cout << tmp_monster->id() << jgl::endl;
				jgl::cout << name << jgl::endl;
				jgl::cout << level << jgl::endl;
				tmp_account->monsters[i] = tmp_monster->instanciate();
				tmp_account->monsters[i]->set_name(name);
				tmp_account->monsters[i]->set_level(level);
			}
		}
	}

	file.close();

	return (tmp_account);
}

void Player_file::save(jgl::String p_path, Account* p_account)
{
	jgl::File file = jgl::open_file(p_path + p_account->username + Path_atlas::player_save_extension, jgl::File_mode::out);

	file << p_account->username << std::endl;
	file << p_account->password << std::endl;

	file << p_account->pos.x << "/" << p_account->pos.y << std::endl;

	for (jgl::Size_t i = 0; i < 6; i++)
	{
		if (p_account->monsters[i] != nullptr)
		{
			jgl::cout << "Monster name : " << p_account->monsters[i]->name() << jgl::endl;
			file << p_account->monsters[i]->id() << ";" << p_account->monsters[i]->name() << ";" << p_account->monsters[i]->level() << std::endl;
		}
		else
			file << "-1" << std::endl;
	}

	file.close();
}
