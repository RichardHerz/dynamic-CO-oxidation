///////////////////////////////////////////////////////////////////////////////
//
// VARIABLE HEADER
//
// This header file defines an abstraction for wrapping a Revolution variable
// name to ease access to its contents.
//

#ifndef __VARIABLE__
#define __VARIABLE__

#ifndef _STRING_
#include <string>
#endif

#ifdef _EXCEPTION_
#include <exception>
#endif

#ifndef __EXTERNAL__
#include <revolution/external.h>
#endif

#ifndef __UTILITY__
#include "utility.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//
// VARIABLE CLASS
//
// The Variable class wraps the name of a Revolution handler-local variable and
// provides a collection of accessors and mutators to make manipulation easier.
//
// Error handling is implicit via the use of exceptions.
//
// To use the wrapper, instantiate an object passing it the name of a Revolution
// variable as a C-string:
//    e.g. Variable t_foo("tFoo");
// 
//    e.g. const char *t_bar_name = "tBar";
//         Variable t_bar(t_bar_name);
//

class Variable
{
public:
	Variable(const char *p_name);
	~Variable(void);

	// Set the value of the variable to an unsigned integer
	//
	void SetUnsignedInteger(unsigned int p_value);

	// Set the value of the variable to a signed integer
	//
	void SetInteger(int p_value);

	// Set the value of the variable to a floating-point number
	//
	void SetReal(double p_value);

	// Set the value of the variable using a stdc++ string
	//
	void SetString(const std::string& p_string);

	// Set the value of the variable using a C-string
	//
	void SetCString(const char *p_string);

	// Set the value of the variable using a raw (binary or text) string
	//
	void SetRawString(const ExternalString& p_raw_string);

	// Set the value of the variable using a buffer and length
	//
	void SetRawBuffer(const void *p_buffer, unsigned int p_length);

	// Coerce the value of the variable to an unsigned integer and
	// return it.
	// If coercion fails, InvalidConversionError will be thrown
	//
	unsigned int GetUnsignedInteger(void);
	
	// Coerce the value of the variable to a signed integer and
	// return it.
	// If coercion fails, InvalidConversionError will be thrown
	//
	int GetInteger(void);

	// Coerce the value of the variable to a floating-point number and
	// return it.
	// If coercion fails, InvalidConversionError will be thrown
	//
	double GetReal(void);
	
	// Fetch the current value of the variable as a stdc++ string and
	// return it.
	//
	std::string GetString(void);

	// Fetch the current value of the variable as a (raw) string and
	// return it.
	// NB: The 'buffer' pointer returned inside the ExternalString here is only
	//     valid until the variable is next changed or control passes back to
	//     Revolution.
	//
	ExternalString GetRawString(void);

	// Ensure the variable is an array then set an element with key <p_key>
	// to the unsigned integer <p_value>.
	//
	void SetUnsignedIntegerElement(const char *p_key, unsigned int p_value);
	
	// Ensure the variable is an array then set an element with key <p_key>
	// to the signed integer <p_value>.
	//
	void SetIntegerElement(const char *p_key, int p_value);

	// Ensure the variable is an array then set an element with key <p_key>
	// to the floating-point number <p_value>.
	//
	void SetRealElement(const char *p_key, double p_value);
	
	// Ensure the variable is an array then set an element with key <p_key>
	// to the stdc++ string <p_value>.
	//
	void SetStringElement(const char *p_key, const std::string& p_string);

	// Ensure the variable is an array then set an element with key <p_key>
	// to the C-string string <p_value>.
	//
	void SetCStringElement(const char *p_key, const char *p_cstring);

	// Ensure the variable is an array then set an element with key <p_key>
	// to the (raw) string <p_value>.
	//
	void SetRawStringElement(const char *p_key, const ExternalString& p_raw_string);
	
	// Ensure the variable is an array then set an element with key <p_key>
	// to the string pointed to by <p_buffer> of length <p_length>.
	//
	void SetRawBufferElement(const char *p_key, const void *p_buffer, unsigned int p_length);

	// Fetch the value of the element with key <p_key> and coerce it an unsigned
	// integer.
	// If coercion fails, InvalidConversionError will be thrown
	// NB: If the key does not exist, or the variable is not an array the value
	//     as a string will be empty, and so a conversion error will result.
	//
	unsigned int GetUnsignedIntegerElement(const char *p_key);

	// Fetch the value of the element with key <p_key> and coerce it an signed
	// integer.
	// If coercion fails, InvalidConversionError will be thrown
	// NB: If the key does not exist, or the variable is not an array the value
	//     as a string will be empty, and so a conversion error will result.
	//
	int GetIntegerElement(const char *p_key);

	// Fetch the value of the element with key <p_key> and coerce it to a floating-
	// point number.
	// If coercion fails, InvalidConversionError will be thrown
	// NB: If the key does not exist, or the variable is not an array the value
	//     as a string will be empty, and so a conversion error will result.
	//
	double GetRealElement(const char *p_key);

  // Fetch the value of the element with key <p_key> and return it as a stdc++
	// string.
	// NB: If the key does not exist, or the variable is not an array, the empty
	//     string will be returned.
	//
	std::string GetStringElement(const char *p_key);
	
	// Fetch the value of the element with key <p_key> and return it as a (raw)
	// string.
	// NB: If the key does not exist, or the variable is not an array, a buffer
	//     of length 0 will be returned.
	//
	ExternalString GetRawStringElement(const char *p_key);

private:
	char *m_name;
};

///////////////////////////////////////////////////////////////////////////////
//
// EXCEPTION CLASSES
//

// The 'UnknownVariableError' exception is thrown when an attempt is made to
// access a Revolution local variable that does not exist.
//
class UnknownVariableError: public ErrorException
{
	friend class Variable;

private:
	UnknownVariableError(const char *p_variable_name);
};

// The 'InvalidConversionError' exception is thrown when an attempt is made to
// access the value of a Revolution variable (or element) that does not
// convert to the requested type.
//
class InvalidConversionError: public ErrorException
{
	friend class Variable;

private:
	InvalidConversionError(const char *p_type, const char *p_variable, const char *p_element);
};

#endif
