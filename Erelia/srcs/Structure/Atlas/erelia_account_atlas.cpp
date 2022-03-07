#include "erelia.h"

Account_atlas* Account_atlas::_instance;

Account_atlas::Account_atlas()
{

}

Account* Account_atlas::account(jgl::String p_username)
{
	if (_accounts.count(p_username) == 0)
		return (nullptr);
	return (_accounts[p_username]);
}

void Account_atlas::add_account(jgl::String p_username, jgl::String p_password)
{
	if (_accounts.count(p_username) == 0)
	{
		_accounts[p_username] = new Account(p_username, p_password);
	}
}

Account* Account_atlas::active_account(jgl::Ulong p_id)
{
	if (_active_accounts.count(p_id) == 0)
		return (nullptr);
	return (_active_accounts[p_id]);
}

void Account_atlas::activate_account(Account* p_account)
{
	_active_accounts[p_account->connection->id()] = p_account;
}

void Account_atlas::desactivate_account(Account* p_account)
{
	if (p_account->connection != nullptr)
	{
		desactivate_account(p_account->connection->id());
	}
}

void Account_atlas::desactivate_account(jgl::Ulong p_id)
{
	if (_active_accounts.count(p_id) != 0)
	{
		_active_accounts[p_id]->connection = nullptr;
		_active_accounts.erase(p_id);
	}
}

Account_atlas* Account_atlas::instanciate()
{
	_instance = new Account_atlas();

	return (_instance);
}

Account_atlas* Account_atlas::instance()
{
	return (_instance);
}