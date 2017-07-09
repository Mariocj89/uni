namespace QuercusEventChain
{
    partial class AxisController
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this._amc = new AxAXISMEDIACONTROLLib.AxAxisMediaControl();
            this.cmsOptions = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.x480ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.x360ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.x240ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.x180ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.x120ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this._amc)).BeginInit();
            this.cmsOptions.SuspendLayout();
            this.SuspendLayout();
            // 
            // _amc
            // 
            this._amc.Enabled = true;
            this._amc.Location = new System.Drawing.Point(12, 12);
            this._amc.Name = "_amc";
            this._amc.OcxState = ((System.Windows.Forms.AxHost.State)(QES.Properties.Resources.ResourceManager.GetObject("_amcOcxState"))); 
            this._amc.Size = new System.Drawing.Size(640, 480);
            this._amc.TabIndex = 0;
            this._amc.OnDoubleClick += new AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnDoubleClickEventHandler(this.amcView_OnDoubleClick);
            // 
            // cmsOptions
            // 
            this.cmsOptions.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.x480ToolStripMenuItem,
            this.x360ToolStripMenuItem,
            this.x240ToolStripMenuItem,
            this.x180ToolStripMenuItem,
            this.x120ToolStripMenuItem});
            this.cmsOptions.Name = "cmsOptions";
            this.cmsOptions.Size = new System.Drawing.Size(128, 114);
            // 
            // x480ToolStripMenuItem
            // 
            this.x480ToolStripMenuItem.Name = "x480ToolStripMenuItem";
            this.x480ToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.x480ToolStripMenuItem.Text = "640x480";
            this.x480ToolStripMenuItem.Click += new System.EventHandler(this.x480ToolStripMenuItem_Click);
            // 
            // x360ToolStripMenuItem
            // 
            this.x360ToolStripMenuItem.Name = "x360ToolStripMenuItem";
            this.x360ToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.x360ToolStripMenuItem.Text = "480x360";
            this.x360ToolStripMenuItem.Click += new System.EventHandler(this.x360ToolStripMenuItem_Click);
            // 
            // x240ToolStripMenuItem
            // 
            this.x240ToolStripMenuItem.Name = "x240ToolStripMenuItem";
            this.x240ToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.x240ToolStripMenuItem.Text = "320x240";
            this.x240ToolStripMenuItem.Click += new System.EventHandler(this.x240ToolStripMenuItem_Click);
            // 
            // x180ToolStripMenuItem
            // 
            this.x180ToolStripMenuItem.Name = "x180ToolStripMenuItem";
            this.x180ToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.x180ToolStripMenuItem.Text = "240x180";
            this.x180ToolStripMenuItem.Click += new System.EventHandler(this.x180ToolStripMenuItem_Click);
            // 
            // x120ToolStripMenuItem
            // 
            this.x120ToolStripMenuItem.Name = "x120ToolStripMenuItem";
            this.x120ToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.x120ToolStripMenuItem.Text = "160x120";
            this.x120ToolStripMenuItem.Click += new System.EventHandler(this.x120ToolStripMenuItem_Click);
            // 
            // AxisController
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(663, 503);
            this.Controls.Add(this._amc);
            this.Name = "AxisController";
            ((System.ComponentModel.ISupportInitialize)(this._amc)).EndInit();
            this.cmsOptions.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip cmsOptions;
        private System.Windows.Forms.ToolStripMenuItem x480ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem x360ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem x240ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem x180ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem x120ToolStripMenuItem;
    }
}