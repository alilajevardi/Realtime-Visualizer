Imports System.IO
Public Class frmRetain
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
    Friend WithEvents GroupBox6 As System.Windows.Forms.GroupBox
    Friend WithEvents btnSelectFile As System.Windows.Forms.Button
    Friend WithEvents txtSelectPath As System.Windows.Forms.TextBox
    Friend WithEvents ofdSelectFile As System.Windows.Forms.OpenFileDialog
    Friend WithEvents btnPlay As System.Windows.Forms.Button
    Friend WithEvents btnCancel As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.GroupBox6 = New System.Windows.Forms.GroupBox
        Me.txtSelectPath = New System.Windows.Forms.TextBox
        Me.btnSelectFile = New System.Windows.Forms.Button
        Me.ofdSelectFile = New System.Windows.Forms.OpenFileDialog
        Me.btnPlay = New System.Windows.Forms.Button
        Me.btnCancel = New System.Windows.Forms.Button
        Me.GroupBox6.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox6
        '
        Me.GroupBox6.Controls.Add(Me.txtSelectPath)
        Me.GroupBox6.Location = New System.Drawing.Point(8, 24)
        Me.GroupBox6.Name = "GroupBox6"
        Me.GroupBox6.Size = New System.Drawing.Size(344, 64)
        Me.GroupBox6.TabIndex = 4
        Me.GroupBox6.TabStop = False
        Me.GroupBox6.Text = "Path and Name of Data File"
        '
        'txtSelectPath
        '
        Me.txtSelectPath.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(178, Byte))
        Me.txtSelectPath.Location = New System.Drawing.Point(9, 29)
        Me.txtSelectPath.Name = "txtSelectPath"
        Me.txtSelectPath.Size = New System.Drawing.Size(326, 20)
        Me.txtSelectPath.TabIndex = 3
        Me.txtSelectPath.Text = ""
        '
        'btnSelectFile
        '
        Me.btnSelectFile.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnSelectFile.Location = New System.Drawing.Point(262, 111)
        Me.btnSelectFile.Name = "btnSelectFile"
        Me.btnSelectFile.Size = New System.Drawing.Size(90, 25)
        Me.btnSelectFile.TabIndex = 4
        Me.btnSelectFile.Text = "Select File"
        '
        'btnPlay
        '
        Me.btnPlay.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnPlay.Location = New System.Drawing.Point(67, 111)
        Me.btnPlay.Name = "btnPlay"
        Me.btnPlay.Size = New System.Drawing.Size(90, 25)
        Me.btnPlay.TabIndex = 5
        Me.btnPlay.Text = "Play"
        '
        'btnCancel
        '
        Me.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnCancel.Location = New System.Drawing.Point(165, 111)
        Me.btnCancel.Name = "btnCancel"
        Me.btnCancel.Size = New System.Drawing.Size(90, 25)
        Me.btnCancel.TabIndex = 10
        Me.btnCancel.Text = "Cancel"
        '
        'frmRetain
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(368, 166)
        Me.Controls.Add(Me.btnCancel)
        Me.Controls.Add(Me.btnPlay)
        Me.Controls.Add(Me.GroupBox6)
        Me.Controls.Add(Me.btnSelectFile)
        Me.Name = "frmRetain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Retain Mode"
        Me.GroupBox6.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub btnPlay_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnPlay.Click
        If File.Exists(txtSelectPath.Text) Then
            Me.DialogResult = DialogResult.OK
            Me.Close()
        Else

            Dim msgResult As Integer
            msgResult = MsgBox("Please select true Data File", MsgBoxStyle.OKCancel)
            If msgResult = DialogResult.OK Then
                btnSelectFile_Click(sender, e)
            Else
                Return
            End If
        End If

    End Sub

    Private Sub btnCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCancel.Click
        Me.DialogResult = DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub btnSelectFile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSelectFile.Click
        ofdSelectFile.Filter = "dat files (*.dat)|*.dat|All files (*.*)|*.*"
        ofdSelectFile.ShowDialog()
        txtSelectPath.Text = ofdSelectFile.FileName 'to show DataFile path that selected by user
    End Sub
End Class
