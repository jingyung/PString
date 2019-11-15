
#ifndef PSting_h
#define PSting_h


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PCommon.h"

namespace PLibary
{

	class PString
	{
	public:
		static const UInt32 npos = -1;
		PString();
		PString(const char* str, UInt32 length = PString::npos);
		PString(const PString& other);
		virtual ~PString();
		PString& clear();
		PString& set(const char* str, UInt32 length = PString::npos);
		PString& operator=(const PString& other);
		PString& operator=(const char* other);
		PString& append(Int64 value);
		PString& append(UInt64 value);
		PString& append(Int32 value);
		PString& append(UInt32 value);
		PString& append(float value);
		PString& append(double value);
		PString& append(const char* value);
		PString& append(const PString& value);
		PString& operator+=(Int64 value);
		PString& operator+=(UInt64 value);
		PString& operator+=(Int32 value);
		PString& operator+=(UInt32 value);
		PString& operator+=(float value);
		PString& operator+=(double value);
		PString& operator+=(const char* value);
		PString& operator+=(const PString& value);
		PString operator+(const PString& str) const;
		PString operator+(const char* str) const;
		char& operator[](UInt32 index);
		PString& trimWhitespace();
		bool empty() const;
		virtual const char* c_str() const;
		UInt32 length() const;
		char operator[](UInt32 index) const;
		PString substr(UInt32 index, UInt32 length) const;
		operator const char* () const;
		Int32 find(const PString& str, Int32 index = 0) const;
		Int32 find(const char* str, Int32 index = 0) const;
		Int32 findLast(const PString& str) const;
		Int32 findLast(const char*) const;
		bool operator==(const PString& str) const;
		bool operator!=(const PString& str) const;
		bool operator>(const PString& str) const;
		bool operator<(const PString& str) const;
		bool operator>=(const PString& str) const;
		bool operator<=(const PString& str) const;
		bool operator==(const char* str) const;
		bool operator!=(const char* str) const;
		bool operator>(const char* str) const;
		bool operator<(const char* str) const;
		bool operator>=(const char* str) const;
		bool operator<=(const char* str) const;
		bool caseInsensitiveCompare(const PString& str) const;
		bool caseInsensitiveCompare(const char * str) const;
	protected:
		mutable char*	_pString;
		UInt32			_length;
		mutable UInt32	_capacity;
	private:
		int compare(const char * rhs) const;
	};
}

#endif 
