--2014/06/09 12:48
--select * from sysdatabases where name = 'LIUJIQUAN';	-- �ŗL��
--select DB_ID('LIUJIQUAN')�G -- ��s
--select OBJECT_ID('LIUJIQUAN')	--���� 
--�n���ɝ���
if exists(select * from sysdatabases where name = 'LIUJIQUAN') 
	drop database LIUJIQUAN;
create database LIUJIQUAN;
USE LIUJIQUAN;
--�n���\User
if exists(select * from sysobjects where id = object_id('[USER]') ) 
	drop table [USER];
CREATE TABLE [USER]
(
	[ID] int NOT NULL,
	[NAME] varchar(20) NOT NULL,
	[PASSWORD] varchar(20) NOT NULL,
	constraint PK_USER primary key NONCLUSTERED
	(
		[ID]
	)
)
insert into [USER] values(2014060601,'1','1');
insert into [USER] values(2014060602,'liujiquan','123');
select * from [USER]



