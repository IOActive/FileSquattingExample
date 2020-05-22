using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Timers;

namespace QuatService
{
    // Install with InstallUtil.exe \path\to\service.exe
    // Uninstall with InstallUtil.exe -u \path\to\service.exe

    public partial class Service1 : ServiceBase
    {
        Timer timer = new Timer();

        public Service1()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            timer.Elapsed += new ElapsedEventHandler(OnElapsedTime);
            timer.Interval = 60000; //number in milisecinds  
            timer.AutoReset = true;
            timer.Enabled = true;
        }

        protected override void OnStop()
        {
        }

        private void OnElapsedTime(object source, ElapsedEventArgs e)
        {
            CallAgent();
        }

        public void CallAgent()
        {
            string ExeFile = "C:\\Windows\\System32\\calc.exe";
            if (!new Signtool().VerifyExe(ExeFile))
                return;
        }
    }
}

