using System;
using System.Collections.Generic;
using System.Text;

namespace Marauder.Aeryn.Runner
{
    public interface ITestSetVisitor
    {
        void TestSet(string name);

        void Test(string name);
    }
}
