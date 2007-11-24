using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.ComponentModel;
using System.Threading;

namespace Marauder.Aeryn.Runner
{
    public class ProcessExecuter : IExecute
    {
        string output = "";
        
        public bool Exectue(string path, string arg)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo(path,arg);
            Process process = new Process();
            
            startInfo.UseShellExecute = false;
            startInfo.RedirectStandardInput = true;
            startInfo.RedirectStandardOutput = true;
            startInfo.RedirectStandardError = true;
            startInfo.CreateNoWindow = true;
            process.StartInfo = startInfo;
            bool result = process.Start();
            StreamWriter sw = process.StandardInput;
            StreamReader sr = process.StandardOutput;
            sw.AutoFlush = true;

            output = sr.ReadToEnd();       
            return result;
        }

        public string Output
        {
            get { return output; }
        }
    }
}
