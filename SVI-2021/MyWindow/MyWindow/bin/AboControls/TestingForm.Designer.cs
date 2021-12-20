namespace AboControls
{
    partial class TestingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.customNumberBox1 = new AboControls.ExtendedControls.CustomNumberBox();
            this.aboNumberBox1 = new AboControls.ExtendedControls.AboNumberBox();
            this.delayedTextBox1 = new AboControls.ExtendedControls.DelayedTextBox();
            this.numericTextBox1 = new AboControls.ExtendedControls.NumericTextBox();
            this.SuspendLayout();
            // 
            // customNumberBox1
            // 
            this.customNumberBox1.Location = new System.Drawing.Point(226, 101);
            this.customNumberBox1.Name = "customNumberBox1";
            this.customNumberBox1.Size = new System.Drawing.Size(258, 120);
            this.customNumberBox1.TabIndex = 1;
            this.customNumberBox1.Text = "customNumberBox1";
            // 
            // aboNumberBox1
            // 
            this.aboNumberBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.aboNumberBox1.Increment = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.aboNumberBox1.Location = new System.Drawing.Point(552, 51);
            this.aboNumberBox1.Maximum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.aboNumberBox1.Minimum = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.aboNumberBox1.Name = "aboNumberBox1";
            this.aboNumberBox1.Size = new System.Drawing.Size(80, 20);
            this.aboNumberBox1.TabIndex = 0;
            this.aboNumberBox1.Text = "aboNumberBox1";
            this.aboNumberBox1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // delayedTextBox1
            // 
            this.delayedTextBox1.Location = new System.Drawing.Point(491, 86);
            this.delayedTextBox1.Name = "delayedTextBox1";
            this.delayedTextBox1.Size = new System.Drawing.Size(100, 20);
            this.delayedTextBox1.TabIndex = 2;
            // 
            // numericTextBox1
            // 
            this.numericTextBox1.AllowControl = true;
            this.numericTextBox1.AllowDecimal = true;
            this.numericTextBox1.AllowMultipleDecimals = true;
            this.numericTextBox1.AllowNegation = true;
            this.numericTextBox1.DecimalValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.numericTextBox1.IntegerValue = 0;
            this.numericTextBox1.Location = new System.Drawing.Point(239, 27);
            this.numericTextBox1.Multiline = true;
            this.numericTextBox1.Name = "numericTextBox1";
            this.numericTextBox1.Size = new System.Drawing.Size(100, 262);
            this.numericTextBox1.TabIndex = 3;
            // 
            // TestingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
            this.ClientSize = new System.Drawing.Size(725, 350);
            this.Controls.Add(this.numericTextBox1);
            this.Controls.Add(this.delayedTextBox1);
            this.Controls.Add(this.customNumberBox1);
            this.Controls.Add(this.aboNumberBox1);
            this.KeyPreview = true;
            this.Name = "TestingForm";
            this.TransparencyKey = System.Drawing.Color.Magenta;
            this.ResumeLayout(false);
            this.PerformLayout();

        }
















































































































        #endregion

        private ExtendedControls.AboNumberBox aboNumberBox1;
        private ExtendedControls.CustomNumberBox customNumberBox1;
        private ExtendedControls.DelayedTextBox delayedTextBox1;
        private ExtendedControls.NumericTextBox numericTextBox1;
    }
}