Imports System.IO
Imports System.Math
Imports System.Diagnostics
Public Class MainForm
    Inherits System.Windows.Forms.Form
    Dim FileNm As String = "Nano"
    Dim FilePth As String
    Public frmProperty As frmProperties = New frmProperties
    Public frmImmedaite As frmImmed = New frmImmed
    Public frmRetained As frmRetain = New frmRetain
    Public frmControls As frmControl = New frmControl


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
    Friend WithEvents MainMenu1 As System.Windows.Forms.MainMenu
    Friend WithEvents MenuItem1 As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem7 As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem8 As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem11 As System.Windows.Forms.MenuItem
    Friend WithEvents GroupBox7 As System.Windows.Forms.GroupBox
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents txtPotential As System.Windows.Forms.TextBox
    Friend WithEvents txtEnergy As System.Windows.Forms.TextBox
    Friend WithEvents txtTemp As System.Windows.Forms.TextBox
    Friend WithEvents txtStep As System.Windows.Forms.TextBox
    Friend WithEvents txtNumber As System.Windows.Forms.TextBox
    Friend WithEvents Label13 As System.Windows.Forms.Label
    Friend WithEvents mnuFileSaveAs As System.Windows.Forms.MenuItem
    Friend WithEvents sfdFileSaveAs As System.Windows.Forms.SaveFileDialog
    Friend WithEvents mnuFileOpen As System.Windows.Forms.MenuItem
    Friend WithEvents ofdFileOpen As System.Windows.Forms.OpenFileDialog
    Friend WithEvents mnuFileSave As System.Windows.Forms.MenuItem
    Friend WithEvents mnuFileNew As System.Windows.Forms.MenuItem
    Friend WithEvents mnuFileExit As System.Windows.Forms.MenuItem
    Friend WithEvents mnuFileClose As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem2 As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem3 As System.Windows.Forms.MenuItem
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents btnRunMain As System.Windows.Forms.Button
    Friend WithEvents gbInstant As System.Windows.Forms.GroupBox
    Friend WithEvents btnNoAnimation As System.Windows.Forms.Button
    Friend WithEvents rbImmediate As System.Windows.Forms.RadioButton
    Friend WithEvents rbRetain As System.Windows.Forms.RadioButton
    Friend WithEvents mnuHelpAbout As System.Windows.Forms.MenuItem
    Friend WithEvents hp As System.Windows.Forms.HelpProvider
    Friend WithEvents mnuHelpContent As System.Windows.Forms.MenuItem
    Friend WithEvents mnuHelpIndex As System.Windows.Forms.MenuItem
    Friend WithEvents mnuHelpSearch As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem4 As System.Windows.Forms.MenuItem
    Friend WithEvents mnuDemoC60 As System.Windows.Forms.MenuItem
    Friend WithEvents mnuDemoMolecule As System.Windows.Forms.MenuItem
    Friend WithEvents mnuDemoBox As System.Windows.Forms.MenuItem
    Friend WithEvents mnuDemoSphere As System.Windows.Forms.MenuItem
    Friend WithEvents Demo As System.Diagnostics.Process
    Friend WithEvents btnCancelMain As System.Windows.Forms.Button
    Friend WithEvents Timer2 As System.Windows.Forms.Timer
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.MainMenu1 = New System.Windows.Forms.MainMenu
        Me.MenuItem1 = New System.Windows.Forms.MenuItem
        Me.mnuFileNew = New System.Windows.Forms.MenuItem
        Me.mnuFileOpen = New System.Windows.Forms.MenuItem
        Me.MenuItem2 = New System.Windows.Forms.MenuItem
        Me.mnuFileSaveAs = New System.Windows.Forms.MenuItem
        Me.mnuFileSave = New System.Windows.Forms.MenuItem
        Me.MenuItem3 = New System.Windows.Forms.MenuItem
        Me.mnuFileClose = New System.Windows.Forms.MenuItem
        Me.MenuItem7 = New System.Windows.Forms.MenuItem
        Me.mnuFileExit = New System.Windows.Forms.MenuItem
        Me.MenuItem4 = New System.Windows.Forms.MenuItem
        Me.mnuDemoC60 = New System.Windows.Forms.MenuItem
        Me.mnuDemoMolecule = New System.Windows.Forms.MenuItem
        Me.mnuDemoBox = New System.Windows.Forms.MenuItem
        Me.mnuDemoSphere = New System.Windows.Forms.MenuItem
        Me.MenuItem8 = New System.Windows.Forms.MenuItem
        Me.mnuHelpContent = New System.Windows.Forms.MenuItem
        Me.mnuHelpIndex = New System.Windows.Forms.MenuItem
        Me.mnuHelpSearch = New System.Windows.Forms.MenuItem
        Me.MenuItem11 = New System.Windows.Forms.MenuItem
        Me.mnuHelpAbout = New System.Windows.Forms.MenuItem
        Me.GroupBox7 = New System.Windows.Forms.GroupBox
        Me.btnNoAnimation = New System.Windows.Forms.Button
        Me.gbInstant = New System.Windows.Forms.GroupBox
        Me.Label13 = New System.Windows.Forms.Label
        Me.txtNumber = New System.Windows.Forms.TextBox
        Me.Label12 = New System.Windows.Forms.Label
        Me.Label11 = New System.Windows.Forms.Label
        Me.Label10 = New System.Windows.Forms.Label
        Me.Label9 = New System.Windows.Forms.Label
        Me.txtPotential = New System.Windows.Forms.TextBox
        Me.txtEnergy = New System.Windows.Forms.TextBox
        Me.txtTemp = New System.Windows.Forms.TextBox
        Me.txtStep = New System.Windows.Forms.TextBox
        Me.sfdFileSaveAs = New System.Windows.Forms.SaveFileDialog
        Me.ofdFileOpen = New System.Windows.Forms.OpenFileDialog
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.rbRetain = New System.Windows.Forms.RadioButton
        Me.rbImmediate = New System.Windows.Forms.RadioButton
        Me.btnRunMain = New System.Windows.Forms.Button
        Me.hp = New System.Windows.Forms.HelpProvider
        Me.Demo = New System.Diagnostics.Process
        Me.btnCancelMain = New System.Windows.Forms.Button
        Me.Timer2 = New System.Windows.Forms.Timer(Me.components)
        Me.GroupBox7.SuspendLayout()
        Me.gbInstant.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'MainMenu1
        '
        Me.MainMenu1.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.MenuItem1, Me.MenuItem4, Me.MenuItem8})
        '
        'MenuItem1
        '
        Me.MenuItem1.Index = 0
        Me.MenuItem1.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuFileNew, Me.mnuFileOpen, Me.MenuItem2, Me.mnuFileSaveAs, Me.mnuFileSave, Me.MenuItem3, Me.mnuFileClose, Me.MenuItem7, Me.mnuFileExit})
        Me.MenuItem1.Text = "&File"
        '
        'mnuFileNew
        '
        Me.mnuFileNew.Index = 0
        Me.mnuFileNew.Shortcut = System.Windows.Forms.Shortcut.CtrlN
        Me.mnuFileNew.Text = "&New"
        '
        'mnuFileOpen
        '
        Me.mnuFileOpen.Index = 1
        Me.mnuFileOpen.Shortcut = System.Windows.Forms.Shortcut.CtrlO
        Me.mnuFileOpen.Text = "&Open"
        '
        'MenuItem2
        '
        Me.MenuItem2.Index = 2
        Me.MenuItem2.Text = "-"
        '
        'mnuFileSaveAs
        '
        Me.mnuFileSaveAs.Index = 3
        Me.mnuFileSaveAs.Text = "S&ave As..."
        '
        'mnuFileSave
        '
        Me.mnuFileSave.Index = 4
        Me.mnuFileSave.Shortcut = System.Windows.Forms.Shortcut.CtrlS
        Me.mnuFileSave.Text = "&Save"
        '
        'MenuItem3
        '
        Me.MenuItem3.Index = 5
        Me.MenuItem3.Text = "-"
        '
        'mnuFileClose
        '
        Me.mnuFileClose.Index = 6
        Me.mnuFileClose.Text = "&Close"
        '
        'MenuItem7
        '
        Me.MenuItem7.Index = 7
        Me.MenuItem7.Text = "-"
        '
        'mnuFileExit
        '
        Me.mnuFileExit.Index = 8
        Me.mnuFileExit.Shortcut = System.Windows.Forms.Shortcut.AltF4
        Me.mnuFileExit.Text = "E&xit"
        '
        'MenuItem4
        '
        Me.MenuItem4.Index = 1
        Me.MenuItem4.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuDemoC60, Me.mnuDemoMolecule, Me.mnuDemoBox, Me.mnuDemoSphere})
        Me.MenuItem4.Text = "&Demo"
        '
        'mnuDemoC60
        '
        Me.mnuDemoC60.Index = 0
        Me.mnuDemoC60.Text = "&C60"
        '
        'mnuDemoMolecule
        '
        Me.mnuDemoMolecule.Index = 1
        Me.mnuDemoMolecule.Text = "&Molecule"
        '
        'mnuDemoBox
        '
        Me.mnuDemoBox.Index = 2
        Me.mnuDemoBox.Text = "&Box"
        '
        'mnuDemoSphere
        '
        Me.mnuDemoSphere.Index = 3
        Me.mnuDemoSphere.Text = "&Sphere"
        '
        'MenuItem8
        '
        Me.MenuItem8.Index = 2
        Me.MenuItem8.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuHelpContent, Me.mnuHelpIndex, Me.mnuHelpSearch, Me.MenuItem11, Me.mnuHelpAbout})
        Me.MenuItem8.Text = "&Help"
        '
        'mnuHelpContent
        '
        Me.mnuHelpContent.Index = 0
        Me.mnuHelpContent.Text = "&Content"
        '
        'mnuHelpIndex
        '
        Me.mnuHelpIndex.Index = 1
        Me.mnuHelpIndex.Text = "&Index"
        '
        'mnuHelpSearch
        '
        Me.mnuHelpSearch.Index = 2
        Me.mnuHelpSearch.Text = "&Search"
        '
        'MenuItem11
        '
        Me.MenuItem11.Index = 3
        Me.MenuItem11.Text = "-"
        '
        'mnuHelpAbout
        '
        Me.mnuHelpAbout.Index = 4
        Me.mnuHelpAbout.Text = "Abo&ut"
        '
        'GroupBox7
        '
        Me.GroupBox7.Controls.Add(Me.btnNoAnimation)
        Me.GroupBox7.Location = New System.Drawing.Point(144, 20)
        Me.GroupBox7.Name = "GroupBox7"
        Me.GroupBox7.Size = New System.Drawing.Size(120, 120)
        Me.GroupBox7.TabIndex = 4
        Me.GroupBox7.TabStop = False
        Me.GroupBox7.Text = "Visualization"
        '
        'btnNoAnimation
        '
        Me.btnNoAnimation.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnNoAnimation.Location = New System.Drawing.Point(15, 53)
        Me.btnNoAnimation.Name = "btnNoAnimation"
        Me.btnNoAnimation.Size = New System.Drawing.Size(90, 25)
        Me.btnNoAnimation.TabIndex = 11
        Me.btnNoAnimation.Tag = "0"
        Me.btnNoAnimation.Text = "Animaition Off"
        '
        'gbInstant
        '
        Me.gbInstant.Controls.Add(Me.Label13)
        Me.gbInstant.Controls.Add(Me.txtNumber)
        Me.gbInstant.Controls.Add(Me.Label12)
        Me.gbInstant.Controls.Add(Me.Label11)
        Me.gbInstant.Controls.Add(Me.Label10)
        Me.gbInstant.Controls.Add(Me.Label9)
        Me.gbInstant.Controls.Add(Me.txtPotential)
        Me.gbInstant.Controls.Add(Me.txtEnergy)
        Me.gbInstant.Controls.Add(Me.txtTemp)
        Me.gbInstant.Controls.Add(Me.txtStep)
        Me.gbInstant.Enabled = False
        Me.gbInstant.Location = New System.Drawing.Point(8, 158)
        Me.gbInstant.Name = "gbInstant"
        Me.gbInstant.Size = New System.Drawing.Size(256, 224)
        Me.gbInstant.TabIndex = 9
        Me.gbInstant.TabStop = False
        Me.gbInstant.Text = "Instantaneous Parameter"
        '
        'Label13
        '
        Me.Label13.Location = New System.Drawing.Point(8, 184)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(88, 24)
        Me.Label13.TabIndex = 18
        Me.Label13.Text = "No of Particle"
        '
        'txtNumber
        '
        Me.txtNumber.Location = New System.Drawing.Point(104, 184)
        Me.txtNumber.Name = "txtNumber"
        Me.txtNumber.Size = New System.Drawing.Size(128, 20)
        Me.txtNumber.TabIndex = 17
        Me.txtNumber.Text = ""
        '
        'Label12
        '
        Me.Label12.Location = New System.Drawing.Point(8, 152)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(64, 24)
        Me.Label12.TabIndex = 16
        Me.Label12.Text = "Potential"
        '
        'Label11
        '
        Me.Label11.Location = New System.Drawing.Point(8, 112)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(80, 24)
        Me.Label11.TabIndex = 15
        Me.Label11.Text = "Total Energy"
        '
        'Label10
        '
        Me.Label10.Location = New System.Drawing.Point(8, 72)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(72, 24)
        Me.Label10.TabIndex = 14
        Me.Label10.Text = "Temperature"
        '
        'Label9
        '
        Me.Label9.Location = New System.Drawing.Point(8, 40)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(64, 24)
        Me.Label9.TabIndex = 13
        Me.Label9.Text = "Step"
        '
        'txtPotential
        '
        Me.txtPotential.Location = New System.Drawing.Point(104, 149)
        Me.txtPotential.Name = "txtPotential"
        Me.txtPotential.Size = New System.Drawing.Size(128, 20)
        Me.txtPotential.TabIndex = 12
        Me.txtPotential.Text = ""
        '
        'txtEnergy
        '
        Me.txtEnergy.Location = New System.Drawing.Point(104, 110)
        Me.txtEnergy.Name = "txtEnergy"
        Me.txtEnergy.Size = New System.Drawing.Size(128, 20)
        Me.txtEnergy.TabIndex = 11
        Me.txtEnergy.Text = ""
        '
        'txtTemp
        '
        Me.txtTemp.Location = New System.Drawing.Point(104, 72)
        Me.txtTemp.Name = "txtTemp"
        Me.txtTemp.Size = New System.Drawing.Size(128, 20)
        Me.txtTemp.TabIndex = 10
        Me.txtTemp.Text = ""
        '
        'txtStep
        '
        Me.txtStep.Location = New System.Drawing.Point(104, 38)
        Me.txtStep.Name = "txtStep"
        Me.txtStep.Size = New System.Drawing.Size(128, 20)
        Me.txtStep.TabIndex = 9
        Me.txtStep.Text = ""
        '
        'Timer1
        '
        Me.Timer1.Interval = 10
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.rbRetain)
        Me.GroupBox1.Controls.Add(Me.rbImmediate)
        Me.GroupBox1.Location = New System.Drawing.Point(9, 20)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(135, 120)
        Me.GroupBox1.TabIndex = 12
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Visualization Mode"
        '
        'rbRetain
        '
        Me.rbRetain.Location = New System.Drawing.Point(10, 72)
        Me.rbRetain.Name = "rbRetain"
        Me.rbRetain.Size = New System.Drawing.Size(112, 24)
        Me.rbRetain.TabIndex = 1
        Me.rbRetain.Text = "Retained Mode"
        '
        'rbImmediate
        '
        Me.rbImmediate.Location = New System.Drawing.Point(10, 32)
        Me.rbImmediate.Name = "rbImmediate"
        Me.rbImmediate.Size = New System.Drawing.Size(112, 24)
        Me.rbImmediate.TabIndex = 0
        Me.rbImmediate.Text = "Immediate Mode"
        '
        'btnRunMain
        '
        Me.btnRunMain.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnRunMain.Location = New System.Drawing.Point(72, 400)
        Me.btnRunMain.Name = "btnRunMain"
        Me.btnRunMain.Size = New System.Drawing.Size(90, 25)
        Me.btnRunMain.TabIndex = 13
        Me.btnRunMain.Text = "Run"
        '
        'hp
        '
        Me.hp.HelpNamespace = "Nano RV.chm"
        '
        'Demo
        '
        Me.Demo.StartInfo.FileName = "VBC60DLL.exe"
        Me.Demo.SynchronizingObject = Me
        '
        'btnCancelMain
        '
        Me.btnCancelMain.Enabled = False
        Me.btnCancelMain.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnCancelMain.Location = New System.Drawing.Point(173, 400)
        Me.btnCancelMain.Name = "btnCancelMain"
        Me.btnCancelMain.Size = New System.Drawing.Size(90, 25)
        Me.btnCancelMain.TabIndex = 14
        Me.btnCancelMain.Tag = "0"
        Me.btnCancelMain.Text = "Cancel"
        '
        'Timer2
        '
        Me.Timer2.Interval = 1000
        '
        'MainForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(272, 445)
        Me.Controls.Add(Me.btnCancelMain)
        Me.Controls.Add(Me.btnRunMain)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.gbInstant)
        Me.Controls.Add(Me.GroupBox7)
        Me.Location = New System.Drawing.Point(20, 100)
        Me.Menu = Me.MainMenu1
        Me.Name = "MainForm"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Nano RV"
        Me.GroupBox7.ResumeLayout(False)
        Me.gbInstant.ResumeLayout(False)
        Me.GroupBox1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Declare Function GraphRun Lib "Visualize.dll" (ByVal XCoordinate() As Double, ByVal YCoordinate() _
            As Double, ByVal ZCoordinate() As Double, ByVal Red() As Integer, ByVal Green() As Integer, _
            ByVal Blue() As Integer, ByVal Radial() As Double, ByVal NoParticle As Integer, _
            ByVal InstantString As String) As Integer



    'Private Declare Function GraphRun Lib "Visualize.dll" (ByVal XCoordinate() As Double, ByVal YCoordinate() _
    '    As Double, ByVal ZCoordinate() As Double, ByVal Red() As Integer, ByVal Green() As Integer, _
    '    ByVal Blue() As Integer, ByVal Radial() As Double, ByVal NoParticle As Integer, _
    '    ByVal InstantString As String, ByVal XCamera As Single, ByVal YCamera As Single, _
    '    ByVal ZCamera As Single) As Integer

    Private Declare Function EndDll Lib "Visualize.dll" (ByVal NoParticle As Integer) As Integer
    Private Declare Function View Lib "Visualize.dll" () As Integer
    Private Declare Sub Simulation Lib "Simulation.dll" (ByRef NMD As Integer, ByRef ITN As Integer, _
        ByRef NALL As Integer, ByRef SAMPELING As Integer, ByRef TEMPF As Double, ByRef ENERGYF As Double, _
        ByRef POTENTIALF As Double, ByVal RXF() As Double, ByVal RYF() As Double, ByVal RZF() As Double, ByVal IPF() As Integer)

    Private Sub MainForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        'to show Mycomputer for DataFile path
        Me.Text += " - " & FileNm
        Call View()
        frmControls.Show()
    End Sub

    Private Sub RunDllSimulation()
        Dim No As Integer
        Dim Red(), Green(), Blue() As Integer
        Dim Radial() As Double
        Dim kk, i, j, k As Integer
       
        Dim X(), Y(), Z() As Double
        Dim Ip() As Integer
        Dim StepNumber, ParticleNumber, TotalIteration As Int64
        Dim Temp, Energy, Potential As Single
        Dim InstantString As String
        Dim Jump As Integer
        Dim msg As Message

        TotalIteration = frmProperty.nudIteration.Value
        ParticleNumber = frmProperty.nudNoParticle.Value
        Jump = CInt(frmImmedaite.nudJump.Value)

        No = ParticleNumber
        ReDim Red(No), Green(No), Blue(No), Radial(No), X(No), Y(No), Z(No), Ip(No)

        Try
            For StepNumber = 0 To TotalIteration \ Jump

                'Dim Itr As Integer
                'For Itr = 1 To Jump
                Call Simulation(TotalIteration, StepNumber * Jump + 1, ParticleNumber, Jump, Temp, Energy, Potential, X, Y, Z, Ip)
                'Next

                For kk = 0 To ParticleNumber - 1
                    Red(kk) = AtomRed(Ip(kk))
                    Green(kk) = AtomGreen(Ip(kk))
                    Blue(kk) = AtomBlue(Ip(kk))
                    Radial(kk) = AtomRadial(Ip(kk))

                    X(kk) = X(kk) * 7 / (frmProperty.nudX.Value + 0.001)
                    Y(kk) = Y(kk) * 7 / (frmProperty.nudY.Value + 0.001)
                    Z(kk) = Z(kk) * 5.5 / (frmProperty.nudZ.Value + 0.001)
                Next

                If btnCancelMain.Tag = 0 Then
                    If btnNoAnimation.Tag = 0 Then
                        InstantString = "Step Number: " & (StepNumber * Jump + 1).ToString & vbCrLf & "Temperature (°K): " & Temp.ToString & _
                                           vbCrLf & "Total Energy (eV): " & Energy.ToString & vbCrLf & "Potential (eV): " & Potential.ToString & _
                                           vbCrLf & "particles Number: " & ParticleNumber.ToString
                        'Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, ParticleNumber, InstantString, Xcam, Ycam, Zcam)
                        Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, ParticleNumber, InstantString)
                    Else
                        txtStep.Text = StepNumber.ToString
                        txtTemp.Text = Temp.ToString
                        txtEnergy.Text = Energy.ToString
                        txtPotential.Text = Potential.ToString
                        txtNumber.Text = ParticleNumber.ToString.Trim
                        Me.Update()
                        'Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, 0, InstantString, Xcam, Ycam, Zcam)
                        Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, 0, InstantString)
                    End If

                Else
                    btnCancelMain.Tag = 0
                    Exit For

                End If


            Next
        Catch ex As Exception
            MsgBox(ex.ToString)

        End Try
        
        btnRunMain.Enabled = True
        btnCancelMain.Enabled = False

    End Sub

    Private Sub RunFromFile()
        Dim No As Integer
        Dim Red(), Green(), Blue() As Integer
        Dim Radial() As Double
        Dim i, j, k As Integer
       
        'Dim NumS, NumM As Integer

        Dim X(), Y(), Z() As Double
        Dim Ip() As Integer

        Dim s As String
        Dim Data(4) As String

        Dim StepNumber, ParticleNumber As Int64
        Dim Temp, Energy, Potential As Single
        Dim InstantString As String

        Dim fsr As System.IO.FileStream = New System.IO.FileStream(frmRetained.txtSelectPath.Text, FileMode.Open, FileAccess.Read, FileShare.ReadWrite)
            Dim LineStream As New StreamReader(fsr)
            Dim LineString As String
            Dim ii, jj, kk As Integer
            Dim Continue As Boolean = True

            kk = 0

            Try
                LineString = LineStream.ReadLine()

            If LineString <> Nothing Then
                '              If frmControls.btnControlPuse.Tag = 0 Then
                Do While LineString <> Nothing
                    StepNumber = CInt(LineString)
                    LineString = LineStream.ReadLine()

                    Temp = Round(CSng(LineString), 4)
                    LineString = LineStream.ReadLine()

                    Energy = Round(CSng(LineString), 4)
                    LineString = LineStream.ReadLine()

                    Potential = Round(CSng(LineString), 4)
                    LineString = LineStream.ReadLine()


                    ParticleNumber = CInt(LineString)
                    No = ParticleNumber

                    ReDim Red(No), Green(No), Blue(No), Radial(No), X(No), Y(No), Z(No), Ip(No)

                    For kk = 0 To ParticleNumber - 1 'Zero base thus ParticleNumber-1
                        LineString = LineStream.ReadLine()

                        ii = 0
                        jj = 0
                        LineString = Trim(LineString)
                        ii = LineString.IndexOf(" ", 0)
                        Do While ii > 0
                            Data(jj) = LineString.Substring(0, ii)
                            LineString = LineString.Remove(0, ii)
                            LineString = LineString.Trim(LineString)
                            ii = LineString.IndexOf(" ", 0)
                            jj += 1
                        Loop
                        Data(jj) = LineString


                        X(kk) = CDbl(Data(0) * 7 / (frmProperty.nudX.Value + 0.001))
                        Y(kk) = CDbl(Data(1) * 7 / (frmProperty.nudY.Value + 0.001))
                        Z(kk) = CDbl(Data(2) * 5.5 / (frmProperty.nudZ.Value + 0.001))
                        Ip(kk) = CDbl(Data(3))

                        Red(kk) = AtomRed(Ip(kk))
                        Green(kk) = AtomGreen(Ip(kk))
                        Blue(kk) = AtomBlue(Ip(kk))
                        Radial(kk) = AtomRadial(Ip(kk))
                    Next

                    If btnCancelMain.Tag = 0 Then
                        If btnNoAnimation.Tag = 0 Then
                            InstantString = "Step Number: " & StepNumber.ToString & vbCrLf & "Temperature (°K): " & Temp.ToString & _
                                               vbCrLf & "Total Energy (eV): " & Energy.ToString & vbCrLf & "Potential (eV): " & Potential.ToString & _
                                               vbCrLf & "particles Number: " & ParticleNumber.ToString
                            'Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, ParticleNumber, InstantString, Xcam, Ycam, Zcam)
                            Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, ParticleNumber, InstantString)
                        Else
                            txtStep.Text = StepNumber.ToString
                            txtTemp.Text = Temp.ToString
                            txtEnergy.Text = Energy.ToString
                            txtPotential.Text = Potential.ToString
                            txtNumber.Text = ParticleNumber.ToString.Trim
                            Me.Update()
                            'Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, 0, InstantString, Xcam, Ycam, Zcam)
                            Call GraphRun(X, Y, Z, Red, Green, Blue, Radial, 0, InstantString)
                        End If 'btnNoAnimation
                        LineString = LineStream.ReadLine()

                    Else
                        btnCancelMain.Tag = 0
                        Exit Do

                    End If 'btnCancelMain

                Loop
                '           Else
                '               Timer2.Enabled = True
                '          End If 'btnControlPuse
            End If 'LineString


        Catch When Err.Number = 9
            MsgBox("Number of particles is less than number of particles that there is in file.")

        Catch ex As Exception
            MsgBox(ex.ToString + vbCrLf + Err.Number.ToString + vbCrLf + Err.Description + vbCrLf + "SN:" + StepNumber.ToString)

        Finally
            fsr.Close()
        End Try
        btnRunMain.Enabled = True
        btnCancelMain.Enabled = False

    End Sub

    Private Sub mnuFileSaveAs_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFileSaveAs.Click
        Dim srWriter As StreamWriter
        Dim str As String
        Dim i As Integer = 0
        sfdFileSaveAs.Filter = "NRV file|*.nrv"
        sfdFileSaveAs.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal)
        Do
            i += 1
        Loop While File.Exists(sfdFileSaveAs.InitialDirectory + "\" + FileNm + i.ToString + ".nrv")
        sfdFileSaveAs.FileName = FileNm & i.ToString

        If sfdFileSaveAs.ShowDialog() = DialogResult.OK Then
            FilePth = sfdFileSaveAs.FileName
            srWriter = New StreamWriter(FilePth)

            str = frmProperty.chkLennard_Jones.Checked.ToString + vbCrLf
            str += frmProperty.chkMorse.Checked.ToString + vbCrLf
            str += frmProperty.chkMorse.Checked.ToString + vbCrLf
            str += frmProperty.chkTersoff_Bernner.Checked.ToString + vbCrLf

            str += frmProperty.chkNVT.Checked.ToString + vbCrLf
            str += frmProperty.chkNPT.Checked.ToString + vbCrLf
            str += frmProperty.chkMVT.Checked.ToString + vbCrLf

            str += frmProperty.nudNoParticle.Value.ToString + vbCrLf
            str += frmProperty.nudIteration.Value.ToString + vbCrLf

            str += frmProperty.nudX.Value.ToString + vbCrLf
            str += frmProperty.nudY.Value.ToString + vbCrLf
            str += frmProperty.nudZ.Value.ToString + vbCrLf

            str += frmRetained.txtSelectPath.Text + vbCrLf

            srWriter.Write(str)
            srWriter.Close()
            Me.Text = "Nano RV - " & System.IO.Path.GetFileNameWithoutExtension(FilePth)

        End If

    End Sub

    Private Sub mnuFileOpen_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFileOpen.Click
        Dim Strm As StreamReader
        Dim Strng As String

        ofdFileOpen.Filter = "NRV file (*.nrv)|*.nrv"
        If ofdFileOpen.ShowDialog = DialogResult.OK Then
            FilePth = ofdFileOpen.FileName
            Strm = New StreamReader(FilePth)
            Strng = Strm.ReadLine
            frmProperty.chkLennard_Jones.Checked = Strng
            Strng = Strm.ReadLine
            frmProperty.chkMorse.Checked = Strng
            Strng = Strm.ReadLine
            frmProperty.chkMorse.Checked = Strng
            Strng = Strm.ReadLine
            frmProperty.chkTersoff_Bernner.Checked = Strng

            Strng = Strm.ReadLine
            frmProperty.chkNVT.Checked = Strng
            Strng = Strm.ReadLine
            frmProperty.chkNPT.Checked = Strng
            Strng = Strm.ReadLine
            frmProperty.chkMVT.Checked = Strng

            Strng = Strm.ReadLine
            frmProperty.nudNoParticle.Value = Strng
            Strng = Strm.ReadLine
            frmProperty.nudIteration.Value = Strng


            Strng = Strm.ReadLine
            frmProperty.nudX.Value = Strng
            Strng = Strm.ReadLine
            frmProperty.nudY.Value = Strng
            Strng = Strm.ReadLine
            frmProperty.nudZ.Value = Strng

            Strng = Strm.ReadLine
            frmRetained.txtSelectPath.Text = Strng

            Strm.Close()
            Me.Text = "Nano RV - " & System.IO.Path.GetFileNameWithoutExtension(FilePth)
            frmProperty.txtVolume.Text = Round((frmProperty.nudX.Value * frmProperty.nudY.Value * frmProperty.nudZ.Value), 2).ToString

        End If

    End Sub

    Private Sub mnuFileSave_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFileSave.Click
        Dim srWriter As StreamWriter
        Dim str As String

        If File.Exists(FilePth) Then
            srWriter = New StreamWriter(FilePth)
            str = frmProperty.chkLennard_Jones.Checked.ToString + vbCrLf
            str += frmProperty.chkMorse.Checked.ToString + vbCrLf
            str += frmProperty.chkMorse.Checked.ToString + vbCrLf
            str += frmProperty.chkTersoff_Bernner.Checked.ToString + vbCrLf

            str += frmProperty.chkNVT.Checked.ToString + vbCrLf
            str += frmProperty.chkNPT.Checked.ToString + vbCrLf
            str += frmProperty.chkMVT.Checked.ToString + vbCrLf

            str += frmProperty.nudNoParticle.Value.ToString + vbCrLf
            str += frmProperty.nudIteration.Value.ToString + vbCrLf


            str += frmProperty.nudX.Value.ToString + vbCrLf
            str += frmProperty.nudY.Value.ToString + vbCrLf
            str += frmProperty.nudZ.Value.ToString + vbCrLf

            str += frmRetained.txtSelectPath.Text + vbCrLf

            srWriter.Write(str)
            srWriter.Close()
        Else
            mnuFileSaveAs_Click(sender, e)
        End If
    End Sub

    Private Sub mnuFileNew_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFileNew.Click

        frmProperty.chkLennard_Jones.Checked = False
        frmProperty.chkMorse.Checked = False
        frmProperty.chkMorse.Checked() = False
        frmProperty.chkTersoff_Bernner.Checked() = False

        frmProperty.chkNVT.Checked = False
        frmProperty.chkNPT.Checked = False

        frmProperty.chkMVT.Checked = False

        frmProperty.nudNoParticle.Value = 1
        frmProperty.nudIteration.Value = 1

        frmProperty.nudX.Value = 0
        frmProperty.nudY.Value = 0
        frmProperty.nudZ.Value = 0

        frmRetained.txtSelectPath.Text = Nothing
        FilePth = Nothing
        Me.Text = "Nano RV - " & "Nano"
    End Sub

    Private Sub mnuFileClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFileClose.Click
        Dim MsgRsult As Integer
        MsgRsult = MsgBox("Do you want save file?", MsgBoxStyle.YesNoCancel)
        If MsgRsult = DialogResult.Yes Then
            mnuFileSave_Click(sender, e)
            mnuFileNew_Click(sender, e)
        ElseIf MsgRsult = DialogResult.No Then
            mnuFileNew_Click(sender, e)
        End If

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Timer1.Enabled = False
    End Sub


    Private Sub btnRunMain_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRunMain.Click
        If rbImmediate.Checked = False And rbRetain.Checked = False Then
            MsgBox("Please Chech one mode Immediate or Retain.")
            Return
        End If
        
        If rbImmediate.Checked = True Then
            frmProperty.gbInitial.Enabled = True
            btnRunMain.Enabled = False
            btnCancelMain.Enabled = True
            frmProperty.ShowDialog()
            If frmProperty.DialogResult = DialogResult.Cancel Then
                btnRunMain.Enabled = True
                btnCancelMain.Enabled = False
                Return
            End If
            frmImmedaite.ShowDialog()
            If frmImmedaite.DialogResult = DialogResult.Cancel Then
                btnRunMain.Enabled = True
                btnCancelMain.Enabled = False
                Return
            End If
            RunDllSimulation()
        Else
            frmProperty.gbInitial.Enabled = False
            btnRunMain.Enabled = False
            btnCancelMain.Enabled = True
            frmProperty.ShowDialog()
            If frmProperty.DialogResult = DialogResult.Cancel Then
                btnRunMain.Enabled = True
                btnCancelMain.Enabled = False
                Return
            End If
            frmRetained.ShowDialog()
            If frmRetained.DialogResult = DialogResult.Cancel Then
                btnRunMain.Enabled = True
                btnCancelMain.Enabled = False
                Return
            End If
            RunFromFile()
        End If
    End Sub


    Private Sub btnNoAnimation_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnNoAnimation.Click
        If btnNoAnimation.Tag = 0 Then
            btnNoAnimation.Tag = 1
            btnNoAnimation.Text = "Animaition On"
            gbInstant.Enabled = True
        Else
            btnNoAnimation.Tag = 0
            btnNoAnimation.Text = "Animaition Off"
            gbInstant.Enabled = False
        End If
    End Sub

    Private Sub mnuFileExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuFileExit.Click
        Call EndDll(1000)
        End
    End Sub

    Private Sub MainForm_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
        Call EndDll(1000)
        End
    End Sub

    Private Sub mnuHelpAbout_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuHelpAbout.Click
        Dim frmSplash As New Splash
        frmSplash.ShowDialog()
    End Sub

    
    Private Sub mnuHelpContent_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuHelpContent.Click
        Help.ShowHelp(Me, Me.hp.HelpNamespace)
    End Sub

    Private Sub mnuHelpIndex_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuHelpIndex.Click
        Help.ShowHelpIndex(Me, Me.hp.HelpNamespace)
    End Sub

    Private Sub mnuHelpSearch_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuHelpSearch.Click
        Help.ShowHelp(Me, Me.hp.HelpNamespace, HelpNavigator.Find, "")
    End Sub

    Private Sub mnuDemoC60_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuDemoC60.Click
        Demo.StartInfo.FileName = "VBC60DLL.exe"
        Demo.Start()
    End Sub

    Private Sub mnuDemoBox_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuDemoBox.Click
        Demo.StartInfo.FileName = "RotateCub.exe"
        Demo.Start()
    End Sub

    Private Sub mnuDemoMolecule_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuDemoMolecule.Click
        Demo.StartInfo.FileName = "Molecule.exe"
        Demo.Start()
    End Sub

    Private Sub mnuDemoSphere_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuDemoSphere.Click
        Demo.StartInfo.FileName = "Sphere.exe"
        Demo.Start()
    End Sub

    Private Sub btnCancelMain_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCancelMain.Click
        btnCancelMain.Tag = 1
    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        Timer2.Enabled = False
        End
    End Sub
End Class
