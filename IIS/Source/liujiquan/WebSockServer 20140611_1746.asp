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
</head>	
<%
'	Set Obj = Server.CreateObject("WebSocketServer.SocketServer")
%>		
<!--
<OBJECT id="m_Object" CLASSID="CLSID:C848BB5E-04A0-4D52-A6DA-F978D69E078C"></OBJECT>									
-->
<script type="text/javascript">
//var m_Object;
function OnStartServer()
{
	// �n������
	m_Object  = new ActiveXObject("WebSocketServer.SocketServer"); 
	// �ݒu����
	m_Object.SetJsCallbackFunc(AddString);
//	m_Object.TestJsFunc();
	var bResult = m_Object.OnInitSocket();
}

function OnAdd(i)
{
	alert("ATL Com�g�����pJSFunc ����");	
	alert(i);		
}
//���x
function GetLength()
{
	return document.form_server.listBox.options.length;
}
//����
function ClearList()
{
	document.form_server.listBox.options.length = 0;
}
//�Y��
function AddString(str)
{
	var len = GetLength();
	var item = new Option(str,len);
	document.form_server.listBox.options.add(item);
}
</SCRIPT>
<form name="form_server" method="post">
<input Type='Button' Value='&#21855;������' onClick='OnStartServer()' Name="InitButton">
<select name="listBox" id = "listBox" multiple="true"  size="25"  style="width:200px" >  
</select>  
<input Type='Button' Value='Add' onClick='AddString("123")' Name="Add">
</form>
</body>
</html>
