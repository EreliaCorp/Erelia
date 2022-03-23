#include "Structure/File/erelia_player_save_file.h"
#include "Structure/Atlas/erelia_path_atlas.h"
#include "structure/Data/Account/erelia_account.h"

Account* Player_file::load(jgl::String p_path)
{
	Account* tmp_account = new Account();

	jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

	static jgl::Array<jgl::String> tab;

	tmp_account->username = jgl::get_str(file);
	tmp_account->password = jgl::get_str(file);

	tab = jgl::get_strsplit(file, "/");

	tmp_account->pos = jgl::Vector2(jgl::stof(tab[0]), jgl::stof(tab[1]));

	file.close();

	return (tmp_account);
}

void Player_file::save(jgl::String p_path, Account* p_account)
{
	jgl::File file = jgl::open_file(p_path + p_account->username + Path_atlas::player_save_extension, jgl::File_mode::out);

	file << p_account->username << std::endl;
	file << p_account->password << std::endl;

	file << p_account->pos.x << "/" << p_account->pos.y << std::endl;

	file.close();
}
