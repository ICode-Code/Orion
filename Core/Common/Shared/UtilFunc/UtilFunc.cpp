#include "UtilFunc.h"


namespace OE1Core
{
	namespace Util
	{
		std::string UtilFunc::CheckNameCollision(std::string _name, std::function<bool(std::string)> _cmp)
		{
			while (_cmp(_name))
			{
				// If the last char is not ) it means this isthe first instance
				if (_name.back() != ')')
					_name += "(1)";
				else
				{
					// If the code reach here it means the name is modefied with (index)
					// so we need to extract this index and increament it
					size_t last_open_index = _name.find_last_of('(');
					size_t last_close_index = _name.find_last_of(')');

					size_t index_digit_count = last_close_index - last_open_index;
					std::string digit = _name.substr(last_open_index + 1, index_digit_count);
					_name.replace(last_open_index + 1, index_digit_count - 1, std::to_string(std::stoi(digit) + 1));
				}
			}

			return _name;
		}
	}
}