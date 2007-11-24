using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace Marauder.Aeryn.Runner.Tests
{
    public class ExecuteFake : IExecute
    {
        string output = "";

        public bool Exectue(string path, string arg)
        {
            output = GenerateTwoTestSetXML();
            return true;
        }

        public string Output
        {
            get { return output; }
        }

        public static string GenerateTwoTestSetXML()
        {
            StringWriter stringWriter = new StringWriter();
            XmlTextWriter xmlWriter = new XmlTextWriter(stringWriter);
            xmlWriter.Formatting = Formatting.Indented;

            xmlWriter.WriteStartElement("Aeryn");
            xmlWriter.WriteStartElement("TestSet");
            xmlWriter.WriteAttributeString("name", "Test set 1");
            xmlWriter.WriteElementString("Test", "Test 1");
            xmlWriter.WriteElementString("Test", "Test 2");
            xmlWriter.WriteEndElement();
            xmlWriter.WriteStartElement("TestSet");
            xmlWriter.WriteAttributeString("name", "Test set 2");
            xmlWriter.WriteElementString("Test", "Test 3");
            xmlWriter.WriteElementString("Test", "Test 4");
            xmlWriter.WriteEndElement();

/*           for (int i = 0; i < 200; ++i)
            {
                xmlWriter.WriteStartElement("TestSet");
                xmlWriter.WriteAttributeString("name", string.Format("Test set {0}", i ) );

                for (int j = 0; j < 10; ++j)
                {
                    xmlWriter.WriteElementString("Test", string.Format("Test {0}",j));
                }

                xmlWriter.WriteEndElement();
            }*/

            xmlWriter.WriteEndElement();


            return stringWriter.ToString();

        }
    }
}
