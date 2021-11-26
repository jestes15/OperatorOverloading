
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <numeric>

#if (__cplusplus >= 201103L)
#include <vector>
#include <stdexcept>

template <typename T>
class vector_ext : std::vector<T>
{
public:
	using std::vector<T>::size;
	using std::vector<T>::at;
	using std::vector<T>::vector;
	using std::vector<T>::emplace_back;
	using std::vector<T>::begin;
	using std::vector<T>::end;
	using std::vector<T>::iterator;
	using std::vector<T>::operator[];

	vector_ext<T> operator+(vector_ext<T>& vector_obj)
	{
		if (this->size() != vector_obj.size())
			throw std::runtime_error("Vectors are different sizes");

		vector_ext<T> _ret_vec(this->size());
#ifdef _OPENMP
		#pragma omp parallel for
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) + vector_obj.at(i);
#else
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) + vector_obj.at(i);
#endif
		return _ret_vec;
	}

	vector_ext<T> operator-(vector_ext<T>& vector_obj)
	{
		if (this->size() != vector_obj.size())
			throw std::runtime_error("Vectors are different sizes");

		vector_ext<T> _ret_vec(this->size());
#ifdef _OPENMP
		#pragma omp parallel for
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) - vector_obj.at(i);
#else
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) - vector_obj.at(i);
#endif

		return _ret_vec;
	}

	vector_ext<T> operator*(vector_ext<T>& vector_obj)
	{
		if (this->size() != vector_obj.size())
			throw std::runtime_error("Vectors are different sizes");

		vector_ext<T> _ret_vec(this->size());
#ifdef _OPENMP
		#pragma omp parallel for
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) * vector_obj.at(i);
#else
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) * vector_obj.at(i);
#endif

		return _ret_vec;
	}

	vector_ext<T> operator/(vector_ext<T>& vector_obj)
	{
		if (this->size() != vector_obj.size())
			throw std::runtime_error("Vectors are different sizes");

		vector_ext<T> _ret_vec(this->size());
#ifdef _OPENMP
		#pragma omp parallel for
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) / vector_obj.at(i);
#else
		for (auto i = 0; i < static_cast<int>(_ret_vec.size()); i++)
			_ret_vec[i] = this->at(i) / vector_obj.at(i);
#endif

		return _ret_vec;
	}
};

class file_operations
{
private:
	int _currentNumber = 0;
	bool _emptyFileFlag = false;

	vector_ext<int> _lineNumber = {1};
	vector_ext<int> _upperCaseChar = {0};
	vector_ext<int> _lowerCaseChar = {0};
	vector_ext<int> _digitChar = {0};
	vector_ext<int> _punctuationChar = {0};
	vector_ext<int> _spaceChar = {0};
	vector_ext<int> _otherChar = {0};
	vector_ext<int> _totalChar = {0};

	vector_ext<int> _totals = {0, 0, 0, 0, 0, 0, 0};
	vector_ext<double> _percents = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

	std::fstream _stream;

