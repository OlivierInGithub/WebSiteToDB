using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SupervisionTool
{
    public enum eServiceStatus
    {
        stopped,
        launching,
        running
    }
    public class SupervisionToolData : INotifyPropertyChanged
    {
        public SupervisionToolData()
        {
            Urls = new ObservableCollection<string>();
        }

        #region Properties
        private eServiceStatus _WebSiteParserStatus = eServiceStatus.stopped;
        public eServiceStatus WebSiteParserStatus
        {
            get { return _WebSiteParserStatus; }
            set
            {
                if (value != _WebSiteParserStatus)
                {
                    _WebSiteParserStatus = value;
                    OnPropertyChanged("WebSiteParserStatus");
                }
            }
        }
        private eServiceStatus _SentenceEncrypterStatus = eServiceStatus.stopped;
        public eServiceStatus SentenceEncrypterStatus
        {
            get { return _SentenceEncrypterStatus; }
            set
            {
                if (value != _SentenceEncrypterStatus)
                {
                    _SentenceEncrypterStatus = value;
                    OnPropertyChanged("SentenceEncrypterStatus");
                }
            }
        }
        private eServiceStatus _DBSaverStatus = eServiceStatus.stopped;
        public eServiceStatus DBSaverStatus
        {
            get { return _DBSaverStatus; }
            set
            {
                if (value != _DBSaverStatus)
                {
                    _DBSaverStatus = value;
                    OnPropertyChanged("DBSaverStatus");
                }
            }
        }

        public ObservableCollection<String> Urls { get; set; }


        #endregion

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
