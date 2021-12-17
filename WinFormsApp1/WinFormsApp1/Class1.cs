
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;


namespace WinFormsApp1
{
	class but : Button
	{
		#region
		private int RoundingPercent = 100;

        [DisplayName("Rounding [%]")]
		[DefaultValue(100)]
		[Description("Here would be something later")]
		public int Rounding 
		{ get => RoundingPercent;
			set 
				{
				if (value >= 0 && value <= 100) 
				{
					RoundingPercent = value;
					Refresh();
				}
				
			} }

        #endregion


		public but() : base() { }

	}




	public class MyButton : Control 
	{


		private StringFormat SF = new StringFormat();

		private bool MouseEntered = false;
		private bool MousePressed = false;

		Animation CurtainButtinAnim = new Animation();

		public MyButton() 
		{
			SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);
			DoubleBuffered = true;
			Size = new Size(100,30);

			BackColor = Color.Aquamarine;
			ForeColor = Color.Black;


			SF.Alignment = StringAlignment.Center;
			SF.LineAlignment = StringAlignment.Center;

			
		}

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

			Graphics graph = e.Graphics;
			graph.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;


			graph.Clear(Parent.BackColor);

			Rectangle rect = new Rectangle(0, 0, Width-1, Height-1);


			graph.DrawRectangle(new Pen(BackColor), rect);
			graph.FillRectangle(new SolidBrush(BackColor), rect);

			if (MouseEntered) 
			{
				graph.DrawRectangle(new Pen(Color.FromArgb(60, Color.White)), rect);
				graph.FillRectangle(new SolidBrush(Color.FromArgb(60, Color.White)), rect);
			}

			if (MousePressed) 
			{
				graph.DrawRectangle(new Pen(Color.FromArgb(30, Color.White)), rect);
				graph.FillRectangle(new SolidBrush(Color.FromArgb(30, Color.White)), rect);
			}

			graph.DrawString(Text, Font, new SolidBrush(ForeColor), rect, SF);
        }

        protected override void OnMouseEnter(EventArgs e)
        {
            base.OnMouseEnter(e);

			MouseEntered = true;
			Invalidate();
		}

        protected override void OnMouseLeave(EventArgs e)
        {
            base.OnMouseLeave(e);


			MouseEntered = false;

			Invalidate();
		}

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

			MousePressed = true;
			Invalidate();
        }


        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);

			MousePressed = false;
			Invalidate();
        }
    }
}
