using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Marauder.Aeryn.Runner;

namespace Marauder.Aeryn.Forms
{
    class TestSetTreeViewMediator : ITestSetVisitor
    {
        private MainForm parent;
        private TreeView treeView;
        private TreeNode rootTestSetNode;
        private TreeNode currentTestSetNode;

        delegate void LoadTreeDelegate(string path);
        delegate void AddTestSetDelegate(string name);
        delegate void AddSetDelegate(string name);

        public TestSetTreeViewMediator(MainForm parent, TreeView treeView)
        {
            this.parent = parent;
            this.treeView = treeView;
        }

        public void Load( string path)
        {
            treeView.Nodes.Clear();
            rootTestSetNode = treeView.Nodes.Add(path);

            LoadTreeDelegate loadTree = new LoadTreeDelegate(LoadTree);
            loadTree.BeginInvoke(path, EndLoadTree, loadTree);
        }

        private void LoadTree(string path)
        {
            IExecute testExe = new ProcessExecuter();
            TestSetReader ts = new TestSetReader(this, testExe);
            ts.Read(path);
        }

        private void EndLoadTree(IAsyncResult result)
        {
            try
            {
                LoadTreeDelegate loadTree = (LoadTreeDelegate)result.AsyncState;
                loadTree.EndInvoke(result);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Load Test Set Tree Error.");
            }
        }

        public void TestSet(string name)
        {
            AddTestSetDelegate addTestSet = new AddTestSetDelegate(AddTestSet);
            parent.Invoke(addTestSet, new object[] { name });
        }

        public void Test(string name)
        {
            AddTestSetDelegate addTestSet = new AddTestSetDelegate(AddTest);
            parent.Invoke(addTestSet, new object[] { name });
        }

        public void AddTestSet(string name)
        {
            currentTestSetNode = rootTestSetNode.Nodes.Add(name);
            treeView.ExpandAll();
        }

        public void AddTest(string name)
        {
            currentTestSetNode.Nodes.Add(name);
            treeView.ExpandAll();
        }
    }
}
