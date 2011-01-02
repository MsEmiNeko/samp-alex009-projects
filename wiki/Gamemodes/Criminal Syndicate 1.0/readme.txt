Criminal Syndicate 1.0
by 009 (Alex009)

Description:
RolePlay gamemode.Not edit.
NEXTGEN:
Core systems description:
> 3dtexts - 3dtexts streamer, add some functions for controll.

native CreateMode3DText(Text[],Color,Float:X,Float:Y,Float:Z,Float:DrawDistance,ModeInterior,VirtualWorld,LOS);
native DestroyMode3DText(text3did);
native GetMode3DTextPos(text3did,&Float:X,&Float:Y,&Float:Z);
native SetMode3DTextPos(text3did,Float:X,Float:Y,Float:Z);
native GetMode3DTextModeInterior(text3did);
native SetMode3DTextModeInterior(text3did,modeinterior);
native GetMode3DTextVirtualWorld(text3did);
native SetMode3DTextVirtualWorld(text3did,virtualworld);
native AttachMode3DTextToPlayer(text3did,playerid,Float:oX,Float:oY,Float:oZ);
native AttachMode3DTextToVehicle(text3did,vehicleid,Float:oX,Float:oY,Float:oZ);
native DeAttachMode3DText(text3did);
native IsMode3DTextAttached(text3did);
native GetMode3DTextText(text3did);
native SetMode3DTextText(text3did,Text[]);
native GetMode3DTextColor(text3did);
native SetMode3DTextColor(text3did,Color);
native Float:GetMode3DTextDrawDistance(text3did);
native SetMode3DTextDrawDistance(text3did,Float:DrawDistance);
native IsMode3DTextNeedToShow(playerid,text3did);

> actions - select action GUI.

native SetPlayerAction(playerid,actionid);
native GetPlayerAction(playerid);
native AddActionSelectRow(const actionname[],actionid);
native ShowActionSelecting(playerid);

> camera - camera controll functions.

native MovePlayerCamera(playerid,cameraid,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:vX,Float:vY,Float:vZ,Float:speed);
native MovePlayerCameraEx(playerid,cameraid,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:lX,Float:lY,Float:lZ,Float:speed);
native MovePlayerCameraAroundPlayer(playerid,cameraid,aroundid,Float:radius,Float:speed,direction);
native MovePlayerCameraAroundXYZ(playerid,cameraid,Float:X,Float:Y,Float:Z,Float:radius,Float:speed,direction);
native MovePlayerCameraAroundXYZEx(playerid,cameraid,Float:X,Float:Y,Float:Z,Float:radius,Float:speed,Float:minAngle,Float:maxAngle,direction);
native Float:GetPlayerCameraAroundRadius(playerid);
native SetPlayerCameraAroundRadius(playerid,Float:radius);
native GetPlayerCameraAroundCenter(playerid,&Float:X,&Float:Y,&Float:Z);
native SetPlayerCameraAroundCenter(playerid,Float:X,Float:Y,Float:Z);
native GetPlayerCameraAroundDirection(playerid);
native SetPlayerCameraAroundDirection(playerid,direction);
native StopPlayerCamera(playerid,bool:returncamera);
native IsPlayerCameraMoving(playerid);

> debug - debug system.

native Debug(type,const format[],{Float,_}:...);

> dialogs - dialogs controll functions.

native ShowPlayerModeDialog(playerid,dialogid,style,caption[],info[],button1[],button2[]);
native HidePlayerModeDialog(playerid);
native SetPlayerModeDialogListData(playerid,listitem,data);
native GetPlayerModeDialogListData(playerid,listitem);
native GetPlayerModeDialogStyle(playerid);

> holding - data holding.MySQL,SQLite,Files.

native AddHolding(dir[],field[],name[]);
native OpenHolding(dir[],field[],name[],mode);
native CloseHolding();
native IsHoldingExist(dir[],field[],name[]);
native DeleteHolding(dir[],field[],name[]);
native GetHoldingDataInt(field[]);
native Float:GetHoldingDataFloat(field[]);
native GetHoldingDataString(field[]);
native GetHoldingDataStringEx(field[],dest[],destlen=sizeof dest);
native SetHoldingDataInt(field[],data);
native SetHoldingDataFloat(field[],Float:data);
native SetHoldingDataString(field[],data[]);
native GetHoldingDataByOrder(dir[],field[],order);
native OpenHoldingTable(dir[]);
native NextHoldingTableRow();
native CloseHoldingTable();

> icons - icons streamer.Some controll functions.

