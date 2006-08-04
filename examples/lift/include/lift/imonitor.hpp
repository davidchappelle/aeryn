
#ifndef LIFT_IMONITOR_H
#define LIFT_IMONITOR_H

namespace Lift
{
	class ILift;
	
	class IMonitor
	{
	protected:
		IMonitor()
		{
		}

	public:
		virtual ~IMonitor() = 0
		{
		}

		virtual void Update( const ILift* lift ) = 0;

	private:
		IMonitor& operator=( const IMonitor& );
		IMonitor( const IMonitor& );
	};
}

#endif // LIFT_IMONITOR_H
