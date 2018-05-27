using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SupervisionTool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Data = new SupervisionToolData();
            DataContext = Data;
            Loaded += OnLoaded;
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            client.BaseAddress = new Uri("http://127.0.0.1:7210/");
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(
                new MediaTypeWithQualityHeaderValue("application/json"));

            webSiteParserWatcher = new ProcessWatcher("WebSiteParser", 7210, client);
            //sentenceEncrypterWatcher = new ProcessWatcher("SentenceEncrypter", 7211, client2);
            //dbSaverWatcher = new ProcessWatcher("DBSaver", 7212, client3);

            webSiteParserWatcher.PropertyChanged += WebSiteParserWatcher_PropertyChanged;
            Data.PropertyChanged += Data_PropertyChanged;
        }

        private void Data_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "WebSiteParserStatus" && Data.WebSiteParserStatus == eServiceStatus.running)
            {
                SendURLsToParse();
            }
        }

        private void SendURLsToParse()
        {
            //TODO : should send a POST request to WebSiteParser with urls in body
        }

        private void WebSiteParserWatcher_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "Status")
            {
                Data.WebSiteParserStatus = webSiteParserWatcher.Status;
            }
        }

        static HttpClient client = new HttpClient();

        private ProcessWatcher webSiteParserWatcher;
        //private ProcessWatcher sentenceEncrypterWatcher;
        //private ProcessWatcher dbSaverWatcher;
        private SupervisionToolData Data { get; set; }

        private void WebSiteParser_Configure_Click(object sender, RoutedEventArgs e)
        {
            //TODO : should open a window to edit the URL list
            Data.Urls.Add("https://fr.wikipedia.org/wiki/Louis_Armstrong");
            Data.Urls.Add("https://fr.wikipedia.org/wiki/Neil_Armstrong");
            MessageBox.Show("WebSiteParser configured OK");
        }

        private void WebSiteParser_Start_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Process.Start(".\\services\\WebSiteParser.exe");
                Data.WebSiteParserStatus = eServiceStatus.launching;
            }
            catch (Exception ex)
            {
                var currentDir = System.IO.Directory.GetCurrentDirectory();
                MessageBox.Show("An error occured while trying to launch WebSiteParser.exe.\n" +
                    "Please note the exe should be in " + currentDir + "\\services directory\n" +
                    "The error is: " + ex.Message);
            }
        }

        private void WebSiteParser_Stop_Click(object sender, RoutedEventArgs e)
        {
            foreach (var process in Process.GetProcessesByName("WebSiteParser"))
            {
                process.Kill();
                Data.WebSiteParserStatus = eServiceStatus.stopped;
            }
        }

        private void SentenceEncrypter_Configure_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SentenceEncrypter_Start_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SentenceEncrypter_Stop_Click(object sender, RoutedEventArgs e)
        {

        }

        private void DBSaver_Configure_Click(object sender, RoutedEventArgs e)
        {

        }

        private void DBSaver_Start_Click(object sender, RoutedEventArgs e)
        {

        }

        private void DBSaver_Stop_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
