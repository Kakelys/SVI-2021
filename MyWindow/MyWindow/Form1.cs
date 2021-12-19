using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;



namespace WinFormsApp1
{




	public partial class Form1 : Form
	{
       

        public Form1()
		{
			//init();
			InitializeComponent();
			//Buttons();


			bool FileExist = false;
			if (File.Exists("last_file.txt")) { FileExist = true;}
			


			if (FileExist == true)
			{
				using (FileStream Last_File = new("last_file.txt", FileMode.Open)) {
					using (StreamReader read = new(Last_File))
					{
						openFileDialog1.FileName = read.ReadLine();
						if (openFileDialog1.FileName != "")
						{
							using (StreamReader TextToBox = new(openFileDialog1.FileName))
							{
								richTextBox1.Text = TextToBox.ReadToEnd();
							}
						}
					}
			}
			}
			else
			{
				using (FileStream Last_File = new("last_file.txt", FileMode.OpenOrCreate))
				{

				}
			}
		}








		//Открытие файла
		private void myButton3_Click(object sender, EventArgs e)
        {
			//Кнопка для открытия файла
			String FileName = "";

			if (openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				FileName = openFileDialog1.FileName;
			}
			else { return; }
			
			
			try
			{
				StreamReader file = new(FileName);
				richTextBox1.Text = file.ReadToEnd();
				file.Close();
				//Сохранение в файл, чтобы при последующих запусках открывался тот же файл
				using (FileStream Last_File = new("last_file.txt", FileMode.OpenOrCreate))
				{
					using (StreamWriter PathToFile = new(Last_File)) 
					{
						PathToFile.WriteLine(FileName);
					}


				}
				

			}
			catch
			{

			}

		}
		//Сохранение файла
		private void myButton1_Click(object sender, EventArgs e)
        {
			
			String FileName = openFileDialog1.FileName;
			File.WriteAllText(FileName, richTextBox1.Text);

		}

		//Запуске exe с нужным параметром
        private void myButton4_Click(object sender, EventArgs e)
        {
			//string FilePath = "C:\\papka\\programms\\Git\\SVI-2021\\Debug\\SVI-2021.exe";
			//Process.Start(FilePath);
			System.Diagnostics.Process p = new System.Diagnostics.Process();
			p.StartInfo.FileName = "C:\\papka\\programms\\Git\\SVI-2021\\Debug\\SVI-2021.exe";
			p.StartInfo.Arguments = "-in:" + openFileDialog1.FileName;
			p.Start();


		}

        private void richTextBox1_KeyDown(object sender, KeyEventArgs e)
        {

			if (e.KeyCode == Keys.S && e.Control)
			{

				myButton1_Click(sender, e);


				e.Handled = true;
			}

			if (e.KeyCode == Keys.O && e.Control)
			{

				myButton3_Click(sender, e);
				e.Handled = true;
			}
		}
    }
}

