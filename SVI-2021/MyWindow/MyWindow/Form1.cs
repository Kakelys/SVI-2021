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
using System.Threading;


namespace WinFormsApp1
{




	public partial class Form1 : Form
	{
       

        public Form1()
		{
			//init();
			InitializeComponent();
			//Buttons();

			numberedrtb1.RichTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(richTextBox1_KeyDown);
			bool FileExist = false;
			if (File.Exists("last_file.txt")) { FileExist = true;}
			


			if (FileExist == true)
			{
				//Работа с файлом "последних сохранений"
				using (FileStream Last_File = new("last_file.txt", FileMode.Open))
				{
					using (StreamReader read = new(Last_File))
					{
						//Если первая строка не пуста, то записать в текстовое поле всё из него
						openFileDialog1.FileName = read.ReadLine();
						if (openFileDialog1.FileName != "")
						{
							if(File.Exists(openFileDialog1.FileName))
							using (StreamReader TextToBox = new(openFileDialog1.FileName))
							{
								//richTextBox1.Text = TextToBox.ReadToEnd();
									numberedrtb1.RichTextBox.Text = TextToBox.ReadToEnd();
								//Если вторая строка пуста, то взять значение по умолчанию
								openFileDialog2.FileName = read.ReadLine();
								if (openFileDialog2.FileName == "" || openFileDialog2.FileName == "openFileDialog2")
								{
									openFileDialog2.FileName = "C:\\papka\\programms\\Git\\SVI-2021\\SVI-2021\\asm\\assembler\\asm.asm";
								}
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
				//richTextBox1.Text = file.ReadToEnd();
				numberedrtb1.RichTextBox.Text = file.ReadToEnd();
				file.Close();
				//Сохранение в файл, чтобы при последующих запусках открывался тот же файл
				using (FileStream Last_File = new("last_file.txt", FileMode.OpenOrCreate))
				{
					using (StreamWriter PathToFile = new(Last_File)) 
					{
						PathToFile.WriteLine(FileName);
						PathToFile.WriteLine(openFileDialog2.FileName);
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
			//File.WriteAllText(FileName, richTextBox1.Text);
			File.WriteAllText(FileName, numberedrtb1.RichTextBox.Text);
		}

		//Запуске exe с нужным параметром
        private void myButton4_Click(object sender, EventArgs e)
        {
			//string FilePath = "C:\\papka\\programms\\Git\\SVI-2021\\Debug\\SVI-2021.exe";
			//Process.Start(FilePath);
			//MessageBox.Show(openFileDialog1.FileName);
			System.Diagnostics.Process p = new System.Diagnostics.Process();
			p.StartInfo.FileName = "C:\\papka\\programms\\Git\\SVI-2021\\Debug\\SVI-2021.exe";
			p.StartInfo.Arguments = " -in:"+ openFileDialog1.FileName +" -out:" + openFileDialog2.FileName + " -c";
			//MessageBox.Show(p.StartInfo.Arguments);

			p.Start();


		}
		private void ClearTextBox(object obj)
		{
			textBox1.Text = "";

		}

		private void richTextBox1_KeyDown(object sender, KeyEventArgs e)
        {

			if (e.KeyCode == Keys.Tab) 
			{
				numberedrtb1.RichTextBox.SelectedText = "\t";
			}

			if (e.KeyCode == Keys.F5 && e.Control)
			{

				myButton1_Click(sender, e);
				myButton4_Click(sender, e);

				e.Handled = true;
			}

			if (e.KeyCode == Keys.S && e.Control)
			{

				myButton1_Click(sender, e);
			
				textBox1.Text = "File Saved...";

				TimerCallback tm = new TimerCallback(ClearTextBox);
				System.Threading.Timer timer = new System.Threading.Timer(tm, 0, 5000, 0);

				e.Handled = true;
			}



			if (e.KeyCode == Keys.O && e.Control)
			{

				myButton3_Click(sender, e);
				e.Handled = true;
			}
		}
		//out
		private void myButton2_Click(object sender, EventArgs e)
		{
			if (openFileDialog2.ShowDialog() == DialogResult.OK)
			{
				using (FileStream Last_File = new("last_file.txt", FileMode.OpenOrCreate))
				{
					using (StreamWriter PathToFile = new(Last_File))
					{
						PathToFile.WriteLine(openFileDialog1.FileName);
						PathToFile.WriteLine(openFileDialog2.FileName);
					}
				}
			}
			else { return; }


		}

        private void numberedrtb1_KeyDown(object sender, KeyEventArgs e)
        {
			if (e.KeyCode == Keys.S && e.Control)
			{

				myButton1_Click(sender, e);

				textBox1.Text = "File Saved...";

				TimerCallback tm = new TimerCallback(ClearTextBox);
				System.Threading.Timer timer = new System.Threading.Timer(tm, 0, 5000, 0);

				e.Handled = true;
			}



			if (e.KeyCode == Keys.O && e.Control)
			{

				myButton3_Click(sender, e);
				e.Handled = true;
			}
		}

        private void numberedrtb1_KeyDown_1(object sender, KeyEventArgs e)
        {

        }
    }
}

