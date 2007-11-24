using System;
/*using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;*/
using System.Windows.Forms;
using Marauder.Aeryn.Runner;

namespace Marauder.Aeryn.Forms
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }        

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using( OpenFileDialog ofd = new OpenFileDialog() )
            {
                DialogResult result = ofd.ShowDialog();
                if (DialogResult.OK == result)
                {
                    string path = ofd.FileName;
                    this.Text = path;
                    TestSetTreeViewMediator testSetTreeMed = new TestSetTreeViewMediator(this, this.testSetsTreeView);
                    testSetTreeMed.Load(path);
                }
            }
        }

      
    }
}
