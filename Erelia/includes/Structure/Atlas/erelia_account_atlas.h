#pragma once

#include "jgl.h"
#include "Network/erelia_network_definition.h"
#include "Structure/Data/Account/erelia_account.h"
#include "Structure/File/erelia_player_save_file.h"

class Account_atlas : public jgl::Singleton<Account_atlas>
{
private:
	jgl::Map<jgl::String, Account*> _accounts;
	jgl::Map<jgl::Ulong, Account*> _active_accounts;

	Account_atlas();

public:
	void load();
	void save();

	jgl::Map<jgl::String, Account*>& accounts() { return (_accounts); }

	Account* account(jgl::String p_username);
	void add_account(Account* p_account);
	void add_account(jgl::String p_username, jgl::String p_password);

	jgl::Map<jgl::Ulong, Account*>& active_accounts() { return (_active_accounts); }
	Account* active_account(jgl::Ulong p_id);

	void activate_account(Account* p_account);

	void desactivate_account(Account* p_account);
	void desactivate_account(jgl::Ulong p_id);

	void actualize_player_data();
};