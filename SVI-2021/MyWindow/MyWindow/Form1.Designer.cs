
namespace WinFormsApp1
{

  

    partial class Form1
    {
      
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }
    
        

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.myButton3 = new WinFormsApp1.MyButton();
            this.myButton1 = new WinFormsApp1.MyButton();
            this.myButton4 = new WinFormsApp1.MyButton();
            this.openFileDialog2 = new System.Windows.Forms.OpenFileDialog();
            this.myButton2 = new WinFormsApp1.MyButton();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.numberedrtb1 = new AboControls.UserControls.NumberedRTB();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // myButton3
            // 
            this.myButton3.BackColor = System.Drawing.Color.Tomato;
            this.myButton3.BackColorAdditional = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.myButton3.BackColorGradientEnabled = true;
            this.myButton3.BackColorGradientMode = System.Drawing.Drawing2D.LinearGradientMode.ForwardDiagonal;
            this.myButton3.BorderColor = System.Drawing.Color.Tomato;
            this.myButton3.BorderColorEnabled = false;
            this.myButton3.BorderColorOnHover = System.Drawing.Color.Tomato;
            this.myButton3.BorderColorOnHoverEnabled = false;
            this.myButton3.Cursor = System.Windows.Forms.Cursors.Hand;
            this.myButton3.Font = new System.Drawing.Font("Verdana", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.myButton3.ForeColor = System.Drawing.Color.Black;
            this.myButton3.Location = new System.Drawing.Point(16, 70);
            this.myButton3.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.myButton3.Name = "myButton3";
            this.myButton3.RippleColor = System.Drawing.Color.Black;
            this.myButton3.Rounding = 50;
            this.myButton3.RoundingEnable = true;
            this.myButton3.Size = new System.Drawing.Size(129, 58);
            this.myButton3.TabIndex = 3;
            this.myButton3.TabStop = false;
            this.myButton3.Text = "Открыть файл";
            this.myButton3.TextHover = null;
            this.myButton3.UseDownPressEffectOnClick = false;
            this.myButton3.UseRippleEffect = true;
            this.myButton3.UseZoomEffectOnHover = false;
            this.myButton3.Click += new System.EventHandler(this.myButton3_Click);
            // 
            // myButton1
            // 
            this.myButton1.BackColor = System.Drawing.Color.Tomato;
            this.myButton1.BackColorAdditional = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.myButton1.BackColorGradientEnabled = true;
            this.myButton1.BackColorGradientMode = System.Drawing.Drawing2D.LinearGradientMode.BackwardDiagonal;
            this.myButton1.BorderColor = System.Drawing.Color.Tomato;
            this.myButton1.BorderColorEnabled = false;
            this.myButton1.BorderColorOnHover = System.Drawing.Color.Tomato;
            this.myButton1.BorderColorOnHoverEnabled = false;
            this.myButton1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.myButton1.Font = new System.Drawing.Font("Verdana", 10.32F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.myButton1.ForeColor = System.Drawing.Color.Black;
            this.myButton1.Location = new System.Drawing.Point(169, 70);
            this.myButton1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.myButton1.Name = "myButton1";
            this.myButton1.RippleColor = System.Drawing.Color.Black;
            this.myButton1.Rounding = 50;
            this.myButton1.RoundingEnable = true;
            this.myButton1.Size = new System.Drawing.Size(139, 58);
            this.myButton1.TabIndex = 4;
            this.myButton1.Text = "Сохранить Файл";
            this.myButton1.TextHover = null;
            this.myButton1.UseDownPressEffectOnClick = true;
            this.myButton1.UseRippleEffect = true;
            this.myButton1.UseZoomEffectOnHover = false;
            this.myButton1.Click += new System.EventHandler(this.myButton1_Click);
            // 
            // myButton4
            // 
            this.myButton4.BackColor = System.Drawing.Color.Tomato;
            this.myButton4.BackColorAdditional = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.myButton4.BackColorGradientEnabled = true;
            this.myButton4.BackColorGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Horizontal;
            this.myButton4.BorderColor = System.Drawing.Color.Black;
            this.myButton4.BorderColorEnabled = false;
            this.myButton4.BorderColorOnHover = System.Drawing.Color.Tomato;
            this.myButton4.BorderColorOnHoverEnabled = false;
            this.myButton4.Cursor = System.Windows.Forms.Cursors.Hand;
            this.myButton4.Font = new System.Drawing.Font("Verdana", 16.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.myButton4.ForeColor = System.Drawing.Color.Black;
            this.myButton4.Location = new System.Drawing.Point(16, 190);
            this.myButton4.Name = "myButton4";
            this.myButton4.RippleColor = System.Drawing.Color.Black;
            this.myButton4.Rounding = 50;
            this.myButton4.RoundingEnable = true;
            this.myButton4.Size = new System.Drawing.Size(292, 123);
            this.myButton4.TabIndex = 5;
            this.myButton4.Text = "Compile";
            this.myButton4.TextHover = null;
            this.myButton4.UseDownPressEffectOnClick = false;
            this.myButton4.UseRippleEffect = true;
            this.myButton4.UseZoomEffectOnHover = false;
            this.myButton4.Click += new System.EventHandler(this.myButton4_Click);
            // 
            // openFileDialog2
            // 
            this.openFileDialog2.FileName = "openFileDialog2";
            // 
            // myButton2
            // 
            this.myButton2.BackColor = System.Drawing.Color.Tomato;
            this.myButton2.BackColorAdditional = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.myButton2.BackColorGradientEnabled = true;
            this.myButton2.BackColorGradientMode = System.Drawing.Drawing2D.LinearGradientMode.ForwardDiagonal;
            this.myButton2.BorderColor = System.Drawing.Color.White;
            this.myButton2.BorderColorEnabled = true;
            this.myButton2.BorderColorOnHover = System.Drawing.Color.Tomato;
            this.myButton2.BorderColorOnHoverEnabled = true;
            this.myButton2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.myButton2.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.myButton2.ForeColor = System.Drawing.Color.Black;
            this.myButton2.Location = new System.Drawing.Point(16, 545);
            this.myButton2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.myButton2.Name = "myButton2";
            this.myButton2.RippleColor = System.Drawing.Color.Black;
            this.myButton2.Rounding = 90;
            this.myButton2.RoundingEnable = true;
            this.myButton2.Size = new System.Drawing.Size(88, 90);
            this.myButton2.TabIndex = 6;
            this.myButton2.Text = "Изменить параметр out";
            this.myButton2.TextHover = null;
            this.myButton2.UseDownPressEffectOnClick = false;
            this.myButton2.UseRippleEffect = true;
            this.myButton2.UseZoomEffectOnHover = false;
            this.myButton2.Click += new System.EventHandler(this.myButton2_Click);
            // 
            // textBox1
            // 
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(0, 656);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(1292, 27);
            this.textBox1.TabIndex = 7;
            this.textBox1.TabStop = false;
            // 
            // numberedrtb1
            // 
            this.numberedrtb1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numberedrtb1.AutoValidate = System.Windows.Forms.AutoValidate.EnableAllowFocusChange;
            this.numberedrtb1.BackColor = System.Drawing.SystemColors.Window;
            this.numberedrtb1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.numberedrtb1.Location = new System.Drawing.Point(345, 0);
            this.numberedrtb1.Margin = new System.Windows.Forms.Padding(5, 8, 5, 8);
            this.numberedrtb1.Name = "numberedrtb1";
            this.numberedrtb1.Size = new System.Drawing.Size(945, 681);
            this.numberedrtb1.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1292, 683);
            this.Controls.Add(this.numberedrtb1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.myButton4);
            this.Controls.Add(this.myButton1);
            this.Controls.Add(this.myButton3);
            this.Controls.Add(this.myButton2);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private MyButton myButton3;
        private MyButton myButton1;
        private MyButton myButton4;
        private System.Windows.Forms.OpenFileDialog openFileDialog2;
        private MyButton myButton2;
        private System.Windows.Forms.TextBox textBox1;
        private AboControls.UserControls.NumberedRTB numberedrtb1;
    }
}

