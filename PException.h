#ifndef PException_h
#define PException_h
#include "PString.h"
#include "PCommon.h"
namespace PLibary
{
#define MAX_SIZE 2048

	class PException
	{
	public:
		PException ();
		PException(const PString &);
		PException(const char*);
		virtual ~PException();
		void SetMessage(const char*);
		void SetMessage(const PString&);
		const PString    GetMessage();
	private:
		UInt32						_errorTextLength;
		mutable char				_errorText[MAX_SIZE];
		PString _text;
 	};
}
#endif 