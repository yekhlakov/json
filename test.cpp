#include <string>
#include <iostream>
#include "maxy/json.h"

using json = maxy::data::json;

int main ()
{
	json j;

	// assignment
	j = 3;  std::cout << " Assigned int{3}: " << j << "\n";
	j = 1.7; std::cout << " Assigned float{1.7}: " << j << "\n";

	// conversion
	int x{j};
	for (int i = 0; i < 5; i++) j[i] = i * 100;
	j[5]["a"] = "b";
	j[5]["b"] = 123;
	j[5]["c"] = true;
	j[7]["1234"] = nullptr;
	j.push_back (false);

	std::cout << "populated object:" << j << "\n";

	std::cout << "\nArray iteration\n";

	for (auto it : j)
		std::cout << "first: " << it.first << ", second: " << it.second << "\n";

	std::cout << "\nObject iteration\n";
	for (auto it : j[5])
		std::cout << "first: " << it.first << ", second: " << it.second << "\n";

	auto flt = json::parse ("-12.34E-123");
	std::cout << "parse float: " << flt << "\n";

	std::cout << "Equality: " << (flt == -12.34E-123L) << "\n";

	auto arr = json::parse ("[true,true,]");
	std::cout << "parse array: " << arr << ", is_ok = " << arr.is_ok () << "\n";

	arr.push_back ("push");
	std::cout << "push_back: " << arr << "\n";

	auto popped = arr.pop_back ();
	std::cout << "pop_back: " << arr << ", popped = " << popped << "\n";

	auto obj = json::parse ("{\"a\":true, \"b\":[1,2,],}");
	std::cout << "parse object: " << obj << ", is_ok = " << obj.is_ok() << "\n";

	auto err = json::parse ("ckpa8j,qwefasd\"mvif.qwe!#@[");
	std::cout << "parse trash string: " << err << ", is_ok = " << err.is_ok () << "\n";

	json cpy = obj;
	std::cout << "Copied object: " << cpy << "\n";

	std::cout << "Object and copy equality: " << (obj == cpy) << "\n";
	cpy["new_field"] = 666;
	std::cout << "Modified copy " << cpy << ", equality: " << (obj == cpy) << "\n";

	json uni = json::parse ("[\"csaka\\x20\\\"quote\", \"U=\\u20AA!\"]");
	std::cout << "Unicode: " << uni << "\n";

	json x1 = json::parse ("{\"quote\\\"key\":123, inner: [{}, {\"a\" : \"b\"}]}");
	std::cout << "Relaxed input: " << x1 << ", is_ok = " << x1.is_ok () << "\n";

}
