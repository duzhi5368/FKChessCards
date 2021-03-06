IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'TZServerInfoDB') DROP database [TZServerInfoDB]

CREATE database [TZServerInfoDB]  ON (NAME = N'TZServerInfoDB_Data', FILENAME = N'D:\天智游戏_棋牌游戏\天智游戏_棋牌游戏\MyGame\发\NewInfo\TZServerInfoDB_Data.MDF' , SIZE = 2, FILEGROWTH = 10%) LOG ON (NAME = N'TZServerInfoDB_Log', 
	FILENAME = N'D:\天智游戏_棋牌游戏\天智游戏_棋牌游戏\MyGame\发\NewInfo\TZServerInfoDB_Log.LDF' , SIZE = 1, FILEGROWTH = 10%)
	COLLATE Chinese_PRC_CI_AS
GO

exec sp_dboption N'TZServerInfoDB', N'autoclose', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'bulkcopy', N'true'
GO

exec sp_dboption N'TZServerInfoDB', N'trunc. log', N'true'
GO

exec sp_dboption N'TZServerInfoDB', N'torn page detection', N'true'
GO

exec sp_dboption N'TZServerInfoDB', N'read only', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'dbo use', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'single', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'autoshrink', N'true'
GO

exec sp_dboption N'TZServerInfoDB', N'ANSI null default', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'recursive triggers', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'ANSI nulls', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'concat null yields null', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'cursor close on commit', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'default to local cursor', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'quoted identifier', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'ANSI warnings', N'false'
GO

exec sp_dboption N'TZServerInfoDB', N'auto create statistics', N'true'
GO

exec sp_dboption N'TZServerInfoDB', N'auto update statistics', N'true'
GO

if( (@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 724) )
	exec sp_dboption N'TZServerInfoDB', N'db chaining', N'false'
GO

use [TZServerInfoDB]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GameKindInfo]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GameKindInfo]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GameStationInfo]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GameStationInfo]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GameTypeInfo]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GameTypeInfo]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[SQLdatabaseInfo]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SQLdatabaseInfo]
GO

