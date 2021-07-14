#include"LogRegSys.h"

int main()
{
	LogRegSys a;

	a.AddUser("short", "Aa1&");
	a.AddUser("long", "qwertyui");
	a.AddUser("short", "Aa1&0000");
	a.AddUser("username", "qwertyui");

	a.TestPrint();

	a.DeleteUser("long");
	a.DeleteUser("short");

	a.TestPrint();
}
