
using NUnit.Framework;
using Marauder.Aeryn.Runner;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Marauder.Aeryn.Runner.Tests
{
    class TestSetVisitor : ITestSetVisitor
    {
        private List<string> output = new List<string>();

        public List<string> Output
        {
            get{ return output; }
        }
        
        public void TestSet(string name)
        {
            output.Add(name);
        }

        public void Test(string name)
        {
            output.Add(name);
        }
    }
    
    [TestFixture]
    public class TestSetReaderTest
    {
        [Test]
        public void TestSetAndTestsTest()
        {
            List<string> expectedOutput = new List<string>();
            expectedOutput.Add("Test set 1");
            expectedOutput.Add("Test 1");
            expectedOutput.Add("Test 2");
            expectedOutput.Add("Test set 2");
            expectedOutput.Add("Test 3");
            expectedOutput.Add("Test 4");
            
            TestSetVisitor visitor = new TestSetVisitor();
            TestSetReader tsr = new TestSetReader( visitor, new ExecuteFake() );

            Assert.IsTrue(tsr.Read(""));
            Assert.AreEqual(expectedOutput, visitor.Output);
        }
    }
}

