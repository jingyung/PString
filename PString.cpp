#include "PString.h"
#include "PException.h"
using namespace  PLibary;
 

PString::PString() :
    _pString ( 0 ),
    _length ( 0 ),
    _capacity ( 0 )
{
}

PString::PString( const char* str, UInt32 length ) :
    _pString ( 0 ),
    _length ( str ? length : 0 ),
    _capacity ( 0 )
{
	if ( length == PString::npos )
	{
		if ( str )
		{
			size_t tempLength = strlen( str );

			if ( tempLength >= PString::npos )
			{
				const char* temp = "The length of the passed in string is larger than MAX_UINT32. PString( const char* , UInt32 ).";
				throw PException ( temp );
				return;
			}

			_length = static_cast<UInt32>( tempLength );
			
			_capacity = _length + 1;
		}
	}
	else if ( length )
	{
		_capacity = length + 1;
	}

    if ( _capacity )
    {
        _pString = ( char* )malloc( _capacity );

        if ( !_pString )
        {
            const char* temp = "Failed to allocate memory in PString( const char* , UInt32 ).";
			throw PException( temp );
            return;
        }

        memcpy( _pString, str, _length );
        *( _pString + _length ) = 0x00;
    }
}

PString::PString( const PString& other ) :
    _pString ( 0 ),
    _length ( other._length ),
    _capacity ( other._length + 1 )
{
    if ( other._length )
    {
        _pString = ( char* )malloc( _capacity );

        if ( !_pString )
        {
            const char* temp = "Failed to allocate memory in PString( const char* , UInt32 ).";
            throw PException( temp );
            return;
        }

        memcpy( _pString, other._pString, _length );
        *( _pString + _length ) = 0x00;
    }
    else
    {
        _capacity = 0;
    }
}

PString::~PString()
{
    if ( _pString )
        free ( _pString );
}

PString& PString::clear()
{
    _length = 0;
    if ( _pString )
        *_pString = 0x00;

    return *this;
}

bool PString::empty() const
{
    return !_length ? true : false;
}

const char* PString::c_str() const
{
    return _pString ? _pString : "";
}

UInt32 PString::length() const
{
    return _length;
}

PString& PString::operator= ( const char* str )
{
    return set ( str );
}

PString& PString::operator= ( const PString& other )
{
    if ( this == &other ) return *this;

    if ( other._length )
    {
        if ( _capacity <= other._length )
        {
            _capacity = other._length + 1;

            if ( _pString )
            {
                free ( _pString );
                _pString = 0;
            }

            _pString = ( char* ) malloc ( _capacity );
            if ( !_pString )
            {
                const char* temp = "Failed to allocate memory in PString::operator=( const PString& ).";
                throw PException ( temp );
                return *this;
            }
        }

        _length = other._length;

        if ( other._pString )
            memcpy ( _pString, other._pString, _length );

        * ( _pString + _length ) = 0x00;
    }
    else
    {
        clear();
    }

    return *this;
}

//		length		0						0 < x < npos						npos
//
//	str
//
//	null			_capacity = existing	_capacity = x + 1 or existing		_capacity = existing
//					_length = 0				_length = 0							_length = 0
//
//	not null		_capacity = existing	_capacity = x + 1 or existing		_capacity = actual string length + 1 or existing
//					_length = 0				_length = x							_length = actual string length
//																				IUE if actual string length >= PString::npos
//											copy content						copy content
//
PString& PString::set ( const char* str, UInt32 length )
{
	if ( str )
	{
		if ( length == PString::npos )
		{
			size_t tempLength = strlen( str );

			if ( tempLength >= PString::npos )
			{
				const char* temp = "The length of the passed in string is larger than MAX_UINT32. PString::set( const char* , UInt32 ).";
				throw PException( temp );
				return *this;
			}

			_length = static_cast<UInt32>( tempLength );
		}
		else
		{
			_length = length;
		}
	}
	else
	{
		if ( length == PString::npos || !length )
		{
			clear();
		}
		else
		{
			if ( _capacity <= length )
			{
	            _capacity = length + 1;
				_length = 0;

				if ( _pString )
				{
					free( _pString );
					_pString = 0;
				}

				_pString = ( char* )malloc( _capacity );
				if ( !_pString )
				{
					const char* temp = "Failed to allocate memory in PString::set( const char* , UInt32 ).";
					throw PException ( temp );
					return *this;
				}
				
				*_pString = 0x00;
			}
			else
				clear();
		}

		return *this;
	}

    if ( _length )
    {
        if ( _capacity <= _length )
        {
            _capacity = _length + 1;

            if ( _pString )
            {
                free( _pString );
                _pString = 0;
            }

            _pString = ( char* )malloc( _capacity );
            if ( !_pString )
            {
                const char* temp = "Failed to allocate memory in PString::set( const char* , UInt32 ).";
                throw PException ( temp );
                return *this;
            }
        }

        memcpy( _pString, str, _length );
        *( _pString + _length ) = 0x00;
    }
    else
    {
        clear();
    }

    return *this;
}

