Public Class frmControl

    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents NUDRadial As System.Windows.Forms.NumericUpDown
    Friend WithEvents NUDBlue As System.Windows.Forms.NumericUpDown
    Friend WithEvents NUDGreen As System.Windows.Forms.NumericUpDown
    Friend WithEvents NUDRed As System.Windows.Forms.NumericUpDown
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents NUDXCamera As System.Windows.Forms.NumericUpDown
    Friend WithEvents NUDYCamera As System.Windows.Forms.NumericUpDown
    Friend WithEvents NUDZCamera As System.Windows.Forms.NumericUpDown
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents CBOIp As System.Windows.Forms.ComboBox
    Friend WithEvents btnControlPuse As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.CBOIp = New System.Windows.Forms.ComboBox
        Me.Label11 = New System.Windows.Forms.Label
        Me.NUDRadial = New System.Windows.Forms.NumericUpDown
        Me.NUDBlue = New System.Windows.Forms.NumericUpDown
        Me.NUDGreen = New System.Windows.Forms.NumericUpDown
        Me.NUDRed = New System.Windows.Forms.NumericUpDown
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.Label7 = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.NUDZCamera = New System.Windows.Forms.NumericUpDown
        Me.NUDYCamera = New System.Windows.Forms.NumericUpDown
        Me.NUDXCamera = New System.Windows.Forms.NumericUpDown
        Me.btnControlPuse = New System.Windows.Forms.Button
        Me.GroupBox1.SuspendLayout()
        CType(Me.NUDRadial, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NUDBlue, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NUDGreen, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NUDRed, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox2.SuspendLayout()
        CType(Me.NUDZCamera, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NUDYCamera, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.NUDXCamera, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.CBOIp)
        Me.GroupBox1.Controls.Add(Me.Label11)
        Me.GroupBox1.Controls.Add(Me.NUDRadial)
        Me.GroupBox1.Controls.Add(Me.NUDBlue)
        Me.GroupBox1.Controls.Add(Me.NUDGreen)
        Me.GroupBox1.Controls.Add(Me.NUDRed)
        Me.GroupBox1.Controls.Add(Me.Label4)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Location = New System.Drawing.Point(10, 8)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(144, 200)
        Me.GroupBox1.TabIndex = 12
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Atoms"
        '
        'CBOIp
        '
        Me.CBOIp.Items.AddRange(New Object() {"0", "1", "2", "3", "4", "5"})
        Me.CBOIp.Location = New System.Drawing.Point(70, 37)
        Me.CBOIp.Name = "CBOIp"
        Me.CBOIp.Size = New System.Drawing.Size(64, 23)
        Me.CBOIp.TabIndex = 21
        '
        'Label11
        '
        Me.Label11.Location = New System.Drawing.Point(14, 38)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(48, 24)
        Me.Label11.TabIndex = 20
        Me.Label11.Text = "IP No."
        '
        'NUDRadial
        '
        Me.NUDRadial.AccessibleRole = System.Windows.Forms.AccessibleRole.None
        Me.NUDRadial.DecimalPlaces = 2
        Me.NUDRadial.Increment = New Decimal(New Integer() {1, 0, 0, 65536})
        Me.NUDRadial.Location = New System.Drawing.Point(70, 166)
        Me.NUDRadial.Maximum = New Decimal(New Integer() {2, 0, 0, 0})
        Me.NUDRadial.Minimum = New Decimal(New Integer() {1, 0, 0, 131072})
        Me.NUDRadial.Name = "NUDRadial"
        Me.NUDRadial.Size = New System.Drawing.Size(64, 21)
        Me.NUDRadial.TabIndex = 15
        Me.NUDRadial.Value = New Decimal(New Integer() {3, 0, 0, 65536})
        '
        'NUDBlue
        '
        Me.NUDBlue.AccessibleRole = System.Windows.Forms.AccessibleRole.None
        Me.NUDBlue.ForeColor = System.Drawing.Color.Blue
        Me.NUDBlue.Location = New System.Drawing.Point(70, 127)
        Me.NUDBlue.Maximum = New Decimal(New Integer() {255, 0, 0, 0})
        Me.NUDBlue.Name = "NUDBlue"
        Me.NUDBlue.Size = New System.Drawing.Size(64, 21)
        Me.NUDBlue.TabIndex = 14
        '
        'NUDGreen
        '
        Me.NUDGreen.AccessibleRole = System.Windows.Forms.AccessibleRole.None
        Me.NUDGreen.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.NUDGreen.ForeColor = System.Drawing.Color.Lime
        Me.NUDGreen.Location = New System.Drawing.Point(70, 101)
        Me.NUDGreen.Maximum = New Decimal(New Integer() {255, 0, 0, 0})
        Me.NUDGreen.Name = "NUDGreen"
        Me.NUDGreen.Size = New System.Drawing.Size(64, 21)
        Me.NUDGreen.TabIndex = 13
        Me.NUDGreen.Value = New Decimal(New Integer() {255, 0, 0, 0})
        '
        'NUDRed
        '
        Me.NUDRed.AccessibleRole = System.Windows.Forms.AccessibleRole.None
        Me.NUDRed.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.NUDRed.ForeColor = System.Drawing.Color.Red
        Me.NUDRed.Location = New System.Drawing.Point(70, 75)
        Me.NUDRed.Maximum = New Decimal(New Integer() {255, 0, 0, 0})
        Me.NUDRed.Name = "NUDRed"
        Me.NUDRed.Size = New System.Drawing.Size(64, 21)
        Me.NUDRed.TabIndex = 12
        '
        'Label4
        '
        Me.Label4.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.Label4.Location = New System.Drawing.Point(14, 166)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(48, 24)
        Me.Label4.TabIndex = 19
        Me.Label4.Text = "Radial"
        '
        'Label3
        '
        Me.Label3.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.Label3.ForeColor = System.Drawing.Color.Blue
        Me.Label3.Location = New System.Drawing.Point(14, 127)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(48, 24)
        Me.Label3.TabIndex = 18
        Me.Label3.Text = "Blue"
        '
        'Label2
        '
        Me.Label2.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.Label2.ForeColor = System.Drawing.Color.Lime
        Me.Label2.Location = New System.Drawing.Point(14, 101)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(48, 24)
        Me.Label2.TabIndex = 17
        Me.Label2.Text = "Green"
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.Label1.ForeColor = System.Drawing.Color.Red
        Me.Label1.Location = New System.Drawing.Point(14, 75)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 24)
        Me.Label1.TabIndex = 16
        Me.Label1.Text = "Red"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label7)
        Me.GroupBox2.Controls.Add(Me.Label6)
        Me.GroupBox2.Controls.Add(Me.Label5)
        Me.GroupBox2.Controls.Add(Me.NUDZCamera)
        Me.GroupBox2.Controls.Add(Me.NUDYCamera)
        Me.GroupBox2.Controls.Add(Me.NUDXCamera)
        Me.GroupBox2.Enabled = False
        Me.GroupBox2.Location = New System.Drawing.Point(10, 224)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(144, 136)
        Me.GroupBox2.TabIndex = 13
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Camera Position"
        '
        'Label7
        '
        Me.Label7.Location = New System.Drawing.Point(17, 98)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(29, 24)
        Me.Label7.TabIndex = 5
        Me.Label7.Text = "Z"
        '
        'Label6
        '
        Me.Label6.Location = New System.Drawing.Point(17, 66)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(29, 24)
        Me.Label6.TabIndex = 4
        Me.Label6.Text = "Y"
        '
        'Label5
        '
        Me.Label5.Location = New System.Drawing.Point(17, 33)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(29, 24)
        Me.Label5.TabIndex = 3
        Me.Label5.Text = "X"
        '
        'NUDZCamera
        '
        Me.NUDZCamera.DecimalPlaces = 1
        Me.NUDZCamera.Location = New System.Drawing.Point(54, 98)
        Me.NUDZCamera.Maximum = New Decimal(New Integer() {60, 0, 0, 0})
        Me.NUDZCamera.Minimum = New Decimal(New Integer() {60, 0, 0, -2147483648})
        Me.NUDZCamera.Name = "NUDZCamera"
        Me.NUDZCamera.Size = New System.Drawing.Size(72, 21)
        Me.NUDZCamera.TabIndex = 2
        Me.NUDZCamera.Value = New Decimal(New Integer() {30, 0, 0, 0})
        '
        'NUDYCamera
        '
        Me.NUDYCamera.DecimalPlaces = 1
        Me.NUDYCamera.Location = New System.Drawing.Point(54, 66)
        Me.NUDYCamera.Maximum = New Decimal(New Integer() {60, 0, 0, 0})
        Me.NUDYCamera.Minimum = New Decimal(New Integer() {60, 0, 0, -2147483648})
        Me.NUDYCamera.Name = "NUDYCamera"
        Me.NUDYCamera.Size = New System.Drawing.Size(72, 21)
        Me.NUDYCamera.TabIndex = 1
        '
        'NUDXCamera
        '
        Me.NUDXCamera.DecimalPlaces = 1
        Me.NUDXCamera.Location = New System.Drawing.Point(54, 34)
        Me.NUDXCamera.Maximum = New Decimal(New Integer() {60, 0, 0, 0})
        Me.NUDXCamera.Minimum = New Decimal(New Integer() {60, 0, 0, -2147483648})
        Me.NUDXCamera.Name = "NUDXCamera"
        Me.NUDXCamera.Size = New System.Drawing.Size(72, 21)
        Me.NUDXCamera.TabIndex = 0
        '
        'btnControlPuse
        '
        Me.btnControlPuse.Enabled = False
        Me.btnControlPuse.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnControlPuse.Location = New System.Drawing.Point(36, 373)
        Me.btnControlPuse.Name = "btnControlPuse"
        Me.btnControlPuse.Size = New System.Drawing.Size(90, 25)
        Me.btnControlPuse.TabIndex = 14
        Me.btnControlPuse.Tag = "0"
        Me.btnControlPuse.Text = "&Puse"
        '
        'frmControl
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 14)
        Me.ClientSize = New System.Drawing.Size(168, 406)
        Me.ControlBox = False
        Me.Controls.Add(Me.btnControlPuse)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.Location = New System.Drawing.Point(800, 100)
        Me.MaximizeBox = False
        Me.Name = "frmControl"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Control"
        Me.GroupBox1.ResumeLayout(False)
        CType(Me.NUDRadial, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NUDBlue, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NUDGreen, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NUDRed, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox2.ResumeLayout(False)
        CType(Me.NUDZCamera, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NUDYCamera, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.NUDXCamera, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub frmControl_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim II As Integer
        Dim IRed() As Integer = {255, 210, 255, 205, 180, 100}
        Dim IGreen() As Integer = {255, 255, 105, 200, 150, 200}
        Dim IBlue() As Integer = {255, 140, 50, 210, 230, 50}

        For II = 0 To 5
            AtomRed(II) = IRed(II)
            AtomGreen(II) = IGreen(II)
            AtomBlue(II) = IBlue(II)
            AtomRadial(II) = 0.3F

        Next
        CBOIp.SelectedIndex = 0

    End Sub


    Private Sub CBOIp_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CBOIp.SelectedIndexChanged

        NUDRed.Value = AtomRed(CBOIp.SelectedIndex)
        NUDGreen.Value = AtomGreen(CBOIp.SelectedIndex)
        NUDBlue.Value = AtomBlue(CBOIp.SelectedIndex)
        NUDRadial.Value = AtomRadial(CBOIp.SelectedIndex)

    End Sub

    Private Sub NUDRed_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDRed.ValueChanged

        If CBOIp.SelectedIndex >= 0 Then
            AtomRed(CBOIp.SelectedIndex) = CInt(NUDRed.Value)
        End If
    End Sub

    Private Sub NUDGreen_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDGreen.ValueChanged
        If CBOIp.SelectedIndex >= 0 Then
            AtomGreen(CBOIp.SelectedIndex) = CInt(NUDGreen.Value)
        End If
    End Sub

    Private Sub NUDBlue_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDBlue.ValueChanged
        If CBOIp.SelectedIndex >= 0 Then
            AtomBlue(CBOIp.SelectedIndex) = CInt(NUDBlue.Value)
        End If
    End Sub

    Private Sub NUDRadial_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDRadial.ValueChanged

        If CBOIp.SelectedIndex >= 0 Then
            AtomRadial(CBOIp.SelectedIndex) = CSng(NUDRadial.Value)
        End If
    End Sub

    Private Sub NUDXCamera_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDXCamera.ValueChanged
        Xcam = CSng(NUDXCamera.Value)
    End Sub

    Private Sub NUDYCamera_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDYCamera.ValueChanged
        Ycam = CSng(NUDYCamera.Value)
    End Sub

    Private Sub NUDZCamera_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NUDZCamera.ValueChanged
        Zcam = CSng(NUDZCamera.Value)
    End Sub


    
    Private Sub NUDRed_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDRed.LostFocus
        If CBOIp.SelectedIndex >= 0 Then
            AtomRed(CBOIp.SelectedIndex) = CInt(NUDRed.Value)
        End If
    End Sub

    Private Sub NUDGreen_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDGreen.LostFocus
        If CBOIp.SelectedIndex >= 0 Then
            AtomGreen(CBOIp.SelectedIndex) = CInt(NUDGreen.Value)
        End If
    End Sub

    Private Sub NUDBlue_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDBlue.LostFocus
        If CBOIp.SelectedIndex >= 0 Then
            AtomBlue(CBOIp.SelectedIndex) = CInt(NUDBlue.Value)
        End If
    End Sub

    Private Sub NUDRadial_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDRadial.LostFocus
        If CBOIp.SelectedIndex >= 0 Then
            AtomRadial(CBOIp.SelectedIndex) = CSng(NUDRadial.Value)
        End If
    End Sub

    Private Sub NUDXCamera_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDXCamera.LostFocus
        Xcam = CSng(NUDXCamera.Value)
    End Sub

    Private Sub NUDYCamera_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDYCamera.LostFocus
        Ycam = CSng(NUDYCamera.Value)
    End Sub

    Private Sub NUDZCamera_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles NUDZCamera.LostFocus
        Zcam = CSng(NUDZCamera.Value)
    End Sub

    Private Sub btnControlPuse_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnControlPuse.Click
        If btnControlPuse.Tag = 0 Then
            btnControlPuse.Tag = 1
        Else
            btnControlPuse.Tag = 0
        End If
    End Sub
End Class

