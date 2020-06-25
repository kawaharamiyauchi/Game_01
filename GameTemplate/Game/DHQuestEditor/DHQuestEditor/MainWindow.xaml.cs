using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace DHQuestEditor
{

    struct QuestPalam
    {
        uint nameCount;
        byte questname;
        uint SummryCount;
        uint Summry;
        uint Quest;
    }
    
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            StreamReader sr = new StreamReader(
            "MH01.que", Encoding.GetEncoding("Shift_JIS"));
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
          
        }
    }
}
