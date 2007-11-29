using System;
using System.Windows.Forms;
using Marauder.Aeryn.Runner;

namespace Marauder.Aeryn.Forms
{
    public partial class MainForm : Form
    {
        private Stats stats = new Stats();
        
        public MainForm()
        {
            InitializeComponent();
            DisableControls();
        }

        private void ToggleControls(bool enabled)
        {
            testSetsTreeView.Enabled = enabled;
            totalTestCountLabel.Enabled = enabled;
            Refresh();
        }

        private void EnableControls()
        {
            ToggleControls(true);
        }

        private void DisableControls()
        {
            ToggleControls(false);
        }

        public override void Refresh()
        {
            totalTestCountLabel.Text = string.Format("Total Test Count: {0}",stats.TestCount);
            base.Refresh();
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
                    stats = new Stats();
                    TestSetTreeViewMediator testSetTreeMed = new TestSetTreeViewMediator(this, this.testSetsTreeView,stats);
                    testSetTreeMed.Load(path);
                    EnableControls();                    
                }
            }
        }      
    }

    class Stats
    {
        private int testCount = 0;

        public int TestCount
        {
            get { return testCount; }
        }

        public void IncTestCount()
        {
            ++testCount;
        }

    }
    
}
