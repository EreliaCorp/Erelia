#pragma once

#include "Network/erelia_network_definition.h"
#include "Structure/Data/Account/erelia_account.h"

class Account_atlas
{
private:
	jgl::Map<jgl::String, Account*> _accounts;
	jgl::Map<jgl::Ulong, Account*> _active_accounts;

	Account_atlas();

	static Account_atlas* _instance;

public:
	Account* account(jgl::String p_username);
	void add_account(jgl::String p_username, jgl::String p_password);

	Account* active_account(jgl::Ulong p_id);

	void activate_account(Account* p_account);

	void desactivate_account(Account* p_account);
	void desactivate_account(jgl::Ulong p_id);
	
	static Account_atlas* instanciate();
	static Account_atlas* instance();
};