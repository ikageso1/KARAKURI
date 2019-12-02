Public Class Form1
    '0～8まで、要素数は 9個になります。
    Dim ClickCount(12, 16) As Integer

    Dim BlockImage As Image = Image.FromFile("Source/Block.png")
    Dim TutiImage As Image = Image.FromFile("Source/Tuti.png")
    Dim NoneImage As Image = Image.FromFile("Source/none.png")

    'ロード時の初期化
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        For i = 0 To 7
            For j = 0 To 11
                ClickCount(i, j) = 0
            Next
        Next
    End Sub

    '出力ボタンのクリック
    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        FileExport()
        MsgBox("保存しました")
    End Sub

    '読み込みボタンのクリック
    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        FileImport()
        MsgBox("ロードしました")
    End Sub

    'ファイル出力
    Private Sub FileExport()
        Dim textFile As System.IO.StreamWriter
        textFile = New System.IO.StreamWriter("editmap.csv")
        For i = 1 To 12
            For j = 1 To 16
                textFile.Write(ClickCount(i, j))    'ファイルの書き込み
                If (j < 16) Then
                    textFile.Write(" ") 'ファイルの「 」の追加
                End If
            Next
            textFile.WriteLine()
        Next
        textFile.Close()
    End Sub

    'ファイル入力
    Private Sub FileImport()

        Dim Reader As New IO.StreamReader("editmap.csv", System.Text.Encoding.GetEncoding("Shift-JIS"))
        Dim Items() As String                'CSVの各項目を表す配列
        Dim Line As String = Reader.ReadLine 'CSVの一行

        For i = 1 To 12
            Items = Line.Split(" ")          '一行を (空白)で区切って項目ごとに分解
            For j = 1 To 16
                ClickCount(i, j) = Integer.Parse(Items(j - 1))
            Next
            Line = Reader.ReadLine                    '次の行を読み込む
        Next
        Reader.Close()
        PictureUpdate()
    End Sub

    '全てのpictureコントロールの画像の状態を更新
    Private Sub PictureUpdate()
        PictureShow(1, 1, PictureBox1)
        PictureShow(1, 2, PictureBox2)   
        PictureShow(1, 3, PictureBox3)
        PictureShow(1, 4, PictureBox4)    
        PictureShow(1, 5, PictureBox42)
        PictureShow(1, 6, PictureBox41)   
        PictureShow(1, 7, PictureBox40)  
        PictureShow(1, 8, PictureBox84)    
        PictureShow(1, 9, PictureBox83)    
        PictureShow(1, 10, PictureBox82)    
        PictureShow(1, 11, PictureBox81)    
        PictureShow(1, 12, PictureBox60)
        PictureShow(1, 13, PictureBox120)
        PictureShow(1, 14, PictureBox119)
        PictureShow(1, 15, PictureBox108)
        PictureShow(1, 16, PictureBox128)
        PictureShow(2, 1, PictureBox5)
        PictureShow(2, 2, PictureBox6)
        PictureShow(2, 3, PictureBox22)
        PictureShow(2, 4, PictureBox21)
        PictureShow(2, 5, PictureBox39)
        PictureShow(2, 6, PictureBox30)
        PictureShow(2, 7, PictureBox29)
        PictureShow(2, 8, PictureBox80)
        PictureShow(2, 9, PictureBox79)
        PictureShow(2, 10, PictureBox66)
        PictureShow(2, 11, PictureBox65)
        PictureShow(2, 12, PictureBox57)
        PictureShow(2, 13, PictureBox114)
        PictureShow(2, 14, PictureBox113)
        PictureShow(2, 15, PictureBox107)
        PictureShow(2, 16, PictureBox127)
        PictureShow(3, 1, PictureBox12)
        PictureShow(3, 2, PictureBox11)
        PictureShow(3, 3, PictureBox10) 
        PictureShow(3, 4, PictureBox9) 
        PictureShow(3, 5, PictureBox38)  
        PictureShow(3, 6, PictureBox37)   
        PictureShow(3, 7, PictureBox36)  
        PictureShow(3, 8, PictureBox78)  
        PictureShow(3, 9, PictureBox77)  
        PictureShow(3, 10, PictureBox76)   
        PictureShow(3, 11, PictureBox75)   
        PictureShow(3, 12, PictureBox56)
        PictureShow(3, 13, PictureBox118)
        PictureShow(3, 14, PictureBox117)
        PictureShow(3, 15, PictureBox106)
        PictureShow(3, 16, PictureBox126)
        PictureShow(4, 1, PictureBox8)
        PictureShow(4, 2, PictureBox7)
        PictureShow(4, 3, PictureBox20)   
        PictureShow(4, 4, PictureBox19)  
        PictureShow(4, 5, PictureBox35)  
        PictureShow(4, 6, PictureBox28) 
        PictureShow(4, 7, PictureBox27)  
        PictureShow(4, 8, PictureBox74)   
        PictureShow(4, 9, PictureBox73)
        PictureShow(4, 10, PictureBox64)
        PictureShow(4, 11, PictureBox63)
        PictureShow(4, 12, PictureBox53)
        PictureShow(4, 13, PictureBox112)
        PictureShow(4, 14, PictureBox111)
        PictureShow(4, 15, PictureBox105)
        PictureShow(4, 16, PictureBox125)
        PictureShow(5, 1, PictureBox18)
        PictureShow(5, 2, PictureBox17)
        PictureShow(5, 3, PictureBox16)
        PictureShow(5, 4, PictureBox15)
        PictureShow(5, 5, PictureBox34)
        PictureShow(5, 6, PictureBox33)
        PictureShow(5, 7, PictureBox32)
        PictureShow(5, 8, PictureBox72)
        PictureShow(5, 9, PictureBox71)
        PictureShow(5, 10, PictureBox70)
        PictureShow(5, 11, PictureBox69)
        PictureShow(5, 12, PictureBox52)
        PictureShow(5, 13, PictureBox116)
        PictureShow(5, 14, PictureBox115)
        PictureShow(5, 15, PictureBox104)
        PictureShow(5, 16, PictureBox124)
        PictureShow(6, 1, PictureBox14)
        PictureShow(6, 2, PictureBox13)
        PictureShow(6, 3, PictureBox24)
        PictureShow(6, 4, PictureBox23)
        PictureShow(6, 5, PictureBox31)
        PictureShow(6, 6, PictureBox26)
        PictureShow(6, 7, PictureBox25)
        PictureShow(6, 8, PictureBox68)
        PictureShow(6, 9, PictureBox67)
        PictureShow(6, 10, PictureBox62)
        PictureShow(6, 11, PictureBox61)
        PictureShow(6, 12, PictureBox49)
        PictureShow(6, 13, PictureBox110)
        PictureShow(6, 14, PictureBox109)
        PictureShow(6, 15, PictureBox103)
        PictureShow(6, 16, PictureBox123)
        PictureShow(7, 1, PictureBox96)
        PictureShow(7, 2, PictureBox95)
        PictureShow(7, 3, PictureBox94)
        PictureShow(7, 4, PictureBox93)
        PictureShow(7, 5, PictureBox88)
        PictureShow(7, 6, PictureBox87)
        PictureShow(7, 7, PictureBox86)
        PictureShow(7, 8, PictureBox55)
        PictureShow(7, 9, PictureBox54)
        PictureShow(7, 10, PictureBox51)
        PictureShow(7, 11, PictureBox50)
        PictureShow(7, 12, PictureBox44)
        PictureShow(7, 13, PictureBox102)
        PictureShow(7, 14, PictureBox101)
        PictureShow(7, 15, PictureBox98)
        PictureShow(7, 16, PictureBox122)
        PictureShow(8, 1, PictureBox92)
        PictureShow(8, 2, PictureBox91)
        PictureShow(8, 3, PictureBox90)
        PictureShow(8, 4, PictureBox89)
        PictureShow(8, 5, PictureBox85)
        PictureShow(8, 6, PictureBox59)
        PictureShow(8, 7, PictureBox58)
        PictureShow(8, 8, PictureBox48)
        PictureShow(8, 9, PictureBox47)
        PictureShow(8, 10, PictureBox46)   
        PictureShow(8, 11, PictureBox45)
        PictureShow(8, 12, PictureBox43)
        PictureShow(8, 13, PictureBox100)
        PictureShow(8, 14, PictureBox99)
        PictureShow(8, 15, PictureBox97)
        PictureShow(8, 16, PictureBox121)
        PictureShow(9, 1, PictureBox192)
        PictureShow(9, 2, PictureBox191)
        PictureShow(9, 3, PictureBox190)
        PictureShow(9, 4, PictureBox189)
        PictureShow(9, 5, PictureBox184)
        PictureShow(9, 6, PictureBox183)
        PictureShow(9, 7, PictureBox182)
        PictureShow(9, 8, PictureBox178)
        PictureShow(9, 9, PictureBox177)
        PictureShow(9, 10, PictureBox176)
        PictureShow(9, 11, PictureBox175)
        PictureShow(9, 12, PictureBox170)
        PictureShow(9, 13, PictureBox144)
        PictureShow(9, 14, PictureBox143)
        PictureShow(9, 15, PictureBox140)
        PictureShow(9, 16, PictureBox132)
        PictureShow(10, 1, PictureBox188)
        PictureShow(10, 2, PictureBox187)
        PictureShow(10, 3, PictureBox186)
        PictureShow(10, 4, PictureBox185)
        PictureShow(10, 5, PictureBox181)
        PictureShow(10, 6, PictureBox180)
        PictureShow(10, 7, PictureBox179)
        PictureShow(10, 8, PictureBox174)
        PictureShow(10, 9, PictureBox173)
        PictureShow(10, 10, PictureBox172)
        PictureShow(10, 11, PictureBox171)
        PictureShow(10, 12, PictureBox169)
        PictureShow(10, 13, PictureBox142)
        PictureShow(10, 14, PictureBox141)
        PictureShow(10, 15, PictureBox139)
        PictureShow(10, 16, PictureBox131)
        PictureShow(11, 1, PictureBox168)
        PictureShow(11, 2, PictureBox167)
        PictureShow(11, 3, PictureBox166)
        PictureShow(11, 4, PictureBox165)
        PictureShow(11, 5, PictureBox160)
        PictureShow(11, 6, PictureBox159)
        PictureShow(11, 7, PictureBox158)
        PictureShow(11, 8, PictureBox154)
        PictureShow(11, 9, PictureBox153)
        PictureShow(11, 10, PictureBox152)
        PictureShow(11, 11, PictureBox151)
        PictureShow(11, 12, PictureBox146)
        PictureShow(11, 13, PictureBox138)
        PictureShow(11, 14, PictureBox137)
        PictureShow(11, 15, PictureBox134)
        PictureShow(11, 16, PictureBox130)
        PictureShow(12, 1, PictureBox164)
        PictureShow(12, 2, PictureBox163)
        PictureShow(12, 3, PictureBox162)
        PictureShow(12, 4, PictureBox161)
        PictureShow(12, 5, PictureBox157)
        PictureShow(12, 6, PictureBox156)
        PictureShow(12, 7, PictureBox155)
        PictureShow(12, 8, PictureBox150)
        PictureShow(12, 9, PictureBox149)
        PictureShow(12, 10, PictureBox148)
        PictureShow(12, 11, PictureBox147)
        PictureShow(12, 12, PictureBox145)
        PictureShow(12, 13, PictureBox136)
        PictureShow(12, 14, PictureBox135)
        PictureShow(12, 15, PictureBox133)
        PictureShow(12, 16, PictureBox129)
    End Sub

    'クリック時のイベント
    Private Sub ClickEvent(ByVal i As Integer, ByVal j As Integer, ByRef Picture As System.Windows.Forms.PictureBox)
        ClickCount(i, j) += 1
        If (ClickCount(i, j) = 3) Then
            ClickCount(i, j) = 0
        End If
        PictureShow(i, j, Picture)
    End Sub

    '表示画像の変更
    Private Sub PictureShow(ByVal i As Integer, ByVal j As Integer, ByRef Picture As System.Windows.Forms.PictureBox)
        Select Case ClickCount(i, j)
            Case 0
                Picture.Image = NoneImage
            Case 1
                Picture.Image = TutiImage
            Case 2
                Picture.Image = BlockImage
        End Select
    End Sub

    '一行目
    Private Sub PictureBox1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox1.Click
        ClickEvent(1, 1, PictureBox1)
    End Sub

    Private Sub PictureBox2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox2.Click
        ClickEvent(1, 2, PictureBox2)
    End Sub

    Private Sub PictureBox3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox3.Click
        ClickEvent(1, 3, PictureBox3)
    End Sub

    Private Sub PictureBox4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox4.Click
        ClickEvent(1, 4, PictureBox4)
    End Sub

    Private Sub PictureBox42_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox42.Click
        ClickEvent(1, 5, PictureBox42)
    End Sub

    Private Sub PictureBox41_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox41.Click
        ClickEvent(1, 6, PictureBox41)
    End Sub

    Private Sub PictureBox40_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox40.Click
        ClickEvent(1, 7, PictureBox40)
    End Sub

    Private Sub PictureBox84_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox84.Click
        ClickEvent(1, 8, PictureBox84)
    End Sub

    Private Sub PictureBox83_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox83.Click
        ClickEvent(1, 9, PictureBox83)
    End Sub

    Private Sub PictureBox82_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox82.Click
        ClickEvent(1, 10, PictureBox82)
    End Sub

    Private Sub PictureBox81_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox81.Click
        ClickEvent(1, 11, PictureBox81)
    End Sub

    Private Sub PictureBox60_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox60.Click
        ClickEvent(1, 12, PictureBox60)
    End Sub

    Private Sub PictureBox120_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox120.Click
        ClickEvent(1, 13, PictureBox120)
    End Sub

    Private Sub PictureBox119_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox119.Click
        ClickEvent(1, 14, PictureBox119)
    End Sub

    Private Sub PictureBox108_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox108.Click
        ClickEvent(1, 15, PictureBox108)
    End Sub

    Private Sub PictureBox128_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox128.Click
        ClickEvent(1, 16, PictureBox128)
    End Sub

    '2行目
    Private Sub PictureBox5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox5.Click
        ClickEvent(2, 1, PictureBox5)
    End Sub

    Private Sub PictureBox6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox6.Click
        ClickEvent(2, 2, PictureBox6)
    End Sub

    Private Sub PictureBox22_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox22.Click
        ClickEvent(2, 3, PictureBox22)
    End Sub

    Private Sub PictureBox21_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox21.Click
        ClickEvent(2, 4, PictureBox21)
    End Sub

    Private Sub PictureBox39_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox39.Click
        ClickEvent(2, 5, PictureBox39)
    End Sub

    Private Sub PictureBox30_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox30.Click
        ClickEvent(2, 6, PictureBox30)
    End Sub

    Private Sub PictureBox29_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox29.Click
        ClickEvent(2, 7, PictureBox29)
    End Sub

    Private Sub PictureBox80_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox80.Click
        ClickEvent(2, 8, PictureBox80)
    End Sub

    Private Sub PictureBox79_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox79.Click
        ClickEvent(2, 9, PictureBox79)
    End Sub

    Private Sub PictureBox66_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox66.Click
        ClickEvent(2, 10, PictureBox66)
    End Sub

    Private Sub PictureBox65_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox65.Click
        ClickEvent(2, 11, PictureBox65)
    End Sub

    Private Sub PictureBox57_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox57.Click
        ClickEvent(2, 12, PictureBox57)
    End Sub

    Private Sub PictureBox114_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox114.Click
        ClickEvent(2, 13, PictureBox114)
    End Sub

    Private Sub PictureBox113_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox113.Click
        ClickEvent(2, 14, PictureBox113)
    End Sub

    Private Sub PictureBox107_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox107.Click
        ClickEvent(2, 15, PictureBox107)
    End Sub

    Private Sub PictureBox127_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox127.Click
        ClickEvent(2, 16, PictureBox127)
    End Sub

    '3行目
    Private Sub PictureBox12_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox12.Click
        ClickEvent(3, 1, PictureBox12)
    End Sub

    Private Sub PictureBox11_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox11.Click
        ClickEvent(3, 2, PictureBox11)
    End Sub

    Private Sub PictureBox10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox10.Click
        ClickEvent(3, 3, PictureBox10)
    End Sub

    Private Sub PictureBox9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox9.Click
        ClickEvent(3, 4, PictureBox9)
    End Sub

    Private Sub PictureBox38_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox38.Click
        ClickEvent(3, 5, PictureBox38)
    End Sub

    Private Sub PictureBox37_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox37.Click
        ClickEvent(3, 6, PictureBox37)
    End Sub

    Private Sub PictureBox36_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PictureBox36.Click
        ClickEvent(3, 7, PictureBox36)
    End Sub

    Private Sub PictureBox78_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox78.Click
        ClickEvent(3, 8, PictureBox78)
    End Sub

    Private Sub PictureBox77_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox77.Click
        ClickEvent(3, 9, PictureBox77)
    End Sub

    Private Sub PictureBox76_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox76.Click
        ClickEvent(3, 10, PictureBox76)
    End Sub

    Private Sub PictureBox75_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox75.Click
        ClickEvent(3, 11, PictureBox75)
    End Sub

    Private Sub PictureBox56_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox56.Click
        ClickEvent(3, 12, PictureBox56)
    End Sub

    Private Sub PictureBox118_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox118.Click
        ClickEvent(3, 13, PictureBox118)
    End Sub

    Private Sub PictureBox117_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox117.Click
        ClickEvent(3, 14, PictureBox117)
    End Sub

    Private Sub PictureBox106_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox106.Click
        ClickEvent(3, 15, PictureBox106)
    End Sub

    Private Sub PictureBox126_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox126.Click
        ClickEvent(3, 16, PictureBox126)
    End Sub
    '4行目
    Private Sub PictureBox8_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox8.Click
        ClickEvent(4, 1, PictureBox8)
    End Sub

    Private Sub PictureBox7_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox7.Click
        ClickEvent(4, 2, PictureBox7)
    End Sub

    Private Sub PictureBox20_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox20.Click
        ClickEvent(4, 3, PictureBox20)
    End Sub

    Private Sub PictureBox19_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox19.Click
        ClickEvent(4, 4, PictureBox19)
    End Sub

    Private Sub PictureBox35_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox35.Click
        ClickEvent(4, 5, PictureBox35)
    End Sub

    Private Sub PictureBox28_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox28.Click
        ClickEvent(4, 6, PictureBox28)
    End Sub

    Private Sub PictureBox27_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox27.Click
        ClickEvent(4, 7, PictureBox27)
    End Sub

    Private Sub PictureBox74_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox74.Click
        ClickEvent(4, 8, PictureBox74)
    End Sub

    Private Sub PictureBox73_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox73.Click
        ClickEvent(4, 9, PictureBox73)
    End Sub

    Private Sub PictureBox64_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox64.Click
        ClickEvent(4, 10, PictureBox64)
    End Sub

    Private Sub PictureBox63_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox63.Click
        ClickEvent(4, 11, PictureBox63)
    End Sub

    Private Sub PictureBox53_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox53.Click
        ClickEvent(4, 12, PictureBox53)
    End Sub

    Private Sub PictureBox112_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox112.Click
        ClickEvent(4, 13, PictureBox112)
    End Sub

    Private Sub PictureBox111_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox111.Click
        ClickEvent(4, 14, PictureBox111)
    End Sub

    Private Sub PictureBox105_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox105.Click
        ClickEvent(4, 15, PictureBox105)
    End Sub

    Private Sub PictureBox125_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox125.Click
        ClickEvent(4, 16, PictureBox125)
    End Sub

    '5行目
    Private Sub PictureBox18_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox18.Click
        ClickEvent(5, 1, PictureBox18)
    End Sub

    Private Sub PictureBox17_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox17.Click
        ClickEvent(5, 2, PictureBox17)
    End Sub

    Private Sub PictureBox16_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox16.Click
        ClickEvent(5, 3, PictureBox16)
    End Sub

    Private Sub PictureBox15_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox15.Click
        ClickEvent(5, 4, PictureBox15)
    End Sub

    Private Sub PictureBox34_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox34.Click
        ClickEvent(5, 5, PictureBox34)
    End Sub

    Private Sub PictureBox33_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox33.Click
        ClickEvent(5, 6, PictureBox33)
    End Sub

    Private Sub PictureBox32_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox32.Click
        ClickEvent(5, 7, PictureBox32)
    End Sub

    Private Sub PictureBox72_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox72.Click
        ClickEvent(5, 8, PictureBox72)
    End Sub

    Private Sub PictureBox71_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox71.Click
        ClickEvent(5, 9, PictureBox71)
    End Sub

    Private Sub PictureBox70_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox70.Click
        ClickEvent(5, 10, PictureBox70)
    End Sub

    Private Sub PictureBox69_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox69.Click
        ClickEvent(5, 11, PictureBox69)
    End Sub

    Private Sub PictureBox52_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox52.Click
        ClickEvent(5, 12, PictureBox52)
    End Sub

    Private Sub PictureBox116_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox116.Click
        ClickEvent(5, 13, PictureBox116)
    End Sub

    Private Sub PictureBox115_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox115.Click
        ClickEvent(5, 14, PictureBox115)
    End Sub

    Private Sub PictureBox104_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox104.Click
        ClickEvent(5, 15, PictureBox104)
    End Sub

    Private Sub PictureBox124_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox124.Click
        ClickEvent(5, 16, PictureBox124)
    End Sub
    '6行目
    Private Sub PictureBox14_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox14.Click
        ClickEvent(6, 1, PictureBox14)
    End Sub

    Private Sub PictureBox13_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox13.Click
        ClickEvent(6, 2, PictureBox13)
    End Sub

    Private Sub PictureBox24_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox24.Click
        ClickEvent(6, 3, PictureBox24)
    End Sub

    Private Sub PictureBox23_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox23.Click
        ClickEvent(6, 4, PictureBox23)
    End Sub

    Private Sub PictureBox31_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox31.Click
        ClickEvent(6, 5, PictureBox31)
    End Sub

    Private Sub PictureBox26_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox26.Click
        ClickEvent(6, 6, PictureBox26)
    End Sub

    Private Sub PictureBox25_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox25.Click
        ClickEvent(6, 7, PictureBox25)
    End Sub

    Private Sub PictureBox68_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox68.Click
        ClickEvent(6, 8, PictureBox68)
    End Sub

    Private Sub PictureBox67_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox67.Click
        ClickEvent(6, 9, PictureBox67)
    End Sub

    Private Sub PictureBox62_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox62.Click
        ClickEvent(6, 10, PictureBox62)
    End Sub

    Private Sub PictureBox61_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox61.Click
        ClickEvent(6, 11, PictureBox61)
    End Sub

    Private Sub PictureBox49_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox49.Click
        ClickEvent(6, 12, PictureBox49)
    End Sub

    Private Sub PictureBox110_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox110.Click
        ClickEvent(6, 13, PictureBox110)
    End Sub

    Private Sub PictureBox109_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox109.Click
        ClickEvent(6, 14, PictureBox109)
    End Sub

    Private Sub PictureBox103_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox103.Click
        ClickEvent(6, 15, PictureBox103)
    End Sub

    Private Sub PictureBox123_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox123.Click
        ClickEvent(6, 16, PictureBox123)
    End Sub
    '7行目
    Private Sub PictureBox96_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox96.Click
        ClickEvent(7, 1, PictureBox96)
    End Sub

    Private Sub PictureBox95_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox95.Click
        ClickEvent(7, 2, PictureBox95)
    End Sub

    Private Sub PictureBox94_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox94.Click
        ClickEvent(7, 3, PictureBox94)
    End Sub

    Private Sub PictureBox93_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox93.Click
        ClickEvent(7, 4, PictureBox93)
    End Sub

    Private Sub PictureBox88_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox88.Click
        ClickEvent(7, 5, PictureBox88)
    End Sub

    Private Sub PictureBox87_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox87.Click
        ClickEvent(7, 6, PictureBox87)
    End Sub

    Private Sub PictureBox86_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox86.Click
        ClickEvent(7, 7, PictureBox86)
    End Sub

    Private Sub PictureBox55_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox55.Click
        ClickEvent(7, 8, PictureBox55)
    End Sub

    Private Sub PictureBox54_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox54.Click
        ClickEvent(7, 9, PictureBox54)
    End Sub

    Private Sub PictureBox51_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox51.Click
        ClickEvent(7, 10, PictureBox51)
    End Sub

    Private Sub PictureBox50_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox50.Click
        ClickEvent(7, 11, PictureBox50)
    End Sub

    Private Sub PictureBox44_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox44.Click
        ClickEvent(7, 12, PictureBox44)
    End Sub

    Private Sub PictureBox102_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox102.Click
        ClickEvent(7, 13, PictureBox102)
    End Sub

    Private Sub PictureBox101_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox101.Click
        ClickEvent(7, 14, PictureBox101)
    End Sub

    Private Sub PictureBox98_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox98.Click
        ClickEvent(7, 15, PictureBox98)
    End Sub

    Private Sub PictureBox122_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox122.Click
        ClickEvent(7, 16, PictureBox122)
    End Sub
    '8行目
    Private Sub PictureBox92_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox92.Click
        ClickEvent(8, 1, PictureBox92)
    End Sub

    Private Sub PictureBox91_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox91.Click
        ClickEvent(8, 2, PictureBox91)
    End Sub

    Private Sub PictureBox90_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox90.Click
        ClickEvent(8, 3, PictureBox90)
    End Sub

    Private Sub PictureBox89_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox89.Click
        ClickEvent(8, 4, PictureBox89)
    End Sub

    Private Sub PictureBox85_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox85.Click
        ClickEvent(8, 5, PictureBox85)
    End Sub

    Private Sub PictureBox59_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox59.Click
        ClickEvent(8, 6, PictureBox59)
    End Sub

    Private Sub PictureBox58_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox58.Click
        ClickEvent(8, 7, PictureBox58)
    End Sub

    Private Sub PictureBox48_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox48.Click
        ClickEvent(8, 8, PictureBox48)
    End Sub

    Private Sub PictureBox47_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox47.Click
        ClickEvent(8, 9, PictureBox47)
    End Sub

    Private Sub PictureBox46_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox46.Click
        ClickEvent(8, 10, PictureBox46)
    End Sub

    Private Sub PictureBox45_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox45.Click
        ClickEvent(8, 11, PictureBox45)
    End Sub

    Private Sub PictureBox43_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox43.Click
        ClickEvent(8, 12, PictureBox43)
    End Sub

    Private Sub PictureBox100_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox100.Click
        ClickEvent(8, 13, PictureBox100)
    End Sub

    Private Sub PictureBox99_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox99.Click
        ClickEvent(8, 14, PictureBox99)
    End Sub

    Private Sub PictureBox97_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox97.Click
        ClickEvent(8, 15, PictureBox97)
    End Sub

    Private Sub PictureBox121_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox121.Click
        ClickEvent(8, 16, PictureBox121)
    End Sub
    '9行目
    Private Sub PictureBox192_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox192.Click
        ClickEvent(9, 1, PictureBox192)
    End Sub

    Private Sub PictureBox191_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox191.Click
        ClickEvent(9, 2, PictureBox191)
    End Sub

    Private Sub PictureBox190_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox190.Click
        ClickEvent(9, 3, PictureBox190)
    End Sub

    Private Sub PictureBox189_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox189.Click
        ClickEvent(9, 4, PictureBox189)
    End Sub

    Private Sub PictureBox184_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox184.Click
        ClickEvent(9, 5, PictureBox184)
    End Sub

    Private Sub PictureBox183_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox183.Click
        ClickEvent(9, 6, PictureBox183)
    End Sub

    Private Sub PictureBox182_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox182.Click
        ClickEvent(9, 7, PictureBox182)
    End Sub

    Private Sub PictureBox178_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox178.Click
        ClickEvent(9, 8, PictureBox178)
    End Sub

    Private Sub PictureBox177_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox177.Click
        ClickEvent(9, 9, PictureBox177)
    End Sub

    Private Sub PictureBox176_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox176.Click
        ClickEvent(9, 10, PictureBox176)
    End Sub

    Private Sub PictureBox175_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox175.Click
        ClickEvent(9, 11, PictureBox175)
    End Sub

    Private Sub PictureBox170_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox170.Click
        ClickEvent(9, 12, PictureBox170)
    End Sub

    Private Sub PictureBox144_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox144.Click
        ClickEvent(9, 13, PictureBox144)
    End Sub

    Private Sub PictureBox143_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox143.Click
        ClickEvent(9, 14, PictureBox143)
    End Sub

    Private Sub PictureBox140_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox140.Click
        ClickEvent(9, 15, PictureBox140)
    End Sub

    Private Sub PictureBox132_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox132.Click
        ClickEvent(9, 16, PictureBox132)
    End Sub

    '10行目
    Private Sub PictureBox188_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox188.Click
        ClickEvent(10, 1, PictureBox188)
    End Sub

    Private Sub PictureBox187_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox187.Click
        ClickEvent(10, 2, PictureBox187)
    End Sub

    Private Sub PictureBox186_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox186.Click
        ClickEvent(10, 3, PictureBox186)
    End Sub

    Private Sub PictureBox185_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox185.Click
        ClickEvent(10, 4, PictureBox185)
    End Sub

    Private Sub PictureBox181_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox181.Click
        ClickEvent(10, 5, PictureBox181)
    End Sub

    Private Sub PictureBox180_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox180.Click
        ClickEvent(10, 6, PictureBox180)
    End Sub

    Private Sub PictureBox179_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox179.Click
        ClickEvent(10, 7, PictureBox179)
    End Sub

    Private Sub PictureBox174_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox174.Click
        ClickEvent(10, 8, PictureBox174)
    End Sub

    Private Sub PictureBox173_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox173.Click
        ClickEvent(10, 9, PictureBox173)
    End Sub

    Private Sub PictureBox172_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox172.Click
        ClickEvent(10, 10, PictureBox172)
    End Sub

    Private Sub PictureBox171_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox171.Click
        ClickEvent(10, 11, PictureBox171)
    End Sub

    Private Sub PictureBox169_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox169.Click
        ClickEvent(10, 12, PictureBox169)
    End Sub

    Private Sub PictureBox142_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox142.Click
        ClickEvent(10, 13, PictureBox142)
    End Sub

    Private Sub PictureBox141_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox141.Click
        ClickEvent(10, 14, PictureBox141)
    End Sub

    Private Sub PictureBox139_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox139.Click
        ClickEvent(10, 15, PictureBox139)
    End Sub

    Private Sub PictureBox131_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox131.Click
        ClickEvent(10, 16, PictureBox131)
    End Sub
    '11行目
    Private Sub PictureBox168_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox168.Click
        ClickEvent(11, 1, PictureBox168)
    End Sub

    Private Sub PictureBox167_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox167.Click
        ClickEvent(11, 2, PictureBox167)
    End Sub

    Private Sub PictureBox166_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox166.Click
        ClickEvent(11, 3, PictureBox166)
    End Sub

    Private Sub PictureBox165_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox165.Click
        ClickEvent(11, 4, PictureBox165)
    End Sub

    Private Sub PictureBox160_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox160.Click
        ClickEvent(11, 5, PictureBox160)
    End Sub

    Private Sub PictureBox159_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox159.Click
        ClickEvent(11, 6, PictureBox159)
    End Sub

    Private Sub PictureBox158_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox158.Click
        ClickEvent(11, 7, PictureBox158)
    End Sub

    Private Sub PictureBox154_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox154.Click
        ClickEvent(11, 8, PictureBox154)
    End Sub

    Private Sub PictureBox153_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox153.Click
        ClickEvent(11, 9, PictureBox153)
    End Sub

    Private Sub PictureBox152_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox152.Click
        ClickEvent(11, 10, PictureBox152)
    End Sub

    Private Sub PictureBox151_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox151.Click
        ClickEvent(11, 11, PictureBox151)
    End Sub

    Private Sub PictureBox146_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox146.Click
        ClickEvent(11, 12, PictureBox146)
    End Sub

    Private Sub PictureBox138_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox138.Click
        ClickEvent(11, 13, PictureBox138)
    End Sub

    Private Sub PictureBox137_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox137.Click
        ClickEvent(11, 14, PictureBox137)
    End Sub

    Private Sub PictureBox134_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox134.Click
        ClickEvent(11, 15, PictureBox134)
    End Sub

    Private Sub PictureBox130_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox130.Click
        ClickEvent(11, 16, PictureBox130)
    End Sub
    '12行目
    Private Sub PictureBox164_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox164.Click
        ClickEvent(12, 1, PictureBox164)
    End Sub

    Private Sub PictureBox163_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox163.Click
        ClickEvent(12, 2, PictureBox163)
    End Sub

    Private Sub PictureBox162_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox162.Click
        ClickEvent(12, 3, PictureBox162)
    End Sub

    Private Sub PictureBox161_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox161.Click
        ClickEvent(12, 4, PictureBox161)
    End Sub

    Private Sub PictureBox157_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox157.Click
        ClickEvent(12, 5, PictureBox157)
    End Sub

    Private Sub PictureBox156_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox156.Click
        ClickEvent(12, 6, PictureBox156)
    End Sub

    Private Sub PictureBox155_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox155.Click
        ClickEvent(12, 7, PictureBox155)
    End Sub

    Private Sub PictureBox150_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox150.Click
        ClickEvent(12, 8, PictureBox150)
    End Sub

    Private Sub PictureBox149_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox149.Click
        ClickEvent(12, 9, PictureBox149)
    End Sub

    Private Sub PictureBox148_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox148.Click
        ClickEvent(12, 10, PictureBox148)
    End Sub

    Private Sub PictureBox147_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox147.Click
        ClickEvent(12, 11, PictureBox147)
    End Sub

    Private Sub PictureBox145_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox145.Click
        ClickEvent(12, 12, PictureBox145)
    End Sub

    Private Sub PictureBox136_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox136.Click
        ClickEvent(12, 13, PictureBox136)
    End Sub

    Private Sub PictureBox135_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox135.Click
        ClickEvent(12, 14, PictureBox135)
    End Sub

    Private Sub PictureBox133_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox133.Click
        ClickEvent(12, 15, PictureBox133)
    End Sub

    Private Sub PictureBox129_Click(sender As System.Object, e As System.EventArgs) Handles PictureBox129.Click
        ClickEvent(12, 16, PictureBox129)
    End Sub
End Class