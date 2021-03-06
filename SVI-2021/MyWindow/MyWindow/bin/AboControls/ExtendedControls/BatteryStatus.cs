using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace AboControls.ExtendedControls
{
    public class BatteryStatus : Control
    {
        private bool _flipOnX;
        private float _powerLevel = 1f;
        private Color _batteryColor = Color.CornflowerBlue;
        private Brush _batteryBrush = Brushes.YellowGreen;
        private Brush  _backBrush = Brushes.White;
        private LinearGradientBrush _LGB;
        private Graphics _graphicsBuffer;
        private Bitmap _drawingSurface;

        //The dimensions for the graphical elements
        private Rectangle _batteryNode, _batteryBox1, _batteryBox2, _batteryBox3;

        //Per is short for percent, all custom graphics are
        //dimensioned by the forms size. (A percentage of the form dims)
        private float _nodeWidthPercent = 0.08f;
        private float _nodeHeightPercent = 0.27f;
        private float _strokePercent = 0.02f;
        private float _paddingPercent = 0.02f;

        public BatteryStatus()
        {
            this.Size = new Size(100, 50);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint, true);
            SetLinearGradient(_batteryColor);
            _batteryBrush = new SolidBrush(_batteryColor);
            SetDimensions();
        }

        private void UpdateGraphicsBuffer()
        {
            _drawingSurface = new Bitmap(this.Width, this.Height);
            _graphicsBuffer = Graphics.FromImage(_drawingSurface);
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);
            SetLinearGradient(_batteryColor);
            UpdateGraphicsBuffer();
        }
        private void SetLinearGradient(Color color)
        {
            Rectangle rect = new Rectangle(Point.Empty, new Size(this.Width, this.Height / 2));
            _LGB = new LinearGradientBrush(rect, color, AdjustBrightness(color, 1.2f), 90f);
            _LGB.WrapMode = WrapMode.TileFlipX;
        }

        private static Color AdjustBrightness(Color c1, float factor)
        {
            float r = ((c1.R * factor) > 255) ? 255 : (c1.R * factor);
            float g = ((c1.G * factor) > 255) ? 255 : (c1.G * factor);
            float b = ((c1.B * factor) > 255) ? 255 : (c1.B * factor);
            return Color.FromArgb(c1.A, (int)r, (int)g, (int)b);
        }

        private void RotateGraphics()
        {
            _graphicsBuffer.TranslateTransform((float)this.Width / 2, (float)this.Height / 2);
            _graphicsBuffer.RotateTransform(180);
            _graphicsBuffer.TranslateTransform(-(float)this.Width / 2, -(float)this.Height / 2);
        }

        protected override void OnBackColorChanged(EventArgs e)
        {
            _backBrush = new SolidBrush(this.BackColor);
            base.OnBackColorChanged(e);
        }

        /// <summary>
        /// Sets the location and size of the various proportions of the control
        /// </summary>
        private void SetDimensions()
        {
            _batteryNode.Width = (int)(this.Width * _nodeWidthPercent + 0.5);
            _batteryNode.Height = (int)(this.Height * _nodeHeightPercent + 0.5);
            _batteryNode.X = 0;
            _batteryNode.Y = this.Height / 2 - (_batteryNode.Height / 2);

            _batteryBox1.Width = this.Width - _batteryNode.Width;
            _batteryBox1.Height = this.Height;
            _batteryBox1.X = _batteryNode.Width;
            _batteryBox1.Y = 0;

            int stroke = ((int)(this.Width * _strokePercent + 0.5)) * 2;
            _batteryBox2.Width = this.Width - (_batteryNode.Width + (stroke * 2));
            _batteryBox2.Height = this.Height - stroke * 2;
            _batteryBox2.X = _batteryNode.Width + stroke;
            _batteryBox2.Y = stroke;

            int padding = (int)(this.Width * _paddingPercent + 0.5);
            //Apply basic calculations
            _batteryBox3.Width = _batteryBox2.Width - padding * 2;
            //store width before applying power levels
            int lastWidth = _batteryBox3.Width;
            //APply powerlevel
            _batteryBox3.Width = (int)(_batteryBox3.Width * _powerLevel + 0.5f);
            _batteryBox3.Height = _batteryBox2.Height - padding * 2;
            _batteryBox3.X = _batteryBox2.X + padding;
            //Find the difference between widths and apply to x
            _batteryBox3.X += lastWidth - _batteryBox3.Width;
            _batteryBox3.Y = _batteryBox2.Y + padding;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            SetDimensions();

            _graphicsBuffer.Clear(this.BackColor);
            _graphicsBuffer.FillRectangle(_batteryBrush, _batteryNode);
            _graphicsBuffer.FillRectangle(_batteryBrush, _batteryBox1);
            _graphicsBuffer.FillRectangle(_backBrush, _batteryBox2);
            _graphicsBuffer.FillRectangle(_LGB, _batteryBox3);

            e.Graphics.DrawImageUnscaled(_drawingSurface, Point.Empty);
        }

        #region Properties
        [Category("Dimension Percents")]
        public int PowerLevel
        {
            get { return (int)(_powerLevel * 100f + 0.5f); }
            set
            {
                if (value > 100) _powerLevel = 1;
                else if (value < 0) _powerLevel = 0;
                else _powerLevel = value / 100f;

                SetDimensions();
                this.Invalidate();
            }
        }

        [Category("Dimension Percents")]
        public int NodeWidth
        {
            get { return (int)(_nodeWidthPercent * 100f + 0.5f); }
            set
            {
                if (value > 30) _nodeWidthPercent = 0.3f;
                else if (value < 0) _nodeWidthPercent = 0;
                else _nodeWidthPercent = value / 100f;

                SetDimensions();
                this.Invalidate();
            }
        }

        [Category("Dimension Percents")]
        public int NodeHeight
        {
            get { return (int)(_nodeHeightPercent * 100f + 0.5f); }
            set
            {
                if (value > 90) _nodeHeightPercent = 0.9f;
                else if (value < 0) _nodeHeightPercent = 0;
                else _nodeHeightPercent = value / 100f;

                SetDimensions();
                this.Invalidate();
            }
        }

        [Category("Dimension Percents")]
        public int Stroke
        {
            get { return (int)(_strokePercent * 100f + 0.5f); }
            set
            {
                if (value > 10) _strokePercent = 0.1f;
                else if (value < 0) _strokePercent = 0;
                else _strokePercent = value / 100f;

                SetDimensions();
                this.Invalidate();
            }
        }

        [Category("Dimension Percents")]
        public int InnerPadding
        {
            get { return (int)(_paddingPercent * 100f + 0.5f); }
            set
            {
                // ange can be from 0-10
                if (value > 10)
                {
                    _paddingPercent = 0.1f;
                }
                else if (value < 0)
                {
                    _paddingPercent = 0;
                }
                else 
                {
                    _paddingPercent = value / 100f;
                }

                SetDimensions();
                this.Invalidate();
            }
        }

        [Category("Appearance")]
        public Color BatteryColor
        {
            get { return _batteryColor; }
            set
            {
                _batteryColor = value;
                SetLinearGradient(value);
                _batteryBrush = new SolidBrush(_batteryColor);
                this.Invalidate();
            }
        }

        [Category("Appearance")]
        public bool FlipOnX
        {
            get { return _flipOnX; }
            set
            {
                _flipOnX = value;
                RotateGraphics();
                this.Invalidate();
            }
        }
        #endregion
    }
}
