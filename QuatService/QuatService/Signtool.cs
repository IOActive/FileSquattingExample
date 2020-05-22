using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace QuatService
{
    internal class Signtool
    {
        private const string SignToolPath = "C:\\Windows\\Temp\\signtool.exe";

        private void ExtractSignTool()
        {
            byte[] signtool = QuatService.Resource1.signtool;
            using (FileStream fileStream = new FileStream("C:\\Windows\\Temp\\signtool.exe", FileMode.Create))
                fileStream.Write(signtool, 0, signtool.Length);
        }

        private void DeleteSignTool()
        {
            File.Delete("C:\\Windows\\Temp\\signtool.exe");
        }

        private bool Verify(string arg)
        {
            this.ExtractSignTool();
            Process process = new Process();
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;
            Path.GetDirectoryName(this.GetType().Assembly.Location);
            process.StartInfo.FileName = "C:\\Windows\\Temp\\signtool.exe";
            process.StartInfo.Arguments = arg;          
            process.Start();
            process.WaitForExit();
            this.DeleteSignTool();
            return process.ExitCode == 0 || process.ExitCode == 2;
        }

        public bool VerifyExe(string ExeFile)
        {
            return this.Verify("verify /pa \"" + ExeFile + "\"");
        }

    }
}
