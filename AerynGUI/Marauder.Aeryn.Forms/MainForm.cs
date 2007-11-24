using System;
/*using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;*/
using System.Windows.Forms;

namespace Marauder.Aeryn.Forms
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            TreeNode testSet1 = this.testSets.Nodes.Add("Test Set 1");
            testSet1.Nodes.Add("Test 1");
            testSet1.Nodes.Add("Test 2");


            TreeNode testSet2 = this.testSets.Nodes.Add("Test Set 2");
            testSet2.Nodes.Add("Test 3");
            testSet2.Nodes.Add("Test 4");

            testSets.ExpandAll();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using( OpenFileDialog ofd = new OpenFileDialog() )
            {
                DialogResult result = ofd.ShowDialog();
                if (DialogResult.OK == result)
                {
                    this.Text = ofd.FileName;
                }
            }
        }
    }
}