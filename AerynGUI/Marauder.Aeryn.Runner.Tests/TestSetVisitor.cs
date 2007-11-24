
using System.Collections.Generic;

namespace Marauder.Aeryn.Runner.Tests
{
    class TestSetVisitor : ITestSetVisitor
    {
        private List<string> output = new List<string>();

        public List<string> Output
        {
            get { return output; }
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
}
