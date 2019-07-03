#pragma once

class String {

public:
	String(const char *init_string);	//conversion constructor
	String(class String &other_string);	//copy constructor

	int string_length();

	//this needs a definition, which was not provided in the original C code
	static int string_case_compare(class String &a, class String &b);	

	class String operator + (class String &other_string);
	class String operator = (class String &other_string);
	class String operator = (const char *other_string);

	int operator - (class String &other_string);
	operator char*();

	char *get_ptr();

	class Exceptions{
	public:
		Exceptions(char *error_type);

	};

	~String();

private:
	char *cstring;
	int mem_size;
	void copy_char(const char *source, char *dest);

};
