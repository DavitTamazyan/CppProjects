#pragma once

#include<iostream>
#include<vector>

class LogRegSys
{
private:
	struct LogPasPair
	{
		std::string m_login;
		std::string m_password;
		int 		m_id;
	};

	enum class Warning { OK, LOGINEXIST, LOGININCORRECT, LOGINSHORT, PASSWORDINCORRECT, PASSWORDUNSAFE, PASSWORDSHORT };

	Warning LoginCheck(std::string username);

	Warning PasswordCheck(std::string password);

	std::vector<LogPasPair> m_data;
	uint8_t m_count = 0;
public:
	LogRegSys();
	~LogRegSys();
	Warning AddUserGUI();
	Warning AddUser(std::string username, std::string password);
	Warning DeleteUser(std::string username);
	bool IsUserExist(std::string username);
	void TestPrint();
};