native CreateModeIcon(Icon,Color,Float:X,Float:Y,Float:Z,ModeInterior,VirtualWorld);
native DestroyModeIcon(iconid);
native GetModeIconPos(iconid,&Float:X,&Float:Y,&Float:Z);
native SetModeIconPos(iconid,Float:X,Float:Y,Float:Z);
native GetModeIconModeInterior(iconid);
native SetModeIconModeInterior(iconid,modeinterior);
native GetModeIconVirtualWorld(iconid);
native SetModeIconVirtualWorld(iconid,virtualworld);
native GetModeIconIcon(iconid);
native SetModeIconIcon(iconid,icon);
native GetModeIconColor(iconid);
native SetModeIconColor(iconid,color);
native IsModeIconNeedToShow(playerid,iconid);

> interiors - interiors without furniture.Enter exits.Need interiors.txt file.

native SetPlayerModeInterior(playerid,modeinteriorid);
native GetPlayerModeInterior(playerid);
native GetModeInteriorExitPos(modeinteriorid,&Float:X,&Float:Y,&Float:Z);

> objects - objects streamer.Some controll functions.Destructible objects.

native CreateModeObject(Model,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ,ModeInterior,VirtualWorld,Float:Health,Type,TypeParam);
native DestroyModeObject(objectid);
native GetModeObjectPos(objectid,&Float:X,&Float:Y,&Float:Z);
native SetModeObjectPos(objectid,Float:X,Float:Y,Float:Z);
native GetModeObjectRot(objectid,&Float:rX,&Float:rY,&Float:rZ);
native SetModeObjectRot(objectid,Float:rX,Float:rY,Float:rZ);
native GetModeObjectModeInterior(objectid);
native SetModeObjectModeInterior(objectid,modeinterior);
native GetModeObjectVirtualWorld(objectid);
native SetModeObjectVirtualWorld(objectid,virtualworld);
native AttachModeObjectToPlayer(objectid,playerid,Float:oX,Float:oY,Float:oZ,Float:orX,Float:orY,Float:orZ);
native DeAttachModeObject(objectid);
native IsModeObjectAttached(objectid);
native GetPlayerAttachedModeObject(playerid);
native GetModeObjectModel(objectid);
native GetModeObjectType(objectid);
native SetModeObjectType(objectid,type);
native GetModeObjectTypeParam(objectid);
native SetModeObjectTypeParam(objectid,typeparam);
native Float:GetModeObjectHealth(objectid);
native SetModeObjectHealth(objectid,Float:health);
native GetPlayerClosestModeObject(playerid);
native Float:GetPlayerDistanceToModeObject(playerid,objectid);
native IsModeObjectNeedToShow(playerid,objectid);
native IsPlayerRangeOfModeObject(playerid,Float:range,objectid);
native HideModeObject(objectid);
native ShowModeObject(objectid);
native IsModeObjectStreamedIn(objectid,playerid);
native GetMaxModeObjectId();
native IsValidModeObject(objectid);

> parsers - CMDs, Texts, Dialogs parsing.

native RegisterCmd(cmdtext[],command[],cmdlen,prefics,cmdid);
native RegisterText(text[],char,prefics,textid);
native RegisterDialog(playerid,response,listitem,inputtext,prefics,dialogid);

> pickups - pickups streamer.Some controll functions.

native CreateModePickup(Model,Type,Float:X,Float:Y,Float:Z,ModeInterior,VirtualWorld,TypeEx,TypeExParam);
native DestroyModePickup(pickupid);
native GetModePickupPos(pickupid,&Float:X,&Float:Y,&Float:Z);
native SetModePickupPos(pickupid,Float:X,Float:Y,Float:Z);
native GetModePickupModeInterior(pickupid);
native SetModePickupModeInterior(pickupid,modeinterior);
native GetModePickupVirtualWorld(pickupid);
native SetModePickupVirtualWorld(pickupid,virtualworld);
native GetModePickupModel(pickupid);
native GetModePickupType(pickupid);
native SetModePickupType(pickupid,type);
native GetModePickupTypeEx(pickupid);
native SetModePickupTypeEx(pickupid,type);
native GetModePickupTypeExParam(pickupid);
native SetModePickupTypeExParam(pickupid,typeparam);
native GetPlayerPickupOn(playerid);
native IsModePickupNeedToShow(playerid,pickupid);

> utils - some of the necessary functions.