PString& PString::append ( Int64 i )
{
	/* Check for length overflow before malloc */
	if (((UInt64)_length + 22) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( Int64 ).";
		throw PException (temp);
		return *this;
	}

    if ( _capacity <= _length + 21 )
    {
	     _capacity = _length + 22;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( Int64 ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

		_length += snprintf ( pNewString + _length,  22, "%lld", i );

        _pString = pNewString;
    }
    else
    {
        _length += snprintf ( _pString + _length, 22,  "%lld", i );
    }

    return *this;
}

PString& PString::append ( UInt64 i )
{
	/* Check for length overflow before malloc */
	if (((UInt64)_length + 22) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( UInt64 ).";
		throw PException (temp);
		return *this;
	}

    if ( _capacity <= _length + 21 )
    {
        _capacity = _length + 22;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( UInt64 ).";
            throw PException  ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        _pString = pNewString;
    }

    _length += snprintf ( _pString + _length, 22, "%llu", i );

    return *this;
}

PString& PString::append ( Int32 i )
{
	/* Check for length overflow before malloc */
	if (((UInt64)_length + 13) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( Int32 ).";
		throw PException (temp);
		return *this;
	}

    if ( _capacity <= _length + 12 )
    {
        _capacity = _length + 13;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( Int32 ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        _length += snprintf ( pNewString + _length, 13, "%i", i );

        _pString = pNewString;
    }
    else
    {
        _length += snprintf ( _pString + _length, 13, "%i", i );
    }

    return *this;
}

PString& PString::append ( UInt32 i )
{
	/* Check for length overflow before malloc */
	if (((UInt64)_length + 13) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( UInt32 ).";
		throw PException (temp);
		return *this;
	}
	
	if ( _capacity <= _length + 12 )
    {
		_capacity = _length + 13;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( UInt32 ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        _length += snprintf ( pNewString + _length, 13, "%u", i );

        _pString = pNewString;
    }
    else
    {
        _length += snprintf ( _pString + _length, 13, "%u", i );
    }

    return *this;
}

PString& PString::append ( float f )
{
	/* Check for length overflow before malloc */
	if (((UInt64)_length + 33) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( float ).";
		throw PException(temp);
		return *this;
	}
	
	if ( _capacity <= _length + 32 )
    {
        _capacity = _length + 33;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( float ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        _length += snprintf ( pNewString + _length, 33, "%.15g", f );

        _pString = pNewString;
    }
    else
    {
        _length += snprintf ( _pString + _length, 33, "%.15g", f );
    }

    return *this;
}

PString& PString::append ( double d )
{
	/* Check for length overflow before malloc */
	if (((UInt64)_length + 33) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( double ).";
		throw PException(temp);
		return *this;
	}
	
	if ( _capacity <= _length + 32 )
    {
        _capacity = _length + 33;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( double ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        _length += snprintf ( pNewString + _length, 33, "%.15g", d );

        _pString = pNewString;
    }
    else
    {
        _length += snprintf ( _pString + _length, 33, "%.15g", d );
    }

    return *this;
}

PString& PString::append ( const char* str )
{
    size_t strLength = str ? static_cast<size_t> ( strlen ( str ) ) : 0;

    if ( !strLength ) return *this;

	/* Check for length overflow before malloc */
	if (((size_t)_length + strLength + 1) >= (size_t)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( const char* ).";
		throw PException(temp);
		return *this;
	}

    if ( _capacity <= _length + strLength )
    {
        _capacity = _length + (UInt32)strLength + 1;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( const char* ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        memcpy ( pNewString + _length, str, strLength );

        _length += (UInt32)strLength;

        * ( pNewString + _length ) = 0x00;

        _pString = pNewString;
    }
    else if ( strLength )
    {
        memcpy ( _pString + _length, str, strLength );

        _length += (UInt32)strLength;

        * ( _pString + _length ) = 0x00;
    }

    return *this;
}

PString& PString::append ( const PString& other )
{
    if ( !other._length ) return *this;

	/* Check for length overflow before malloc */
	if (((UInt64)_length + (UInt64)other._length + 1) >= (UInt64)PString::npos)
	{
		const char* temp = "The total length of the passed in string is larger than MAX_UINT32. PString::append( PString ).";
		throw PException(temp);
		return *this;
	}

    if ( _capacity <= _length + other._length )
    {
        _capacity = _length + other._length + 1;

        char* pNewString = ( char* ) malloc ( _capacity );
        if ( !pNewString )
        {
            const char* temp = "Failed to allocate memory in PString::append( const PString& ).";
            throw PException ( temp );
            return *this;
        }

        if ( _pString )
        {
            memcpy ( pNewString, _pString, _length );
            free ( _pString );
        }

        memcpy ( pNewString + _length, other._pString, other._length );

        _length += other._length;

        * ( pNewString + _length ) = 0x00;

        _pString = pNewString;
    }
    else if ( other._length )
    {
        memcpy ( _pString + _length, other._pString, other._length );

        _length += other._length;

        * ( _pString + _length ) = 0x00;
    }

    return *this;
}

PString& PString::operator+= ( Int64 i )
{
    return append ( i );
}

PString& PString::operator+= ( UInt64 i )
{
    return append ( i );
}

PString& PString::operator+= ( Int32 i )
{
    return append ( i );
}

PString& PString::operator+= ( UInt32 i )
{
    return append ( i );
}

PString& PString::operator+= ( float f )
{
    return append ( f );
}

PString& PString::operator+= ( double d )
{
    return append ( d );
}

PString& PString::operator+= ( const char* str )
{
    return append ( str );
}

PString& PString::operator+= ( const PString& str )
{
    return append ( str );
}

PString PString::operator+ ( const PString& other ) const
{
    return PString ( *this ).append ( other );
}

PString PString::operator+ ( const char* str ) const
{
    return PString ( *this ).append ( str );
}

PString::operator const char *() const
{
    return c_str();
}

PString PString::substr ( UInt32 index, UInt32 length ) const
{
    if ( length != PString::npos &&
            ( index > _length ||
              index + length > _length )
       )
    {
        PString text ( "Attempt to access out of range position in PString::substr( UInt32 , UInt32 ) const. Passed in index is " );
        text.append ( index ).append ( " and passed in length is " ).append ( length ).append ( " while length is " ).append ( _length ).append ( "." );
        throw PException  ( text );
        return PString();
    }

    PString retVal;

    retVal.set ( _pString + index, length );

    return retVal;
}

char PString::operator[] ( UInt32 pos ) const
{
    if ( pos > _length )
    {
        PString text ( "Attempt to access out of range position in PString::operator[]() const. Passed in index is " );
        text.append ( pos ).append ( " while length is " ).append ( _length ).append ( "." );
        throw PException ( text );
    }

    return _pString[pos];
}

char& PString::operator[] ( UInt32 pos )
{
    if ( pos > _length )
    {
        PString text ( "Attempt to access out of range position in PString::operator[](). Passed in index is " );
        text.append ( pos ).append ( " while length is " ).append ( _length ).append ( "." );
		 throw PException  (text);
    }

    return _pString[pos];
}

bool PString::operator== ( const PString& other ) const
{
    if ( this == &other ) return true;

    if ( _length != other._length ) return false;

    if ( !_pString && other._pString ) return false;

    if ( _pString && !other._pString ) return false;

    if ( !_pString && !other._pString ) return true;

    return ( 0 == memcmp ( _pString, other._pString, _length ) ? true : false );
}

bool PString::operator!= ( const PString& other ) const
{
    if ( this == &other ) return false;

    if ( _length != other._length ) return true;

    if ( !_pString && other._pString ) return true;

    if ( _pString && !other._pString ) return true;

    if ( !_pString && !other._pString ) return true;

    return ( 0 == memcmp ( _pString, other._pString, _length ) ? false : true );
}

bool PString::operator== ( const char* other ) const
{
    if ( !other )
        return false;

    if ( _length != strlen ( other ) )
        return false;

    return !memcmp ( _pString, other, _length );
}

bool PString::operator!= ( const char* other ) const
{
    if ( !other )
        return true;

    if ( _length != strlen ( other ) )
        return true;

    return memcmp ( _pString, other, _length ) != 0;
}

bool PString::operator> ( const PString& rhs ) const
{
    return compare ( rhs.c_str() ) > 0;
}

bool PString::operator< ( const PString& rhs ) const
{
    return compare ( rhs.c_str() ) < 0;
}

bool PString::operator>= ( const PString& rhs ) const
{
    return compare ( rhs.c_str() ) >= 0;
}

bool PString::operator<= ( const PString& rhs ) const
{
    return compare ( rhs.c_str() ) <= 0;
}

bool PString::operator> ( const char* rhs ) const
{
    return compare ( rhs ) > 0;
}

bool PString::operator< ( const char* rhs ) const
{
    return compare ( rhs ) < 0;
}

bool PString::operator>= ( const char* rhs ) const
{
    return compare ( rhs ) >= 0;
}

bool PString::operator<= ( const char* rhs ) const
{
    return compare ( rhs ) <= 0;
}

PString& PString::trimWhitespace()
{
    if ( !_length ) return *this;

    char* p = _pString;
    while ( *p && isspace ( *p ) )
        ++p;

    if ( !*p )
    {
        _pString[0] = 0;
        _length = 0;
        return *this;
    }

    if ( p != _pString )
    {
        _length -= static_cast<UInt32> ( p - _pString );
        memmove ( _pString, p, _length );
        _pString[_length] = 0;
    }

    p = _pString + _length - 1;
    while ( isspace ( *p ) )
        --p;

    if ( p != _pString + _length - 1 )
    {
        _length = static_cast<UInt32> ( p - _pString + 1 );
        _pString[_length] = 0;
    }

    return *this;
}

Int32 PString::find ( const PString & source, Int32 index ) const
{
    if ( index < 0 || static_cast<UInt32> ( index ) >= _length ||! source._length )
        return PString::npos;

    char* p = _pString + index;
    Int32 retVal ( 0 );
    while ( *p )
    {
        if ( _length - ( p - _pString ) < source._length )
            return PString::npos;

        char* q = source._pString;
        retVal = static_cast<UInt32> ( p - _pString );
        while ( *p == *q )
        {
            if ( ! *++q )
                return retVal;

            if ( ! *++p )
                return PString::npos;
        }

        if ( q == source._pString )
            ++p;
    }

    return PString::npos;
}

Int32 PString::find ( const char* source, Int32 index ) const
{
    if ( index < 0 || static_cast<UInt32> ( index ) >= _length )
        return PString::npos;

    UInt32 sourceLength ( static_cast<UInt32> ( strlen ( source ) ) );
    if ( ! sourceLength )
        return PString::npos;

    char *p = _pString + index;
    Int32 retVal ( 0 );
    while ( *p )
    {
        if ( _length - static_cast<UInt32> ( p - _pString ) < sourceLength )
            return PString::npos;

        const char *q = source;
        retVal = static_cast<Int32> ( p - _pString );
        while ( *p == *q )
        {
            if ( ! *++q )
                return retVal;

            if ( ! *++p )
                return PString::npos;
        }

        if ( q == source )
            ++p;
    }

    return PString::npos;
}

Int32 PString::findLast ( const PString& str ) const
{
    if ( ! str._length || ! _length )
        return PString::npos;

    if ( str._length > _length )
        return PString::npos;

    const char *p, *q;
    Int32 retVal ( _length - str._length );
    while ( true )
    {
        p = _pString + retVal;
        q = str._pString;
        while ( *q && *p == *q )
        {
            ++p;
            ++q;
        }

        if ( ! *q )
            return retVal;

        if ( --retVal < 0 )
            return PString::npos;
    }
}

Int32 PString::findLast ( const char* str ) const
{
    if ( !str || str[0] == 0 || !_length )
        return PString::npos;

    Int32 strLen ( static_cast<Int32> ( strlen ( str ) ) );

    const char *p, *q;
    Int32 retVal ( _length - strLen );
    while ( true )
    {
        p = _pString + retVal;
        q = str;
        while ( *q && *p == *q )
        {
            ++p;
            ++q;
        }

        if ( ! *q )
            return retVal;

        if ( --retVal < 0 )
            return PString::npos;
    }
}

bool PString::caseInsensitiveCompare ( const PString& rhs ) const
{
    if ( ( this == &rhs ) ||
            ( !_pString && !rhs._pString ) )
        return true;

    if ( _length != rhs._length )
        return false;

    for ( UInt32 i = 0; i < _length; ++i )
        if ( tolower ( _pString[i] ) != tolower ( rhs._pString[i] ) )
            return false;

    return true;
}

bool PString::caseInsensitiveCompare ( const char * rhs ) const
{
    if ( ! rhs )
        return ! _pString;

    if ( strlen ( rhs ) != _length )
        return false;

    for ( UInt32 i = 0; i < _length; ++i )
        if ( tolower ( _pString[i] ) != tolower ( rhs[i] ) )
            return false;

    return true;
}

int PString::compare ( const char * rhs ) const
{
    for ( unsigned int i = 0; i < _length  && i < strlen ( rhs ); ++i )
        if ( _pString[ i ] != rhs[ i ] )
            return _pString[ i ] - rhs[ i ];

    return static_cast< int > ( _length - strlen ( rhs ) );
}
