///////////////////////////////////////////////////////////////////////////////
//
// VARIABLE SOURCE
//
// This source file contains the implementation of the 'Variable' class and
// associated support.
//

#include <cstdio>
#include <cstdlib>
#include <float.h>

#include <revolution/external.h>

#include "variable.h"

// The number of decimal digits of an unsigned integer representable with
// n bytes is always less that 2.5 * n
//
#define UNSIGNED_INTEGER_LENGTH (5 * sizeof(unsigned int) / 2)

// A signed integer may have a preceeding '-'
//
#define SIGNED_INTEGER_LENGTH (UNSIGNED_INTEGER_LENGTH + 1)

// The decimal length of a floating-point number is:
//   precision + '.' + 'e' + '-'/'+' + exponent
// The maximum precision of a double is 15
// The maximum exponent of a double is 308
// XXX CHANGE PER MARK WADDINGHAM TO: #define DOUBLE_LENGTH (16 + 1 + 1 + 1 + 3 + 1)
// XXX FROM: #define DOUBLE_LENGTH (15 + 1 + 1 + 1 + 3)
//
#define DOUBLE_LENGTH (16 + 1 + 1 + 1 + 3 + 1)


///////////////////////////////////////////////////////////////////////////////
//
// CONSTRUCTORS AND DESTRUCTORS
//

Variable::Variable(const char *p_name)
{
	m_name = strdup(p_name);
}

Variable::~Variable(void)
{
	free(m_name);
}

///////////////////////////////////////////////////////////////////////////////
//
// VALUE SETTERS
//
// These are implemented by wrapping the element setters. This works since
// 'SetVariableEx' takes an empty ("") string to mean the variable's string
// value.
//

void Variable::SetUnsignedInteger(unsigned int p_value)
{
	SetUnsignedIntegerElement("", p_value);
}

void Variable::SetInteger(int p_value)
{
	SetIntegerElement("", p_value);
}

void Variable::SetReal(double p_value)
{
	SetRealElement("", p_value);
}

void Variable::SetString(const std::string& p_string)
{
	SetStringElement("", p_string);
}

void Variable::SetCString(const char *p_cstring)
{
	SetCStringElement("", p_cstring);
}

void Variable::SetRawBuffer(const void *p_buffer, unsigned int p_length)
{
	SetRawBufferElement("", p_buffer, p_length);
}

void Variable::SetRawString(const ExternalString& p_raw_string)
{
	SetRawStringElement("", p_raw_string);
}

///////////////////////////////////////////////////////////////////////////////
//
// VALUE GETTERS
//
// These are implemented by wrapping the element getters. This works since
// 'GetVariableEx' takes an empty ("") string to mean the variable's string
// value.
//

unsigned int Variable::GetUnsignedInteger(void)
{
	return GetUnsignedIntegerElement("");
}

int Variable::GetInteger(void)
{
	return GetIntegerElement("");
}

double Variable::GetReal(void)
{
	return GetRealElement("");
}

std::string Variable::GetString(void)
{
	return GetStringElement("");
}

ExternalString Variable::GetRawString(void)
{
	return GetRawStringElement("");
}

///////////////////////////////////////////////////////////////////////////////
//
// ELEMENT SETTERS
//
// These are implemented by converting the given value to a C-string (if
// required) then using SetVariableEx, passing the appropriate key.
//

void Variable::SetUnsignedIntegerElement(const char *p_key, unsigned int p_value)
{
	char t_value[UNSIGNED_INTEGER_LENGTH];
	sprintf(t_value, "%u", p_value);
	SetCStringElement(p_key, t_value);
}

void Variable::SetIntegerElement(const char *p_key, int p_value)
{
	char t_value[SIGNED_INTEGER_LENGTH];
	sprintf(t_value, "%d", p_value);
	SetCStringElement(p_key, t_value);
}

void Variable::SetRealElement(const char *p_key, double p_value)
{
	char t_value[DOUBLE_LENGTH];
	// sprintf(t_value, "%.15g", p_value);
	sprintf(t_value, "%.15g", p_value);
	SetCStringElement(p_key, t_value);
}