CREATE TABLE [dbo].[GameKindInfo] (
	[KindID] [int] NOT NULL ,
	[TypeID] [int] NOT NULL ,
	[KindName] [varchar] (31) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[ProcessName] [varchar] (31) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[MaxVersion] [int] NOT NULL ,
	[SortID] [int] NOT NULL ,
	[Enable] [bit] NOT NULL ,
	[databaseName] [varchar] (30) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GameStationInfo] (
	[StationID] [int] NOT NULL ,
	[KindID] [int] NOT NULL ,
	[JoinID] [int] NOT NULL ,
	[StationName] [varchar] (15) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[SortID] [int] NOT NULL ,
	[Enable] [bit] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GameTypeInfo] (
	[TypeID] [int] NOT NULL ,
	[TypeName] [varchar] (31) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[SortID] [int] NOT NULL ,
	[Enable] [bit] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[SQLdatabaseInfo] (
	[ID] [int] IDENTITY (1, 1) NOT NULL ,
	[databasePort] [int] NOT NULL ,
	[databaseAddr] [varchar] (15) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[databaseUser] [varchar] (512) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[databasePass] [varchar] (512) COLLATE Chinese_PRC_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[GameKindInfo] WITH NOCHECK ADD 
	CONSTRAINT [PK_KindInfo] PRIMARY KEY  CLUSTERED 
	(
		[KindID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[GameStationInfo] WITH NOCHECK ADD 
	CONSTRAINT [PK_StationInfo] PRIMARY KEY  CLUSTERED 
	(
		[StationID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[GameTypeInfo] WITH NOCHECK ADD 
	CONSTRAINT [PK_TypeInfo_TypeID] PRIMARY KEY  CLUSTERED 
	(
		[TypeID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[SQLdatabaseInfo] WITH NOCHECK ADD 
	CONSTRAINT [PK_databaseInfo_ID] PRIMARY KEY  CLUSTERED 
	(
		[ID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[GameKindInfo] ADD 
	CONSTRAINT [DF_KindInfo_MaxVersion] DEFAULT (0) FOR [MaxVersion],
	CONSTRAINT [DF_KindInfo_SortID] DEFAULT (100) FOR [SortID],
	CONSTRAINT [DF_KindInfo_Enable] DEFAULT (1) FOR [Enable]
GO

 CREATE  INDEX [IX_KindInfo_TypeID] ON [dbo].[GameKindInfo]([TypeID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_KindInfo_KindID] ON [dbo].[GameKindInfo]([KindID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_KindInfo_SortID] ON [dbo].[GameKindInfo]([SortID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_KindInfo_KindName] ON [dbo].[GameKindInfo]([KindName]) ON [PRIMARY]
GO

ALTER TABLE [dbo].[GameStationInfo] ADD 
	CONSTRAINT [DF_StationInfo_JoinID] DEFAULT (0) FOR [JoinID],
	CONSTRAINT [DF_StationInfo_SortID] DEFAULT (100) FOR [SortID],
	CONSTRAINT [DF_StationInfo_Enable] DEFAULT (1) FOR [Enable]
GO

 CREATE  INDEX [IX_StationInfo_KindID] ON [dbo].[GameStationInfo]([KindID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_StationInfo_JoinID] ON [dbo].[GameStationInfo]([JoinID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_StationInfo_StationName] ON [dbo].[GameStationInfo]([StationName]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_StationInfo_SortID] ON [dbo].[GameStationInfo]([SortID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_StationInfo_StationID] ON [dbo].[GameStationInfo]([StationID]) ON [PRIMARY]
GO

ALTER TABLE [dbo].[GameTypeInfo] ADD 
	CONSTRAINT [DF_TypeInfo_SortID] DEFAULT (100) FOR [SortID],
	CONSTRAINT [DF_TypeInfo_Enable] DEFAULT (1) FOR [Enable]
GO

 CREATE  INDEX [IX_TypeInfo_SortID] ON [dbo].[GameTypeInfo]([SortID]) ON [PRIMARY]
GO

ALTER TABLE [dbo].[SQLdatabaseInfo] ADD 
	CONSTRAINT [DF_databaseInfo_databasePort] DEFAULT (1433) FOR [databasePort]
GO

 CREATE  UNIQUE  INDEX [IX_SQLdatabaseInfo_Addr] ON [dbo].[SQLdatabaseInfo]([databaseAddr]) ON [PRIMARY]
GO


exec sp_addextendedproperty N'MS_Description', N'数据库名(加)', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'databaseName'
GO
exec sp_addextendedproperty N'MS_Description', N'启用标志', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'Enable'
GO
exec sp_addextendedproperty N'MS_Description', N'种类号码', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'KindID'
GO
exec sp_addextendedproperty N'MS_Description', N'种类名字', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'KindName'
GO
exec sp_addextendedproperty N'MS_Description', N'最新版本', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'MaxVersion'
GO
exec sp_addextendedproperty N'MS_Description', N'进程名字', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'ProcessName'
GO
exec sp_addextendedproperty N'MS_Description', N'排序 ID', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'SortID'
GO
exec sp_addextendedproperty N'MS_Description', N'类型号码', N'user', N'dbo', N'table', N'GameKindInfo', N'column', N'TypeID'


GO


exec sp_addextendedproperty N'MS_Description', N'启用标志', N'user', N'dbo', N'table', N'GameStationInfo', N'column', N'Enable'
GO
exec sp_addextendedproperty N'MS_Description', N'挂接号码', N'user', N'dbo', N'table', N'GameStationInfo', N'column', N'JoinID'
GO
exec sp_addextendedproperty N'MS_Description', N'种类号码', N'user', N'dbo', N'table', N'GameStationInfo', N'column', N'KindID'
GO
exec sp_addextendedproperty N'MS_Description', N'排列号码', N'user', N'dbo', N'table', N'GameStationInfo', N'column', N'SortID'
GO
exec sp_addextendedproperty N'MS_Description', N'站点号码', N'user', N'dbo', N'table', N'GameStationInfo', N'column', N'StationID'
GO
exec sp_addextendedproperty N'MS_Description', N'站点名字', N'user', N'dbo', N'table', N'GameStationInfo', N'column', N'StationName'


GO


exec sp_addextendedproperty N'MS_Description', N'启用标志', N'user', N'dbo', N'table', N'GameTypeInfo', N'column', N'Enable'
GO
exec sp_addextendedproperty N'MS_Description', N'排列号码', N'user', N'dbo', N'table', N'GameTypeInfo', N'column', N'SortID'
GO
exec sp_addextendedproperty N'MS_Description', N'类型号码', N'user', N'dbo', N'table', N'GameTypeInfo', N'column', N'TypeID'
GO
exec sp_addextendedproperty N'MS_Description', N'类型名字', N'user', N'dbo', N'table', N'GameTypeInfo', N'column', N'TypeName'


GO


exec sp_addextendedproperty N'MS_Description', N'数据库地址', N'user', N'dbo', N'table', N'SQLdatabaseInfo', N'column', N'databaseAddr'
GO
exec sp_addextendedproperty N'MS_Description', N'数据库密码', N'user', N'dbo', N'table', N'SQLdatabaseInfo', N'column', N'databasePass'
GO
exec sp_addextendedproperty N'MS_Description', N'数据库端口', N'user', N'dbo', N'table', N'SQLdatabaseInfo', N'column', N'databasePort'
GO
exec sp_addextendedproperty N'MS_Description', N'数据库用户', N'user', N'dbo', N'table', N'SQLdatabaseInfo', N'column', N'databaseUser'
GO
exec sp_addextendedproperty N'MS_Description', N'索引号码', N'user', N'dbo', N'table', N'SQLdatabaseInfo', N'column', N'ID'


GO

