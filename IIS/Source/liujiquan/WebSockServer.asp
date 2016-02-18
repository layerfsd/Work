<%@ LANGUAGE="VBSCRIPT"%>
<SCRIPT LANGUAGE="VBSCRIPT" RUNAT="SERVER">
'====================
'Filename : WebSockClient.asp
'Title�F����WebSock�ʐu
'Date :2014-06-04
'Version : 1.00
'Copyright (C) AMANO Corporation 2006 - 2009
'====================
</SCRIPT>
<!doctype html>
<html lang="ja">
<head>
<meta http-equiv="content-type" content="text/html; charset=Shift_JIS">
<meta http-equiv="content-style-type"  content="text/css">
<meta http-equiv="content-script-type" content="text/javascript">
<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="cache-control" content="no-cache">
<title>Main</title>
<meta name="robots" content="none">
<meta name="description" content="Liujiquan Test WebSock">
<meta name="author" content="ABS-ASE:Development Team">
<link rel="stylesheet" media="all" href="./css/login.css">
<script src="./js/webserver.js" type="text/javascript"></script>
</head>		
<script type="text/javascript">
var m_Object;
var m_listInfo;
var m_ListIp;

function window_load()
{
	//ATL
	m_Object = new ActiveXObject("WebSocketServerProject.IServer"); 
	//Info
	m_listInfo = new CListBox(document.form_server.listBox);
	//IP
	m_ListIp = new CListBox2(document.getElementById("ul_IP"));
}

function window_unload()
{
	OnStopServer();
}
//FunctionID
var AddMsgID = 0;
var AddIPID = 1;
var DeleteIPID = 2;
function OnStartServer()
{
	// �ݒu����
	m_Object.SetJsCallbackFunc(AddString, AddMsgID);
	m_Object.SetJsCallbackFunc(AddIP, AddIPID);
	m_Object.SetJsCallbackFunc(DeleteIP, DeleteIPID);
	var bResult = m_Object.OnInitSocket();
}	
//萕���
function OnStopServer()
{
	m_Object.OnStop();

}
//�Y���M��
function AddString(str)
{
	m_listInfo.addString(str);
}
//�Y��IP
function AddIP(str)
{
	m_ListIp.add(str);
}

//IP����IP
function DeleteIP(str)
{
	m_ListIp.deleteIP(str);
}
</SCRIPT>  
<body  onload="window_load();" id='background' onunload="window_unload();">
<form name="form_server" method="post">
<% '������ Start%>
<div id='container'>

	<div id='ButtonDiv'>
	<table width='100%'>
		<tr>
			<td align='center'><input Type='Button' Value='�J&#21855;����' onClick='OnStartServer()' Name="StartButton"></td>
			<td align='center'><input Type='Button' Value='萕���' onClick='OnStopServer()' Name="StopButton"></td>
		</tr>
	</table>
	</div>
	<div id='InfoDiv'>
		<select name="listBox" id = "listBox" multiple="true"  size="25"  style="width:100%" > </select>  
	</div >	
	<div id='ListDiv'>
		<h2>&nbsp;&nbsp;&nbsp;IP��\</h2>
		<ul id='ul_IP' name='ul_IP'>
		</ul>
	</div>
</div>	
<% '������ End%>
</form>
</body>
</html>