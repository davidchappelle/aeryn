
#include "vector_of_int.hpp"

std::ostream& operator<<( std::ostream& out, const Range::VectorOfInt& range )
{
	std::copy(	range.begin(), 
				range.end(), 
				std::ostream_iterator< int >( out, " " ) );
				return out;
}
