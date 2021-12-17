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



namespace WinFormsApp1
{




	public partial class Form1 : Form
	{
       

        public Form1()
		{
			//init();
			InitializeComponent();
			//Buttons();
			
		}

		

			


		


		private void button1_Click(object sender, EventArgs e)
		{
			//Кнопка для открытия файла
			String FileName = "";

			if (openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				FileName = openFileDialog1.FileName;
			}
			//FileName = "C:\\papka\\programms\\Git\\SVI-2021\\lp_lab13\\in.txt";
			try
			{
				StreamReader file = new(FileName);
				richTextBox1.Text = file.ReadToEnd();
				file.Close();

				//Сохранение в файл, чтобы при последующих запусках открывался тот же файл

			}
			catch
			{

			}


		}

        private void button2_Click(object sender, EventArgs e)
        {

			//Кнопка для сохранения файла
			String FileName = openFileDialog1.FileName;
			//StreamWriter^ file = File::OpenWrite(FileName);
			//richTextBox1->Text = filename;
			//File::WriteAllText(filename, richTextBox1->Text);
			File.WriteAllText(FileName, richTextBox1.Text);

		}



    }
}

