using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Diagnostics;
using System.Net;

namespace SupervisionTool
{
    internal class ProcessWatcher : INotifyPropertyChanged
    {
        public ProcessWatcher(string processName, int apiPort, HttpClient client)
        {
            ProcessName = processName;
            ApiPort = apiPort;
            Status = eServiceStatus.stopped;
            StartWatchingProcess();
            Client = client;
        }

        private void StartWatchingProcess()
        {
            System.Timers.Timer _timer1 = new System.Timers.Timer();
            _timer1.Elapsed += new ElapsedEventHandler(WatchProcess);
            _timer1.Interval = 3000; //3 seconds
            _timer1.Start();
        }

        private void WatchProcess(object sender, ElapsedEventArgs e)
        {
            bool statusIsOK = false;
            try
            {
                statusIsOK = GetStatusAsync("http://127.0.0.1:7210/v1/websiteparser/api/service/test").GetAwaiter().GetResult();
            }
            catch (System.Net.Http.HttpRequestException ex)
            {
                statusIsOK = false;
            }
            if (statusIsOK)
                Status = eServiceStatus.running;
            else if (Process.GetProcessesByName("WebSiteParser").Any())
                Status = eServiceStatus.launching;
            else
                Status = eServiceStatus.stopped;
        }

        public string ProcessName { get; set; }
        public int ApiPort { get; set; }
        private eServiceStatus _status = eServiceStatus.stopped;
        public eServiceStatus Status
        {
            get { return _status; }
            set
            {
                _status = value;
                OnPropertyChanged("Status");
            }
        }

        public HttpClient Client { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        async Task<bool> GetStatusAsync(string path)
        {
            HttpResponseMessage response = await Client.GetAsync(path);
            return response.IsSuccessStatusCode;
        }
    }
}