	void _openFile() noexcept
	{
		std::cout << std::endl;
		std::string name;
		do
		{
			std::cout << "Enter in the name of the input file: ";
			std::cin >> name;
			std::cout << name << std::endl << std::endl;
			this->_stream.open(name, std::ios::in);

			if (!this->_stream)
			{
				std::cout << "*************** File Open Error ***************" << std::endl <<
					"==> Input file failed to open properly!!" << std::endl <<
					"==> Attempted to open file: " << name << std::endl <<
					"==> Please try again..." << std::endl <<
					"***********************************************" << std::endl << std::endl;
			}
		}
		while (!this->_stream);
	}
	void _addToVector()
	{
		this->_lineNumber.emplace_back(0);
		this->_upperCaseChar.emplace_back(0);
		this->_lowerCaseChar.emplace_back(0);
		this->_digitChar.emplace_back(0);
		this->_punctuationChar.emplace_back(0);
		this->_spaceChar.emplace_back(0);
		this->_otherChar.emplace_back(0);
		this->_totalChar.emplace_back(0);
	}
	void _getTotalForLine()
	{
		this->_totalChar = this->_upperCaseChar + this->_lowerCaseChar + this->_digitChar +
			this->_punctuationChar + this->_spaceChar + this->_otherChar;
	}
	void _getTotal()
	{
		vector_ext<std::pair<vector_ext<int>::iterator, vector_ext<int>::iterator>> _combinational_vector = {
			std::make_pair(std::begin(this->_upperCaseChar), std::end(this->_upperCaseChar)),
			std::make_pair(std::begin(this->_lowerCaseChar), std::end(this->_lowerCaseChar)),
			std::make_pair(std::begin(this->_digitChar), std::end(this->_digitChar)),
			std::make_pair(std::begin(this->_punctuationChar), std::end(this->_punctuationChar)),
			std::make_pair(std::begin(this->_spaceChar), std::end(this->_spaceChar)),
			std::make_pair(std::begin(this->_otherChar), std::end(this->_otherChar)),
			std::make_pair(std::begin(this->_totalChar), std::end(this->_totalChar))
		};

		for (auto i = 0; i < _combinational_vector.size(); i++)
			_totals.at(i) = std::accumulate(std::get<0>(_combinational_vector.at(i)), std::get<1>(_combinational_vector.at(i)), 0);

		for (unsigned i = 0; i < this->_percents.size(); i++)
			this->_percents.at(i) = static_cast<double>(this->_totals.at(i)) / static_cast<double>(this->_totals.at(i)) * 100;
	}
	void static _printHeader()
	{
		std::cout << std::left << std::setw(15) << "Line number" <<
			std::setw(10) << "Upper" <<
			std::setw(10) << "Lower" <<
			std::setw(10) << "Digits" <<
			std::setw(10) << "Punct" <<
			std::setw(10) << "Spaces" <<
			std::setw(10) << "Other" << "Total" << std::endl;

		std::cout << std::left << std::setw(15) << "-----------" <<
			std::setw(10) << "-----" <<
			std::setw(10) << "-----" <<
			std::setw(10) << "------" <<
			std::setw(10) << "-----" <<
			std::setw(10) << "------" <<
			std::setw(10) << "-----" << "-----" << std::endl;
	}
	void _printData()
	{
		for (auto x = 0; x < this->_upperCaseChar.size(); x++)
		{
			std::cout << std::left << std::setw(15) << _lineNumber.at(x) <<
				std::setw(10) << this->_upperCaseChar.at(x) <<
				std::setw(10) << this->_lowerCaseChar.at(x) <<
				std::setw(10) << this->_digitChar.at(x) <<
				std::setw(10) << this->_punctuationChar.at(x) <<
				std::setw(10) << this->_spaceChar.at(x) <<
				std::setw(10) << this->_otherChar.at(x) << this->_totalChar.at(x) << std::endl;
		}
		std::cout << std::string(80, '-') << std::endl;

		std::cout << std::left << std::setw(15) << "Totals" <<
			std::setw(10) << this->_totals.at(0) <<
			std::setw(10) << this->_totals.at(1) <<
			std::setw(10) << this->_totals.at(2) <<
			std::setw(10) << this->_totals.at(3) <<
			std::setw(10) << this->_totals.at(4) <<
			std::setw(10) << this->_totals.at(5) << this->_totals.at(6) << std::endl;

		std::cout << std::fixed << std::setprecision(2) << std::left << std::setw(15) << "Percent" <<
			std::setw(10) << this->_percents.at(0) <<
			std::setw(10) << this->_percents.at(1) <<
			std::setw(10) << this->_percents.at(2) <<
			std::setw(10) << this->_percents.at(3) <<
			std::setw(10) << this->_percents.at(4) <<
			std::setw(10) << this->_percents.at(5) << std::endl << std::endl;
	}
	void _printEmptyFileError()
	{
		std::cout << "************* Input File Is Empty *************" << std::endl <<
			"==> The input file is empty." << std::endl <<
			"==> Terminating the program." << std::endl <<
			"***********************************************" << std::endl << std::endl;
		_emptyFileFlag = true;
	}
	void _getInformation()
	{
		if (this->_stream.eof() || this->_stream.peek() == std::ifstream::traits_type::eof())
		{
			_printEmptyFileError();
			return;
		}

		char s;
		while (!this->_stream.eof())
		{
			while (this->_stream.get(s))
			{
				if (s == 10)
				{
					this->_otherChar[this->_currentNumber]++;
					break;
				}

				if (isspace(s))
					this->_spaceChar[this->_currentNumber]++;
				else if (isalpha(s))
				{
					if (islower(s))
						this->_lowerCaseChar[this->_currentNumber]++;
					else
						this->_upperCaseChar[this->_currentNumber]++;
				}
				else if (isdigit(s))
					this->_digitChar[this->_currentNumber]++;
				else if (ispunct(s))
					this->_punctuationChar[this->_currentNumber]++;
			}

			_getTotalForLine();
			this->_lineNumber[this->_currentNumber] = this->_currentNumber + 1;

			if (this->_stream.eof() || this->_stream.peek() == std::ifstream::traits_type::eof())
				break;

			_currentNumber++;
			_addToVector();
		}
		_getTotal();
	}

public:
	file_operations()
	{
		_openFile();
	}
	void run()
	{
		_getInformation();
		if (_emptyFileFlag) return;
		_printHeader();
		_printData();
	}
	~file_operations()
	{
		this->_stream.close();
	}
};

