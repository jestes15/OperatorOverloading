#include "UserAccount.h"

#include <format>
#include <iostream>
#include <string>

int main()
 {
 	UserAccount acc1 = UserAccount(3345, 2847);
	UserAccount acc2 = UserAccount(4484, 23784);

	UserAccount acc3 = (acc1 , acc2);

	std::string buffer = std::format("{} {}.", acc3.get_x(), acc3.get_y());
	std::cout << buffer << std::endl;

	UserAccount acc4 = acc1 + acc2;

	++acc1;
 }
