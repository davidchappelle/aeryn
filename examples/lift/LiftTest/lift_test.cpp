
#include "lift_test.hpp"
#include <lift/lift.hpp>
#include <lift/invalid_floor.hpp>
#include <lift/imonitor.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/throws_exception.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/is_true.hpp>
#include <aeryn/missing_test.hpp>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>

namespace LiftTests
{
	namespace
	{
		class FloorsPassed : public Lift::IMonitor
		{
		private:
			typedef std::vector< unsigned int > FloorCont;
			typedef FloorCont::const_iterator const_iterator;
			FloorCont floors_;

		public:
			FloorsPassed()
				: floors_()
			{
			}

			FloorsPassed( unsigned int begin, unsigned int end )
				: floors_()
			{
				const bool moveUp = begin < end ? true : false;
				
				unsigned int current = begin;
				while( current != end )
				{
					floors_.push_back( current );

					if ( moveUp )
					{
						++current;
					}
					else
					{
						--current;
					}
				}
				floors_.push_back( current );		
			}

			bool IsEqual( const FloorsPassed& other ) const
			{
				return other.floors_ == floors_;
				
			}

            virtual void Update( const Lift::ILift* lift )
			{
				floors_.push_back( lift->CurrentFloor() );
			}
		};

		inline bool operator==( const FloorsPassed& lhs, const FloorsPassed& rhs )
		{
			return lhs.IsEqual( rhs );
		}
	}
	
	void LiftTest::BasicTest()
	{
		try
		{
			std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );
			IS_EQUAL( 0, pLift->CurrentFloor() );
			pLift->Summon( 5 );
			IS_EQUAL( 5, pLift->CurrentFloor() );
		}
		catch( const Lift::Exception& e )
		{
			FAILED( e.what() );
		}
	}

	void LiftTest::InvalidFloorTest()
	{
		std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );
		THROWS_EXCEPTION( pLift->Summon( 11 ); , Lift::InvalidFloor );

		try
		{
			pLift->Summon( -1 );
			FAILED( "Failed to throw Lift::InvalidFloor" );
		}
		catch( const Lift::InvalidFloor& e )
		{
			const unsigned int floor = -1;
			std::stringstream expectedMsg;
			expectedMsg << floor << " is an invalid floor";
			IS_EQUAL( expectedMsg.str(), e.what() );
		}
	}

	void LiftTest::PassAllFloorsUpTest()
	{
		try
		{
			FloorsPassed floorsPassed;
			std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );
			pLift->AddMonitor( &floorsPassed );

			pLift->Summon( 8 );
			const FloorsPassed expectedResult( 0, 8 );
			IS_TRUE( floorsPassed == expectedResult );			
		}
		catch( const Lift::Exception& e )
		{
			FAILED( e.what() );
		}
	}

	void LiftTest::PassAllFloorsDownTest()
	{
		try
		{
			FloorsPassed floorsPassed;
			std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );
			pLift->Summon( 8 );
			IS_EQUAL( 8, pLift->CurrentFloor() );
			pLift->AddMonitor( &floorsPassed );
			pLift->Summon( 2 );

			const FloorsPassed expectedResult( 8, 2 );
			IS_TRUE( floorsPassed == expectedResult );
		}
		catch( const Lift::Exception& e )
		{
			FAILED( e.what() );
		}
	}

	void LiftTest::FloorsPassedMockObjectTest()
	{
		MISSING_TEST( "FloorsPassed mock object test." );
	}
}