native StripNL(str[]);
native GetMaxPlayerId();
native GetDistanceBetweenCoords(Float:X1,Float:Y1,Float:Z1,Float:X2,Float:Y2,Float:Z2);
native TogglePlayerControllableEx(playerid,bool:toggle);
native IsPlayerControllable(playerid);
native MoveCoordsOnAngleByDistance(Float:X,Float:Y,Float:angle,Float:distance);
native ShowHelpBoxForPlayer(playerid,helpboxid,info[]);
native GetPlayerClosestPlayer(playerid);
native fixchars(string[]);
native nullstr(string[]);
native IsPlayerInRangeOfPlayer(playerid,Float:range,pid);
native PreLoadAnimation(playerid,animlib[]);
native GetPlayerCity(playerid);

> vehicles - Some controll functions.

native CreateModeVehicle(model,Float:posx,Float:posy,Float:posz,Float:angle,color1,color2,key,stype,ssubtype,sid);
native DestroyModeVehicle(vehicleid);
native GetModeVehiclePos(vehicleid,&Float:X,&Float:Y,&Float:Z);
native SetModeVehiclePos(vehicleid,Float:X,Float:Y,Float:Z);
native GetModeVehicleAngle(vehicleid,&Float:A);
native SetModeVehicleAngle(vehicleid,Float:A);
native GetModeVehicleHealth(vehicleid,&Float:health);
native SetModeVehicleHealth(vehicleid,Float:health);
native GetModeVehicleTuning(vehicleid,component);
native SetModeVehicleTuning(vehicleid,componentid);
native GetModeVehiclePaintjob(vehicleid);
native SetModeVehiclePaintjob(vehicleid,painjobid);
native GetModeVehicleColor(vehicleid,&color1,&color2);
native SetModeVehicleColor(vehicleid,color1,color2);
native GetModeVehicleKeysize(vehicleid);
native SetModeVehicleKeysize(vehicleid,key);
native GetModeVehicleSpeedoInfo(vehicleid,&stype,&ssubtype,&sid);
native SetModeVehicleSpeedoInfo(vehicleid,stype,ssubtype,sid);
native GetModeVehicleDoorStatus(vehicleid);
native SetModeVehicleDoorStatus(vehicleid,status);
native GetModeVehicleRadioStation(vehicleid);
native SetModeVehicleRadioStation(vehicleid,requency);
native Float:GetModeVehicleFuel(vehicleid);
native SetModeVehicleFuel(vehicleid,Float:fuel);
native GetModeVehicleEngineState(vehicleid);
native SetModeVehicleEngineState(vehicleid,state);
native Float:GetModeVehicleMaxLuggage(vehicleid);
native GetModeVehicleLuggageType(vehicleid);
native GetPlayerClosestModeVehicle(playerid);
native IsPlayerAroundLuggageModeVehicl(playerid,vehicleid);
native IsPlayerAroundDoorModeVehicle(playerid,vehicleid);
native GetModeVehicleType(model);
native GetModeVehicleSubType(model);
native GetMaxModeVehicleId();
native IsModeVehicleActive(vehicleid);
native Float:GetModeVehicleMaxFuel(model);

Game systems description:
> furniture - furniture for premises.Moving, destroing, using. NOT COMPLETED. (not complete list of furniture.not completed types actions).

native CreateFurniture(type,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ,premise);
native GetFurnitureType(furnitureid);
native Float:GetFurnitureMaxLuggage(furnitureid);
native GetFurnitureModeObject(furnitureid);
native Float:GetFurnituresMassForVehicle(vehicleid);
native SetFurnitureVar(furnitureid,varid,value);
native GetFurnitureVar(furnitureid,varid);

> premise - premises.Open, close.Enter exit. NOT COMPLETED (have not saving data).

native GetPlayerPremise(playerid);
native SetPlayerPremise(playerid,premiseid);
native GetPremiseDoorStatus(premiseid);
native SetPremiseDoorStatus(premiseid,status);
native GetPremiseKeysize(premiseid);
native SetPremiseKeysize(premiseid,keysize);
native GetPremiseEnterPos(premiseid,&Float:X,&Float:Y,&Float:Z);
native GetPlayerPremiseEnterOn(playerid);
native GetPlayerPremiseExitOn(playerid);

OLD (need to update for new core):
Game systems description:
> admin - admin system
> characters - characters create,delete,edit.
> delivery - imports of goods in the state, ordering, payment, receipt of goods.
> items - items of characters.
> network - networks for mobile and radio.
> player - brainfuck.
> vehicles - controll vehicles.

Scriptfiles description:
> holding - holding config file
> interiors - interiors objects list
> CS.db - SQLite data base (if holding for SQLite) (by current config)
> CS folder - file data holding (by current config)