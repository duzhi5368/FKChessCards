
----------------------------------------------------------------------------------------------------

USE TZServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- 删除数据
DELETE GameTypeInfo
DELETE GameKindInfo
GO

----------------------------------------------------------------------------------------------------

-- 类型数据
INSERT GameTypeInfo (TypeID, TypeName, SortID, Enable) VALUES ( 1, '扑克类',200, 1)

----------------------------------------------------------------------------------------------------

-- 通用游戏
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 1, 1, '斗地主', 'Land.exe', 65542, 100, 1, 'TZGameDB')
----------------------------------------------------------------------------------------------------

GO