using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CryphousTest
{
    static class Program
    {
        /// <summary>
        /// アプリケーションのメイン エントリ ポイントです。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());
            Application.Run(new Cryphous.MainForm(true));
        }
    }
}
