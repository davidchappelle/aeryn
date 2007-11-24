
using NUnit.Framework;

namespace Marauder.Aeryn.Runner.Tests
{
    [TestFixture]
    public class ProcessExecuterTest
    {
        readonly string dummyTestExe = "Marauder.Aeryn.DummyTestExe.exe";
        
        [Test]
        public void SimpleIntegrationTest()
        {
            IExecute exe = new ProcessExecuter();
            Assert.IsTrue(exe.Exectue(dummyTestExe, ""));
            Assert.AreEqual(ExecuteFake.GenerateTwoTestSetXML(), exe.Output);            
        }
    }
}