#else
#include <vector>

class file_operations
{
private:
	int currentNumber = 0;
	bool emptyFileFlag = false;

	std::vector<int> _lineNumber = {1};
	std::vector<int> _upperCaseChar = {0};
	std::vector<int> _lowerCaseChar = {0};
	std::vector<int> _digitChar = {0};
	std::vector<int> _punctuationChar = {0};
	std::vector<int> _spaceChar = {0};
	std::vector<int> _otherChar = {0};
	std::vector<int> _totalChar = {0};

	std::vector<int> _totals = {0, 0, 0, 0, 0, 0, 0};
	std::vector<double> _percents = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

	std::fstream stream;

	void openFile() noexcept
	{
		std::cout << std::endl;
		std::string name;
		do
		{
			std::cout << "Enter in the name of the input file: ";
			std::cin >> name;
			std::cout << name << std::endl << std::endl;
			this->stream.open(name, std::ios::in);

			if (!this->stream)
			{
				std::cout << "*************** File Open Error ***************" << std::endl <<
					"==> Input file failed to open properly!!" << std::endl <<
					"==> Attempted to open file: " << name << std::endl <<
					"==> Please try again..." << std::endl <<
					"***********************************************" << std::endl << std::endl;
			}
		}
		while (!this->stream);
	}
	void addToVector()
	{
		this->_lineNumber.emplace_back(0);
		this->_upperCaseChar.emplace_back(0);
		this->_lowerCaseChar.emplace_back(0);
		this->_digitChar.emplace_back(0);
		this->_punctuationChar.emplace_back(0);
		this->_spaceChar.emplace_back(0);
		this->_otherChar.emplace_back(0);
		this->_totalChar.emplace_back(0);
	}
	void getTotalForLine()
	{
		this->_totalChar[this->currentNumber] = this->_upperCaseChar[this->currentNumber] + this->_lowerCaseChar[this->
				currentNumber] + this->_digitChar[this->currentNumber] +
			this->_punctuationChar[this->currentNumber] + this->_spaceChar[this->currentNumber] + this->_otherChar[this
				->currentNumber];
	}
	void getTotal()
	{
		this->_totals[0] = std::accumulate(std::begin(this->_upperCaseChar), std::end(this->_upperCaseChar), 0);
		this->_totals[1] = std::accumulate(std::begin(this->_lowerCaseChar), std::end(this->_lowerCaseChar), 0);
		this->_totals[2] = std::accumulate(std::begin(this->_digitChar), std::end(this->_digitChar), 0);
		this->_totals[3] = std::accumulate(std::begin(this->_punctuationChar), std::end(this->_punctuationChar), 0);
		this->_totals[4] = std::accumulate(std::begin(this->_spaceChar), std::end(this->_spaceChar), 0);
		this->_totals[5] = std::accumulate(std::begin(this->_otherChar), std::end(this->_otherChar), 0);
		this->_totals[6] = std::accumulate(std::begin(this->_totalChar), std::end(this->_totalChar), 0);

		for (unsigned i = 0; i < this->_percents.size(); i++)
			this->_percents[i] = static_cast<double>(this->_totals[i]) / static_cast<double>(this->_totals[6]) * 100;
	}
	void static printHeader()
	{
		std::cout << std::left << std::setw(15) << "Line number" <<
			std::setw(10) << "Upper" <<
			std::setw(10) << "Lower" <<
			std::setw(10) << "Digits" <<
			std::setw(10) << "Punct" <<
			std::setw(10) << "Spaces" <<
			std::setw(10) << "Other" << "Total" << std::endl;

		std::cout << std::left << std::setw(15) << "-----------" <<
			std::setw(10) << "-----" <<
			std::setw(10) << "-----" <<
			std::setw(10) << "------" <<
			std::setw(10) << "-----" <<
			std::setw(10) << "------" <<
			std::setw(10) << "-----" << "-----" << std::endl;
	}
	void printData()
	{
		for (auto x = 0; x < this->_upperCaseChar.size(); x++)
		{
			std::cout << std::left << std::setw(15) << _lineNumber[x] <<
				std::setw(10) << this->_upperCaseChar[x] <<
				std::setw(10) << this->_lowerCaseChar[x] <<
				std::setw(10) << this->_digitChar[x] <<
				std::setw(10) << this->_punctuationChar[x] <<
				std::setw(10) << this->_spaceChar[x] <<
				std::setw(10) << this->_otherChar[x] << this->_totalChar[x] << std::endl;
		}
		std::cout << std::string(80, '-') << std::endl;

		std::cout << std::left << std::setw(15) << "Totals" <<
			std::setw(10) << this->_totals[0] <<
			std::setw(10) << this->_totals[1] <<
			std::setw(10) << this->_totals[2] <<
			std::setw(10) << this->_totals[3] <<
			std::setw(10) << this->_totals[4] <<
			std::setw(10) << this->_totals[5] << this->_totals[6] << std::endl;

		std::cout << std::fixed << std::setprecision(2) << std::left << std::setw(15) << "Percent" <<
			std::setw(10) << this->_percents[0] <<
			std::setw(10) << this->_percents[1] <<
			std::setw(10) << this->_percents[2] <<
			std::setw(10) << this->_percents[3] <<
			std::setw(10) << this->_percents[4] <<
			std::setw(10) << this->_percents[5] << std::endl << std::endl;
	}
	void printEmptyFileError()
	{
		std::cout << "************* Input File Is Empty *************" << std::endl <<
			"==> The input file is empty." << std::endl <<
			"==> Terminating the program." << std::endl <<
			"***********************************************" << std::endl << std::endl;
		emptyFileFlag = true;
	}

public:
	void getInformation()
	{
		if (this->stream.eof() || this->stream.peek() == std::ifstream::traits_type::eof())
		{
			printEmptyFileError();
			return;
		}

		char s;
		while (!this->stream.eof())
		{
			while (this->stream.get(s))
			{
				if (s == 10)
				{
					this->_otherChar[this->currentNumber]++;
					break;
				}

				if (isspace(s))
					this->_spaceChar[this->currentNumber]++;
				else if (isalpha(s))
				{
					if (islower(s))
						this->_lowerCaseChar[this->currentNumber]++;
					else
						this->_upperCaseChar[this->currentNumber]++;
				}
				else if (isdigit(s))
					this->_digitChar[this->currentNumber]++;
				else if (ispunct(s))
					this->_punctuationChar[this->currentNumber]++;
			}

			getTotalForLine();
			this->_lineNumber[this->currentNumber] = this->currentNumber + 1;

			if (this->stream.eof() || this->stream.peek() == std::ifstream::traits_type::eof())
				break;

			currentNumber++;
			addToVector();
		}
		getTotal();
	}

	file_operations()
	{
		openFile();
	}

	void run()
	{
		getInformation();
		if (emptyFileFlag) return;
		printHeader();
		printData();
	}

	~file_operations()
	{
		this->stream.close();
	}
};

#endif

int main()
{
	std::cout << "The C++ version is: " << __cplusplus << std::endl;

	auto* const fileIO = new file_operations();
	fileIO->run();
	delete(fileIO);
	return 0;
}