using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace Marauder.Aeryn.Runner
{
    public class TestSetReader
    {
        readonly ITestSetVisitor visitor;
        readonly IExecute execute;
        
        public TestSetReader(ITestSetVisitor visitor, IExecute execute)
        {
            this.visitor = visitor;
            this.execute = execute;
        }

        public bool Read(string path)
        {
            bool result = execute.Exectue(path,"");

            if ( result )
            {
                ProcessOutput(execute.Output);
            }

            return result;
        }

        private void ProcessOutput(string output)
        {
            StringReader sr = new StringReader(output);
            XmlReader rdr = XmlReader.Create(sr);

            while (rdr.Read())
            {
                if (rdr.NodeType == XmlNodeType.Element)
                {
                    if (rdr.Name.Equals("TestSet"))
                    {
                       visitor.TestSet(rdr.GetAttribute("name"));
                    }
                }
                else if (rdr.NodeType == XmlNodeType.Text)
                {
                    visitor.Test(rdr.Value);
                }
            }
        }
    }
}

