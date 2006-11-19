
#ifndef LIFT_ILIFT_H
#define LIFT_ILIFT_H

namespace Lift
{
	class IMonitor;
	
	class ILift
	{
	protected:
		ILift()
		{
		}

	public:
		virtual ~ILift() = 0
		{
		}

		virtual unsigned int CurrentFloor() const = 0;
		virtual void Summon( unsigned int floor ) = 0;
		virtual void AddMonitor( IMonitor* monitor ) = 0;

	private:
		ILift( const ILift& );
		ILift& operator=( const ILift& );		
	};
}

#endif // LIFT_ILIFT_H
