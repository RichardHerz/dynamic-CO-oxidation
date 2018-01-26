///////////////////////////////////////////////////////////////////////////////
//
// UTILITY HEADER
//
// This header file contains an assortment of definitions and declarations to
// help improve coding clarity throughout the 'rnaeffect' external.
//

#ifndef __UTILITY__
#define __UTILITY__

#ifndef _CSTRING_
#include <cstring>
#endif

#ifndef _EXCEPTION_
#include <exception>
#endif

///////////////////////////////////////////////////////////////////////////////
//
// PLATFORM UNIFORMIZATION
//
// A collection of definitions to help ease cross-platform development
//

#if defined(_WINDOWS)
#define strcasecmp _stricmp
#define x_va_copy(d, s) d = s
#define x_va_end(d)
#elif defined(_MACOSX)
#define x_va_copy va_copy
#define x_va_end va_end
#endif

///////////////////////////////////////////////////////////////////////////////
//
// EXCEPTION BASE CLASS
//
// A base class for our error exceptions that allows construction of a message
// string based on a standard print-style format string.
//
// It inherits from std::exception and implements the appropriate interface.
//

class ErrorException: public std::exception
{
public:
	ErrorException(void);
	ErrorException(const char *p_format, ...);
	~ErrorException(void) throw();

	const char *what(void) const throw();

protected:
	void Format(const char *p_format, ...);
	void FormatWithArguments(const char *p_format, va_list p_args);

private:
	char *m_message;
};

///////////////////////////////////////////////////////////////////////////////
//
// AUTO ARRAY PTR TEMPLATE
//
// Modern standard C++ libraries contain a utility template 'auto_ptr' that
// allows you to wrap a pointer (allocated with new) so it automatically
// gets 'deleted' on function exits - in particular when the stack unwinds on
// an exception being thrown.
//
// This is great... except there isn't an equivalent for an 'array' allocated
// with the operater new[]. Thus, this template class is the equivalent of
// auto_ptr but for arrays.
// 

template<class T> class auto_array_ptr
{
public:
	typedef T element_type;

	explicit auto_array_ptr(T* p_ptr = NULL)
		: m_ptr(p_ptr)
	{
	}

	auto_array_ptr(auto_array_ptr<T>& p_other)
		: m_ptr(p_other . release())
	{
	}

	auto_array_ptr<T>& operator = (auto_array_ptr<T>& p_other)
	{
		reset(p_other . release());
		return *this;
	}

	~auto_array_ptr(void)
	{
		delete[] m_ptr;
	}

	T& operator [] (int p_index) const
	{
		return m_ptr[p_index];
	}

	T* get(void) const
	{
		return m_ptr;
	}

	T* release(void)
	{
		T *t_ptr;
		t_ptr = m_ptr;
		m_ptr = NULL;
		return t_ptr;
	}

	void reset(T *p_ptr)
	{
		if (p_ptr != m_ptr)
			delete[] m_ptr;
		m_ptr = p_ptr;
	}

private:
	T* m_ptr;
};

#endif
