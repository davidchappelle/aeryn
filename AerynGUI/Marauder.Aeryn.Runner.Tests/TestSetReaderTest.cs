
using NUnit.Framework;
using Marauder.Aeryn.Runner;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;

namespace Marauder.Aeryn.Runner.Tests
{
    class ExecuteFake : IExecute
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

        private string GenerateTwoTestSetXML()
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
            xmlWriter.WriteEndElement();
            

            return stringWriter.ToString();

        }
    }

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

