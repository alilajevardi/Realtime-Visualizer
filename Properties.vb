Imports System.Math
Public Class frmProperties
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
    Friend WithEvents GroupBox5 As System.Windows.Forms.GroupBox
    Friend WithEvents txtVolume As System.Windows.Forms.TextBox
    Friend WithEvents nudZ As System.Windows.Forms.NumericUpDown
    Friend WithEvents nudY As System.Windows.Forms.NumericUpDown
    Friend WithEvents nudX As System.Windows.Forms.NumericUpDown
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents chkTersoff_Bernner As System.Windows.Forms.CheckBox
    Friend WithEvents chkSutton_Chen As System.Windows.Forms.CheckBox
    Friend WithEvents chkMorse As System.Windows.Forms.CheckBox
    Friend WithEvents chkLennard_Jones As System.Windows.Forms.CheckBox
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents chkMVT As System.Windows.Forms.CheckBox
    Friend WithEvents chkNPT As System.Windows.Forms.CheckBox
    Friend WithEvents chkNVT As System.Windows.Forms.CheckBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents btnNext As System.Windows.Forms.Button
    Friend WithEvents btnCancel As System.Windows.Forms.Button
    Friend WithEvents nudNoParticle As System.Windows.Forms.NumericUpDown
    Friend WithEvents nudIteration As System.Windows.Forms.NumericUpDown
    Friend WithEvents gbInitial As System.Windows.Forms.GroupBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.GroupBox5 = New System.Windows.Forms.GroupBox
        Me.txtVolume = New System.Windows.Forms.TextBox
        Me.nudZ = New System.Windows.Forms.NumericUpDown
        Me.nudY = New System.Windows.Forms.NumericUpDown
        Me.nudX = New System.Windows.Forms.NumericUpDown
        Me.Label8 = New System.Windows.Forms.Label
        Me.Label7 = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.chkTersoff_Bernner = New System.Windows.Forms.CheckBox
        Me.chkSutton_Chen = New System.Windows.Forms.CheckBox
        Me.chkMorse = New System.Windows.Forms.CheckBox
        Me.chkLennard_Jones = New System.Windows.Forms.CheckBox
        Me.GroupBox3 = New System.Windows.Forms.GroupBox
        Me.chkMVT = New System.Windows.Forms.CheckBox
        Me.chkNPT = New System.Windows.Forms.CheckBox
        Me.chkNVT = New System.Windows.Forms.CheckBox
        Me.gbInitial = New System.Windows.Forms.GroupBox
        Me.nudIteration = New System.Windows.Forms.NumericUpDown
        Me.nudNoParticle = New System.Windows.Forms.NumericUpDown
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.btnNext = New System.Windows.Forms.Button
        Me.btnCancel = New System.Windows.Forms.Button
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox5.SuspendLayout()
        CType(Me.nudZ, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudY, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudX, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.gbInitial.SuspendLayout()
        CType(Me.nudIteration, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudNoParticle, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.GroupBox5)
        Me.GroupBox1.Controls.Add(Me.GroupBox2)
        Me.GroupBox1.Controls.Add(Me.GroupBox3)
        Me.GroupBox1.Controls.Add(Me.gbInitial)
        Me.GroupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.GroupBox1.Location = New System.Drawing.Point(8, 16)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(488, 368)
        Me.GroupBox1.TabIndex = 1
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Properties"
        '
        'GroupBox5
        '
        Me.GroupBox5.Controls.Add(Me.txtVolume)
        Me.GroupBox5.Controls.Add(Me.nudZ)
        Me.GroupBox5.Controls.Add(Me.nudY)
        Me.GroupBox5.Controls.Add(Me.nudX)
        Me.GroupBox5.Controls.Add(Me.Label8)
        Me.GroupBox5.Controls.Add(Me.Label7)
        Me.GroupBox5.Controls.Add(Me.Label6)
        Me.GroupBox5.Controls.Add(Me.Label5)
        Me.GroupBox5.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.GroupBox5.Location = New System.Drawing.Point(288, 200)
        Me.GroupBox5.Name = "GroupBox5"
        Me.GroupBox5.Size = New System.Drawing.Size(184, 160)
        Me.GroupBox5.TabIndex = 3
        Me.GroupBox5.TabStop = False
        Me.GroupBox5.Text = "Initial Volume"
        '
        'txtVolume
        '
        Me.txtVolume.Enabled = False
        Me.txtVolume.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.txtVolume.Location = New System.Drawing.Point(87, 125)
        Me.txtVolume.Name = "txtVolume"
        Me.txtVolume.Size = New System.Drawing.Size(81, 22)
        Me.txtVolume.TabIndex = 8
        Me.txtVolume.Text = "0.00"
        '
        'nudZ
        '
        Me.nudZ.DecimalPlaces = 1
        Me.nudZ.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.nudZ.Increment = New Decimal(New Integer() {5, 0, 0, 0})
        Me.nudZ.Location = New System.Drawing.Point(87, 90)
        Me.nudZ.Maximum = New Decimal(New Integer() {500, 0, 0, 0})
        Me.nudZ.Name = "nudZ"
        Me.nudZ.Size = New System.Drawing.Size(81, 22)
        Me.nudZ.TabIndex = 7
        '
        'nudY
        '
        Me.nudY.DecimalPlaces = 1
        Me.nudY.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.nudY.Increment = New Decimal(New Integer() {5, 0, 0, 0})
        Me.nudY.Location = New System.Drawing.Point(87, 56)
        Me.nudY.Maximum = New Decimal(New Integer() {500, 0, 0, 0})
        Me.nudY.Name = "nudY"
        Me.nudY.Size = New System.Drawing.Size(81, 22)
        Me.nudY.TabIndex = 6
        '
        'nudX
        '
        Me.nudX.DecimalPlaces = 1
        Me.nudX.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.nudX.Increment = New Decimal(New Integer() {5, 0, 0, 0})
        Me.nudX.Location = New System.Drawing.Point(87, 24)
        Me.nudX.Maximum = New Decimal(New Integer() {500, 0, 0, 0})
        Me.nudX.Name = "nudX"
        Me.nudX.Size = New System.Drawing.Size(81, 22)
        Me.nudX.TabIndex = 5
        '
        'Label8
        '
        Me.Label8.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label8.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.Label8.Location = New System.Drawing.Point(16, 124)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(64, 24)
        Me.Label8.TabIndex = 4
        Me.Label8.Text = "Volume"
        Me.Label8.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'Label7
        '
        Me.Label7.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label7.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.Label7.Location = New System.Drawing.Point(16, 88)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(64, 24)
        Me.Label7.TabIndex = 3
        Me.Label7.Text = "Z Height"
        Me.Label7.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'Label6
        '
        Me.Label6.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label6.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.Label6.Location = New System.Drawing.Point(16, 56)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(64, 24)
        Me.Label6.TabIndex = 2
        Me.Label6.Text = "Y Width"
        Me.Label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'Label5
        '
        Me.Label5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label5.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.Label5.Location = New System.Drawing.Point(16, 24)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(64, 24)
        Me.Label5.TabIndex = 1
        Me.Label5.Text = "X Length"
        Me.Label5.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.chkTersoff_Bernner)
        Me.GroupBox2.Controls.Add(Me.chkSutton_Chen)
        Me.GroupBox2.Controls.Add(Me.chkMorse)
        Me.GroupBox2.Controls.Add(Me.chkLennard_Jones)
        Me.GroupBox2.Enabled = False
        Me.GroupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.GroupBox2.Location = New System.Drawing.Point(16, 32)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(240, 160)
        Me.GroupBox2.TabIndex = 0
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Potential"
        '
        'chkTersoff_Bernner
        '
        Me.chkTersoff_Bernner.Location = New System.Drawing.Point(16, 120)
        Me.chkTersoff_Bernner.Name = "chkTersoff_Bernner"
        Me.chkTersoff_Bernner.Size = New System.Drawing.Size(120, 24)
        Me.chkTersoff_Bernner.TabIndex = 3
        Me.chkTersoff_Bernner.Text = "Tersoff_Bernner"
        '
        'chkSutton_Chen
        '
        Me.chkSutton_Chen.Location = New System.Drawing.Point(16, 88)
        Me.chkSutton_Chen.Name = "chkSutton_Chen"
        Me.chkSutton_Chen.TabIndex = 2
        Me.chkSutton_Chen.Text = "Sutton_Chen"
        '
        'chkMorse
        '
        Me.chkMorse.Location = New System.Drawing.Point(16, 56)
        Me.chkMorse.Name = "chkMorse"
        Me.chkMorse.TabIndex = 1
        Me.chkMorse.Text = "Morse"
        '
        'chkLennard_Jones
        '
        Me.chkLennard_Jones.Location = New System.Drawing.Point(16, 24)
        Me.chkLennard_Jones.Name = "chkLennard_Jones"
        Me.chkLennard_Jones.TabIndex = 0
        Me.chkLennard_Jones.Text = "Lennard_Jones"
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.chkMVT)
        Me.GroupBox3.Controls.Add(Me.chkNPT)
        Me.GroupBox3.Controls.Add(Me.chkNVT)
        Me.GroupBox3.Enabled = False
        Me.GroupBox3.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.GroupBox3.Location = New System.Drawing.Point(288, 32)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(184, 160)
        Me.GroupBox3.TabIndex = 1
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Ensemble"
        '
        'chkMVT
        '
        Me.chkMVT.Location = New System.Drawing.Point(16, 116)
        Me.chkMVT.Name = "chkMVT"
        Me.chkMVT.Size = New System.Drawing.Size(144, 24)
        Me.chkMVT.TabIndex = 2
        Me.chkMVT.Text = "MVT (Grand Canonical)"
        '
        'chkNPT
        '
        Me.chkNPT.Location = New System.Drawing.Point(16, 68)
        Me.chkNPT.Name = "chkNPT"
        Me.chkNPT.TabIndex = 1
        Me.chkNPT.Text = "NPT (Isobaric)"
        '
        'chkNVT
        '
        Me.chkNVT.Location = New System.Drawing.Point(16, 24)
        Me.chkNVT.Name = "chkNVT"
        Me.chkNVT.Size = New System.Drawing.Size(120, 24)
        Me.chkNVT.TabIndex = 0
        Me.chkNVT.Text = "NVT (Canonical)"
        '
        'gbInitial
        '
        Me.gbInitial.Controls.Add(Me.nudIteration)
        Me.gbInitial.Controls.Add(Me.nudNoParticle)
        Me.gbInitial.Controls.Add(Me.Label2)
        Me.gbInitial.Controls.Add(Me.Label1)
        Me.gbInitial.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.gbInitial.Location = New System.Drawing.Point(16, 200)
        Me.gbInitial.Name = "gbInitial"
        Me.gbInitial.Size = New System.Drawing.Size(240, 160)
        Me.gbInitial.TabIndex = 2
        Me.gbInitial.TabStop = False
        Me.gbInitial.Text = "Initial Value"
        '
        'nudIteration
        '
        Me.nudIteration.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.nudIteration.Increment = New Decimal(New Integer() {100, 0, 0, 0})
        Me.nudIteration.Location = New System.Drawing.Point(119, 104)
        Me.nudIteration.Maximum = New Decimal(New Integer() {100000000, 0, 0, 0})
        Me.nudIteration.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.nudIteration.Name = "nudIteration"
        Me.nudIteration.Size = New System.Drawing.Size(105, 22)
        Me.nudIteration.TabIndex = 5
        Me.nudIteration.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'nudNoParticle
        '
        Me.nudNoParticle.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.nudNoParticle.Location = New System.Drawing.Point(119, 40)
        Me.nudNoParticle.Maximum = New Decimal(New Integer() {1000, 0, 0, 0})
        Me.nudNoParticle.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.nudNoParticle.Name = "nudNoParticle"
        Me.nudNoParticle.Size = New System.Drawing.Size(105, 22)
        Me.nudNoParticle.TabIndex = 4
        Me.nudNoParticle.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(12, 104)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(104, 24)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "Number of Iteration"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(12, 40)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(104, 24)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Number of particles"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'btnNext
        '
        Me.btnNext.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnNext.Location = New System.Drawing.Point(304, 392)
        Me.btnNext.Name = "btnNext"
        Me.btnNext.Size = New System.Drawing.Size(90, 25)
        Me.btnNext.TabIndex = 2
        Me.btnNext.Tag = "0"
        Me.btnNext.Text = "Next"
        '
        'btnCancel
        '
        Me.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnCancel.Location = New System.Drawing.Point(406, 392)
        Me.btnCancel.Name = "btnCancel"
        Me.btnCancel.Size = New System.Drawing.Size(90, 25)
        Me.btnCancel.TabIndex = 3
        Me.btnCancel.Tag = "0"
        Me.btnCancel.Text = "Cancel"
        '
        'frmProperties
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(520, 430)
        Me.ControlBox = False
        Me.Controls.Add(Me.btnCancel)
        Me.Controls.Add(Me.btnNext)
        Me.Controls.Add(Me.GroupBox1)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmProperties"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Properties of Simulation"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox5.ResumeLayout(False)
        CType(Me.nudZ, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudY, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudX, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox3.ResumeLayout(False)
        Me.gbInitial.ResumeLayout(False)
        CType(Me.nudIteration, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudNoParticle, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region


    Private Sub btnNext_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnNext.Click
        If nudX.Value = 0 And nudY.Value = 0 And nudZ.Value = 0 Then
            MsgBox("Please check length of X,Y and Z coordinate")
            Return
        End If

        Me.DialogResult = DialogResult.OK
        Me.Close()
    End Sub

    Private Sub btnCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCancel.Click
        Me.DialogResult = DialogResult.Cancel
        Me.Close()
    End Sub

 

    Private Sub nudX_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudX.LostFocus
        txtVolume.Text = Round((nudX.Value * nudY.Value * nudZ.Value), 2).ToString
    End Sub

    Private Sub nudY_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudY.LostFocus
        txtVolume.Text = Round((nudX.Value * nudY.Value * nudZ.Value), 2).ToString
    End Sub

    Private Sub nudZ_LostFocus(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudZ.LostFocus
        txtVolume.Text = Round((nudX.Value * nudY.Value * nudZ.Value), 2).ToString
    End Sub

    Private Sub nudX_ValueChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudX.ValueChanged
        txtVolume.Text = Round((nudX.Value * nudY.Value * nudZ.Value), 2).ToString
    End Sub

    Private Sub nudY_ValueChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudY.ValueChanged
        txtVolume.Text = Round((nudX.Value * nudY.Value * nudZ.Value), 2).ToString
    End Sub

    Private Sub nudZ_ValueChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudZ.ValueChanged
        txtVolume.Text = Round((nudX.Value * nudY.Value * nudZ.Value), 2).ToString
    End Sub
End Class
