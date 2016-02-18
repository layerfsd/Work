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
<link rel="stylesheet" media="all" href="./css/SendMail.css">
<script src="./js/webserver.js" type="text/javascript"></script>
</head>	
<%
Dim nResult, n
n = 2
nResult = Request.QueryString("nResult")
if Not IsEmpty(nResult) Then 
	n = CInt(nResult)
End IF

%>	
<script type="text/javascript">
var m_radiolist;
function window_load()
{
	m_radiolist = new CRadiolist(radioDiv,"radio_g"); 
	if(<%=n%> == 0)
	{
		alert("SendMail OK");
	}
	else if(<%=n%> == -1)
	{
		alert("SendMail Failed");
	}
}

function window_unload()
{
	
}
<%' �Y��%>
function AddFile(obj)
{
	m_radiolist.add(m_radiolist.length, obj);
}
<%' &#21024;��%>
function DeletFile()
{
	var group = document.getElementsByName("radio_g");	
	for(var i = 0; i < group.length; i++)
	{
		if(group[i].checked)
		{
			m_radiolist.delete_(	group[i].id, group[i].value);
			break;
		}
	}
}

function OnSendMail()
{
	var strAction = "WebSendMailUpdate.asp?fileString=";
	var group = document.getElementsByName("radio_g");
	var fileString = "";	//����������
	
	for(var i = 0; i < group.length; i++)
	{
		fileString += group[i].value + ";";
	}
	strAction = strAction + fileString;
//	strAction = strAction + "&username=";
//	strAction = strAction + document.form_sendmail.username.value;	
	document.form_sendmail.action = strAction;

	document.form_sendmail.submit();
	
}

</SCRIPT>  
<body  onload="window_load();" id='background' onunload='window_unload()'>
<form name="form_sendmail" method="post">
<% '������ Start%>
<div id='container'>
	<%' �z�u���e%>
	<div id='MaiInfoDiv' >
	<table border='1' cellpadding=2 cellspacing=2>
		<tr >
			<td style='width:60px;'>������</td>
			<td><input type='text' id='server' name='server' value='10.10.1.9'></input></td>
			<td style='width:60px;'>�[&nbsp;&nbsp;&nbsp;��</td>
			<td><input type='text' id='port' name='port' value='25'></input></td>
		</tr>
		<tr>
			<td >&#21457;���[</td>
			<td><input type='text' id='From' name='From' value='liujiquan@ase.com.cn'></input></td>
			<td>�ڝ��[</td>
			<td><textarea style='overflow-y:auto;' id='To' name='To'>liujiquan@ase.com.cn</textarea></td>
		</tr>
		<tr>
			<td>��&nbsp;&nbsp;&nbsp;��</td>
			<td><textarea style='overflow-y:auto;' id='cc' name='cc'>liujiquan@ase.com.cn</textarea></td>
			<td>��&nbsp;&nbsp;&nbsp;��</td>
			<td><textarea style='overflow-y:auto;' id='bcc' name='bcc'>liujiquan@ase.com.cn</textarea></td>
		</tr>
		<tr>
			<td>�p&#25142;��</td>
			<td><input type='text' id='username' name='username' value='Jiquan Liu/ASECN'></input></td>
			<td>��&nbsp;&nbsp;&nbsp;��</td>
			<td><input type='text' id='password' name='password' value='ase_123'></input></td>
		</tr>
		<tr>
			<td>&#26631;&nbsp;&nbsp;&nbsp;&#39064;</td>
			<td><input type='text' id='title' name='title' value='One Mail'></input></td>
		</tr>
	</table>	
	</div >	
	<%' &#21457;�����{%>
	<div id='SendTextDiv' >
		&#21457;�����{�F<BR>
		<textarea rows="10"  style='overflow-y:auto; width:100%' id='sendtext' name='sendtext'>&#35831;�ݍ�&#36755;��&#37038;�����{....</textarea>
	</div>
	<%' &#21457;������%>
	<div id='SendFileDiv' >
		&#21457;�������F<BR>
		<input type='file' NAME="file" style='width:400px;' onchange='AddFile(this.value)'>
		<input type='button' value='&#21024;��' onclick='DeletFile()' style='width:100px; height:19px;'/>
		<BR>
		<div style="width:100%; height:100%;" id='radioDiv'></div>
	</div>	
	<div id='SendButtonDiv' >
		<input type="button" onclick='OnSendMail()' value='&#21457;��&#37038;��'  style='width:200px; height:50px;'>
	</div>	
</div>	
<% '������ End%>
</form>
</body>
</html>