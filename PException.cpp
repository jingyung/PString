#include "PException.h"

using namespace PLibary;

PException::PException()
{
}


PException::~PException()
{
}

PException::PException(const PString& val)
{
	SetMessage(val);

}

PException::PException(const char* val)
{
	SetMessage(val);

}
const PString   PException::GetMessage()
{
	PString text(_errorText);
	//_text.set(_errorText);
	return text;
}
 
void PException::SetMessage(const char * val)
{
	_errorTextLength = 0;
	while (*(val + _errorTextLength))
	{
		*(_errorText + _errorTextLength) = *(val + _errorTextLength);
		if (++_errorTextLength >= MAX_SIZE - 1)
			break;
	}

	*(_errorText + _errorTextLength) = 0x00;
}
void PException::SetMessage(const PString & val )
{
	const char* text = val.c_str();
	SetMessage(text);
}
 