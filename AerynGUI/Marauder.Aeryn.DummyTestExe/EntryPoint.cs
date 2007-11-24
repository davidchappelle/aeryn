
using Marauder.Aeryn.Runner.Tests;

namespace Marauder.Aeryn.DummyTestExe
{
    class EntryPoint
    {
        static void Main(string[] args)
        {
            System.Console.Write(ExecuteFake.GenerateTwoTestSetXML());
        }
    }
}
