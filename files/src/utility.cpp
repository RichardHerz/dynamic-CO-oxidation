///////////////////////////////////////////////////////////////////////////////
//
// UTILITY SOURCE
//
// This source file contains the implementation of the ErrorException class
//

#include <cstdlib>
#include <cstdarg>
#include <cstdio>

#include <exception>

#include "utility.h"

///////////////////////////////////////////////////////////////////////////////
//
// ERROR EXCEPTION: CONSTRUCTORS AND DESTRUCTORS
//

ErrorException::ErrorException(void)
	: m_message(NULL)
{
}

ErrorException::ErrorException(const char *p_format, ...)
  : m_message(NULL)
{
	va_list t_args;
	va_start(t_args, p_format);
	FormatWithArguments(p_format, t_args);
	va_end(t_args);
}

ErrorException::~ErrorException(void) throw()
{
	free(m_message);
}

///////////////////////////////////////////////////////////////////////////////
//
// ERROR EXCEPTION: OVERRIDDEN METHODS
//

const char *ErrorException::what(void) const throw()
{
	return m_message == NULL ? "error exception" : m_message;
}

///////////////////////////////////////////////////////////////////////////////
//
// ERROR EXCEPTION: PROTECTED METHODS
//

// The Format method keeps trying to format the given printf-style format
// until it gets the right length. It then sets the 'm_message' member to the
// resulting string.
//
void ErrorException::FormatWithArguments(const char *p_format, va_list p_args)
{
	int t_length;
	t_length = 256;

	char *t_result;
	t_result = NULL;

	for(;;)
	{
		t_result = (char *)malloc(t_length);
		if (t_result == NULL)
			break;

		int t_formatted_length;
    va_list t_args;
		x_va_copy(t_args, p_args);
		t_formatted_length = vsnprintf(t_result, t_length, p_format, t_args);
    x_va_end(t_args);

		if (t_formatted_length < t_length)
		{
			t_result = (char *)realloc(t_result, t_formatted_length + 1);
			break;
		}

		t_length *= 2;
		free(t_result);
	}

	if (m_message != NULL)
		free(m_message);

	m_message = t_result;
}

void ErrorException::Format(const char *p_format, ...)
{
	va_list t_args;
	va_start(t_args, p_format);
	FormatWithArguments(p_format, t_args);
	va_end(t_args);
}
