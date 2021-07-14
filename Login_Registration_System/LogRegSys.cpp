#include "LogRegSys.h"

LogRegSys::Warning LogRegSys::LoginCheck(std::string username)
{
	if (username.size() < 5)
	{
		std::cout << "error code1 : Login Short" << std::endl;
		return Warning::LOGINSHORT;
	}
	if (IsUserExist(username))
	{
		std::cout << "error code2 : Login Exist" << std::endl;
		return Warning::LOGINEXIST;
	}
	for (char& c : username)
	{
		if (!isalpha(c))
		{
			std::cout << "error code3 : Login Incorrect" << std::endl;
			return Warning::LOGININCORRECT;
		}
	}
	return Warning::OK;
}

LogRegSys::Warning LogRegSys::PasswordCheck(std::string password)
{
	int reg0 = 0; // bit 0 -> A, bit 1 -> a, bit 2 -> 1, bit 3 -> $

	if (password.size() < 8)
	{
		std::cout << "error code4 : Password Short" << std::endl;
		return Warning::PASSWORDSHORT;
	}

	for (char& c : password)
	{
		if (65 <= c && c <= 90)
		{
			reg0 |= 1;
			continue;
		}
		if (97 <= c && c <= 122)
		{
			reg0 |= 2;
			continue;
		}
		if (48 <= c && c <= 57)
		{
			reg0 |= 4;
			continue;
		}
		if (33 <= c && c <= 47)
		{
			reg0 |= 8;
			continue;
		}
		std::cout << "error code5 : Password Incorrect" << std::endl;
		return Warning::PASSWORDINCORRECT;
	}
	if (reg0 != 15)
	{
		std::cout << "warning code1 : Password Unsafe" << std::endl;
	}

	return (reg0 == 15)? Warning::OK : Warning::PASSWORDUNSAFE;
}

LogRegSys::LogRegSys()
{
}

LogRegSys::~LogRegSys()
{
}

LogRegSys::Warning LogRegSys::AddUserGUI()
{
	std::cout << "--- AddUser Start --- " << std::endl;
	LogPasPair newUser;
	LogRegSys::Warning state;

	std::cout << "Please enter Username : ";
	std::cin >> newUser.m_login;
	std::cout << std::endl;
	
	state = LoginCheck(newUser.m_login);
	if (state != Warning::OK)
	{
		return state;
	}

	std::cout << "Please enter Password : ";
	std::cin >> newUser.m_password;
	std::cout << std::endl;

	state = PasswordCheck(newUser.m_login);

	if (state != Warning::OK && state != Warning::PASSWORDUNSAFE)
	{
		return state;
	}

	newUser.m_id = m_count++;

	m_data.push_back(newUser);

	std::cout << "--- AddUser End --- " << std::endl;
	return Warning::OK;
}

LogRegSys::Warning LogRegSys::AddUser(std::string username, std::string password)
{
	LogPasPair newUser;
	LogRegSys::Warning state;

	std::cout << "Adding user " << username << " : ";

	state = LoginCheck(username);
	if (state != Warning::OK)
	{
		return state;
	}

	state = PasswordCheck(password);

	if (state != Warning::OK && state != Warning::PASSWORDUNSAFE)
	{
		return state;
	}

	newUser.m_id = m_count++;
	newUser.m_login = username;
	newUser.m_password = password;

	m_data.push_back(newUser);

	if (state == Warning::OK)
	{
	std::cout << std::endl;
	}

	return state;
}

LogRegSys::Warning LogRegSys::DeleteUser(std::string username)
{
	size_t size = m_data.size();

	std::cout << "Deleting user " << username << " : ";

	for (int i = 0; i < size; ++i)
	{
		if (m_data[i].m_login == username)
		{
			m_data[i].m_login = "";
			m_data[i].m_password = "";
			std::cout << std::endl;
			return Warning::OK;
		}
	}
	std::cout << "error code5 : login unknown" << std::endl;
	return Warning::LOGININCORRECT;
}

bool LogRegSys::IsUserExist(std::string username)
{
	size_t size = m_data.size();
	
	for (int i = 0; i < size; ++i)
	{
		if (m_data[i].m_login == username)
		{
			return true;
		}
	}

	return false;
}

void LogRegSys::TestPrint()
{
	std::cout << "------------------------------------------" << std::endl;
	for (LogPasPair i : m_data)
	{
		std::cout << "Username = " << i.m_login << std::endl;
		std::cout << "password = " << i.m_password << std::endl;
		std::cout << "ID = " << i.m_id<< std::endl;
	}
	std::cout << "------------------------------------------" << std::endl;
}
