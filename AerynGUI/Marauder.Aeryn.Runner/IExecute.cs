using System;
using System.Collections.Generic;
using System.Text;

namespace Marauder.Aeryn.Runner
{
    public interface IExecute
    {
        bool Exectue(string path, string arg);

        string Output
        {
            get;
        }
    }
}
