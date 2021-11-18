#pragma once
#include <cstdlib>

class UserAccount
{
private:
	int x;
	int y;
public:

	UserAccount(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	UserAccount()
	{
		this->x = 6;
		this->y = 22;
	}

	void set_x(int x)
	{
		this->x = x;
	}
	 void set_y(int y)
	{
		this->y = y;
	}

	int get_x()
	{
		return this->x;
	}
	 int get_y()
	{
		return this->y;
	}


	UserAccount operator,(UserAccount& const b)
	{
		UserAccount acc;
		acc.x = this->x + b.x;
		acc.y = this->y + b.y;
		return acc;
	}

	UserAccount operator+(UserAccount& const b)
	{
		UserAccount acc;
		acc.x = this->x * b.x;
		acc.y = this->y / b.y;

		int volatile * const p_reg = reinterpret_cast<int*>(0x0);
		*p_reg = acc.get_x() + acc.get_y();

		return acc;
	}

	void operator++()
	{
		this->x++;
		this->y++;
		exit(1);
	}

	void operator++(int)
	{
		this->x++;
		this->y++;
		exit(1);
	}
};
