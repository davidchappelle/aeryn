
#ifndef RANGE_VECTOR_OF_INT_HPP
#define RANGE_VECTOR_OF_INT_HPP

#include <aeryn/details/is_streamable.hpp>
#include <vector>

namespace Range
{
	typedef std::vector< int > VectorOfInt;
}

namespace Aeryn
{
	namespace Williams
	{
		template<>
		struct IsStreamable< Range::VectorOfInt >
		{
			static FalseType testStreamable
				( const StreamableResult& );

			static TrueType testStreamable
				(...);

			static const bool result =	true;
		};
	}
}	

std::ostream& operator<<( std::ostream& out, const Range::VectorOfInt& range );

#endif // RANGE_VECTOR_OF_INT_HPP