void Variable::SetStringElement(const char *p_key, const std::string& p_string)
{
	ExternalString t_ex_string;
	t_ex_string . buffer = p_string . data();
	t_ex_string . length = p_string . length();
	SetRawStringElement(p_key, t_ex_string);
}

void Variable::SetCStringElement(const char *p_key, const char *p_cstring)
{
	ExternalString t_ex_string;
	t_ex_string . buffer = p_cstring;
	t_ex_string . length = strlen(p_cstring);
	SetRawStringElement(p_key, t_ex_string);
}

void Variable::SetRawBufferElement(const char *p_key, const void *p_buffer, unsigned int p_length)
{
	ExternalString t_raw_string;
	t_raw_string . buffer = (const char *)p_buffer;
	t_raw_string . length = p_length;
	SetRawStringElement(p_key, t_raw_string);
}

void Variable::SetRawStringElement(const char *p_key, const ExternalString& p_raw_string)
{
	int t_success;
	SetVariableEx(m_name, p_key, &p_raw_string, &t_success);
	if (t_success == EXTERNAL_FAILURE)
		throw UnknownVariableError(m_name);
}

///////////////////////////////////////////////////////////////////////////////
//
// ELEMENT GETTERS
//
// These are implemented by fetching the element's value using GetVariableEx
// and then coercing to the required type.
//
// If a type conversion error occurs, an 'InvalidConversionError' exception
// is thrown.
//

unsigned int Variable::GetUnsignedIntegerElement(const char *p_key)
{
	ExternalString t_raw_string;
	t_raw_string = GetRawStringElement(p_key);

	unsigned int t_value;
	char *t_end_ptr;
	t_value = strtoul((char *)t_raw_string . buffer, &t_end_ptr, 10);
	if (t_end_ptr == NULL || (t_end_ptr - (char *)t_raw_string . buffer) < t_raw_string . length)
		throw InvalidConversionError("an unsigned integer", m_name, p_key);

	return t_value;
}

int Variable::GetIntegerElement(const char *p_key)
{
	ExternalString t_raw_string;
	t_raw_string = GetRawStringElement(p_key);

	int t_value;
	char *t_end_ptr;
	t_value = strtol((char *)t_raw_string . buffer, &t_end_ptr, 10);
	if (t_end_ptr == NULL || (t_end_ptr - (char *)t_raw_string . buffer) < t_raw_string . length)
		throw InvalidConversionError("an integer", m_name, p_key);

	return t_value;
}

double Variable::GetRealElement(const char *p_key)
{
	ExternalString t_raw_string;
	t_raw_string = GetRawStringElement(p_key);

	double t_value;
	char *t_end_ptr;
	t_value = strtod((char *)t_raw_string . buffer, &t_end_ptr);
	if (t_end_ptr == NULL || (t_end_ptr - (char *)t_raw_string . buffer) < t_raw_string . length)
		throw InvalidConversionError("a number", m_name, p_key);

	return t_value;
}

std::string Variable::GetStringElement(const char *p_key)
{
	ExternalString t_raw_string;
	t_raw_string = GetRawStringElement(p_key);
	return std::string((char *)t_raw_string . buffer, t_raw_string . length);
}

ExternalString Variable::GetRawStringElement(const char *p_key)
{
	ExternalString t_value;
	int t_success;
	GetVariableEx(m_name, p_key, &t_value, &t_success);
	if (t_success == EXTERNAL_FAILURE)
		throw UnknownVariableError(m_name);
	return t_value;
}


///////////////////////////////////////////////////////////////////////////////
//
// EXCEPTION IMPLEMENTATION
//

UnknownVariableError::UnknownVariableError(const char *p_variable_name)
{
	Format("'%s' is not a local variable in the current scope", p_variable_name);
}

InvalidConversionError::InvalidConversionError(const char *p_type, const char *p_variable, const char *p_element)
{
	if (*p_element == '\0')
		Format("'%s' does not contain %s", p_variable, p_element);
	else
		Format("'%s[%s]' does not contain %s", p_variable, p_element, p_type);
}
