
#ifndef LIFT_ILIFT_H
#define LIFT_ILIFT_H

namespace Lift
{
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

		virtual int CurrentFloor() const = 0;
		virtual void Summon( unsigned int floor ) = 0;

	private:
		ILift( const ILift& );
		ILift& operator=( const ILift& );		
	};
}

#endif // LIFT_ILIFT_H
