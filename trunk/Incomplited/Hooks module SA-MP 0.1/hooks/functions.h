/*
 *	Copyright (C) 2011 Alex009
 *	License read in license.txt
 */

class FakeClass {};

#ifdef WIN32
	typedef void (FakeClass::* f_ClientConnect_1)(int,char*);
	typedef void (FakeClass::* f_ClientConnect_2)(int,char*,int);
	typedef void (FakeClass::* f_ClientConnect_3)(int,char*,char*,int);
	typedef void (FakeClass::* f_ClientDisconnect)(int,int);
	typedef void (FakeClass::* f_SpawnForWorld)();
	typedef void (FakeClass::* f_DeathForWorld)(int,int);

	typedef void (* f_TeleportFunction)(int,float,float,float);
#else
	typedef void (* f_ClientConnect)(FakeClass*,int,char*,char*,int);
	typedef void (* f_ClientDisconnect)(FakeClass*,int,int);
	typedef void (* f_SpawnForWorld)(FakeClass*);
	typedef void (* f_SetSpawnInfoPointer)(FakeClass*,int[]);
	typedef void (* f_SetSkinPointer)(int,int[]);
	typedef void (* f_KillForWorld)(FakeClass*,int,int);
	typedef void (* f_SetWeaponSkill)(FakeClass*,int,int);
#endif