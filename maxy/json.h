#pragma once
#ifndef _MAXY_DATA_JSON
#define _MAXY_DATA_JSON
#include <sstream>
#include <map>
#include <vector>

namespace maxy
{
	namespace data
	{
		class json
		{
			public: class iterator;
			private:

			// types
			using iterator_type = iterator;
			using object_container_type = std::map<std::string, json>;
			using array_container_type = std::vector<json>;

			// Type of this json
			enum class json_type { Empty, Null, False, True, NumberInt, NumberFloat, String, Array, Object };
			json_type type;

			// Value storage
			object_container_type object_elements;
			array_container_type array_elements;
			std::string string_value;
			long long int_value;
			long double float_value;

			// Error
			enum class json_error { None, InvalidatedIterator, ParseError, OutOfRange, };
			json_error error;

			// Parsing
			static char skip_whitespace (std::istream & is);
			static std::pair<json, char> read_string (std::istream & is, char first);
			static std::pair<json, char> read_token (std::istream & is, char first);
			static json from_token (const std::string s);
			static std::pair<json, char> parse_value (std::istream & is, char first = 0);

			public:

			// Factories
			static json make_array () { json j{}; j.type = json_type::Array; return j; }
			static json make_object () { json j{}; j.type = json_type::Object; return j; }
			static json make_error (json_error err = json_error::ParseError)
			{
				json j{}; 
				j.type = json_type::Empty; 
				j.error = err;
				return j;
			}

			// copy and move operations are all default
			json (const json &) = default;
			json (json &&) = default;
			json & operator= (const json &) = default;
			json & operator= (json &&) = default;

			// Destructor
			~json () = default;

			// Constructors
			json () : type{json_type::Empty}, error{json_error::None} {}
			json (const std::string & s) : type{json_type::String}, string_value{s}, error{json_error::None} {}
			json (long long n) : type{json_type::NumberInt}, error{json_error::None} { int_value = n; }
			json (long double n) : type{json_type::NumberFloat}, error{json_error::None} { float_value = n; }
			json (bool n) : error{json_error::None} { if (n) { type = json_type::True; } else { type = json_type::False; } }
			json (const char * const p) : error{json_error::None}
			{
				if (p) { type = json_type::String; string_value = p; }
				else { type = json_type::Null; }
			}

			void clear ()
			{
				array_elements.clear ();
				object_elements.clear ();
			}

			// state checkers
			bool is_empty () { return type == json_type::Empty; }
			bool is_ok () { return error == json_error::None; }

			// parse from a string
			static json parse (const std::string & s);
			static json parse (std::istream & is);

			// conversion operators
			explicit operator bool () const;
			explicit operator int () const { return static_cast<int>(int_value); }
			explicit operator long () const { return static_cast<long>(int_value); }
			explicit operator long long () const { return int_value; }
			explicit operator float () const { return static_cast<float>(float_value); }
			explicit operator double () const { return static_cast<double>(float_value); }
			explicit operator long double () const { return float_value; }
			explicit operator const std::string () const { return string_value; }

			// equalities
			bool operator== (const char * const p) const noexcept;
			bool operator== (long long other) const noexcept;
			bool operator== (long double other) const noexcept;
			bool operator== (const std::string & other) const noexcept;
			bool operator== (const json & other) const noexcept;
			bool operator!= (const char * const p) const noexcept { return !(*this == p); }
			bool operator!= (long long other) const noexcept { return !(*this == other); }
			bool operator!= (long double other) const noexcept { return !(*this == other); }
			bool operator!= (const std::string & other) const noexcept { return !(*this == other); }
			bool operator!= (const json & other) const noexcept { return !(*this == other); }

			// assignments
			json & operator= (int n);
			json & operator= (long n);
			json & operator= (long long n);
			json & operator= (float n);
			json & operator= (double n);
			json & operator= (long double n);
			json & operator= (const std::string & n);
			json & operator= (const char * const p);
			json & operator= (bool n);

			// map-like access for objects
			json & operator[] (const char * const c);
			json & operator[] (const std::string & key);
			json & operator[] (size_t n);

			// stack-like array access
			json & push_back (json j);
			json pop_back ();

			// Iterators
			class iterator
			{
				// exceptions
				struct invalidated {};
				struct out_of_range {};

				// referenced object
				json & ref;
				// object type at iterator construction
				// type change invalidates the iterator
				json_type initial_type;
				// iterator of object_elements
				std::map<std::string, json>::iterator object_iterator;
				// use integer pointer instead of array_elements iterator
				size_t ptr;

				public:
				// construction and destruction
				iterator (json & j, size_t p = 0);
				~iterator () = default;
				iterator (const iterator & i) = default;
				iterator (iterator && i) = default;

				// assignments
				iterator & operator= (const iterator & i) = default;
				iterator & operator= (iterator && i) = default;

				// increments and decrements
				iterator & operator++ ();
				iterator & operator-- ();
				iterator operator++ (int);
				iterator operator-- (int);

				// comparison
				bool operator== (iterator & other) const;
				bool operator!= (iterator & other) const { return !(*this == other); }

				// dereferencing
				std::pair<const std::string, json &> operator* () const;
			};

			// begin iterator
			iterator begin ();

			// end iterator
			iterator end ();

			// string output
			friend std::ostream & operator<< (std::ostream & os, const json & j);
		};
	}
}

#endif // _MAXY_DATA_JSON
