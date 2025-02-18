
#if !defined DISABLE_GUNCHEATS
	#include <Anti-Cheat/GunCheats>//Anti gun cheats -Rogue
#endif

#if !defined DISABLE_LAGGERSDETECT
	#include <Anti-Cheat/LaggersDetect>//Lag spike\desnyc detector- Rogue
#endif

#if !defined DISABLE_AIRBREAKTELEPORT
	#include <Anti-Cheat/AirbreakTeleport>//Anti airbreak\teleport - Rogue
#endif

#if !defined DISABLE_CARTROLL
	#include <Anti-Cheat/CarTroll>//Anti car trolls - Rogue
#endif

#if !defined DISABLE_JETPACK
	#include <Anti-Cheat/Jetpack>//Anti jetpack cheats- Rogue
#endif

#if !defined DISABLE_VEHICLEABUSE
	#include <Anti-Cheat/VehicleAbuse>//Anti carswing\particlespam - Lorenc_
#endif

#if !defined DISABLE_MONEYCHEATS
	#include <Anti-Cheat/MoneyCheats>//Anti money cheats- Rogue
#endif

#if !defined DISABLE_GODMODE
	#include <Anti-Cheat/GodMode>//Anti godmode -Rogue
#endif

#if !defined DISABLE_BUGCHEATS
	#include <Anti-Cheat/BugCheats>//Depresses 5 abusing bugs triggered by cheats. -Rogue
#endif

#if !defined DISABLE_FAKEKILL
	#include <Anti-Cheat/FakeKill> //Anti fake kill -Rogue
#endif

#if !defined DISABLE_FAKECONNECT
	#include <Anti-Cheat/FakeConnect>//Anti fake clients - Rogue
#endif

#if !defined DISABLE_SPEEDCHEATS
	#include <Anti-Cheat/SpeedCheats>//Anti speed cheats- Rogue
#endif

#if !defined DISABLE_VEHICLEMODS
	#include <Anti-Cheat/VehicleMods>//Anti illegal car mods -Emmet_
#endif

#if !defined DISABLE_CARSPAM
	#include <Anti-Cheat/CarSpam>//Anti car spam - Rogue
#endif

#if !defined DISABLE_EASYDIALOG
	#include <Anti-Cheat/EasyDialog> //Anti dialog spoof/crash- Emmet_ (easyDialog)
#endif

#if !defined DISABLE_CHATSPAM
	#include <Anti-Cheat/ChatSpam>//Anti chat spam- Rogue
#endif

#if !defined DISABLE_SLIDEBUG
	#include <Anti-Cheat/SlideBug>//Anti slide bug abuse- Rogue
#endif

#if defined _AC_SYSTEM_
   #endinput
#endif

#define _AC_SYSTEM_

#define SEVERITY_CASE_ONE 0 	//Warn then kick
#define SEVERITY_CASE_TWO 1		//Kick
#define SEVERITY_CASE_THREE 2	//Ban

#define VIOLATION_CODE_BUGATTEMPT 0
#define VIOLATION_CODE_LAGOUT 1
#define VIOLATION_CODE_SLIDEBUG 2
#define VIOLATION_CODE_INVALIDMODS 3
#define VIOLATION_CODE_PARTICLESPAM 4
#define VIOLATION_CODE_CARSWING 5
#define VIOLATION_CODE_MONEYHACK 6
#define VIOLATION_CODE_CARTROLL 7
#define VIOLATION_CODE_CARSPAM 8
#define VIOLATION_CODE_AIRBRAKE 9
#define VIOLATION_CODE_SPEEDING 10
#define VIOLATION_CODE_CHATSPAM 11
#define VIOLATION_CODE_JETPACK 12
#define VIOLATION_CODE_FAKECONNECT 13
#define VIOLATION_CODE_FAKEKILL 14
#define VIOLATION_CODE_GODMODE 15
#define VIOLATION_CODE_WEPHACKS 16

static s_playerWarnings[MAX_PLAYERS];
#define MAX_WARNS_AC 3 //Max warns before kick in severe case 1

forward OnPlayerViolate(playerid, severity, violationCode, const violationName[]);
public OnPlayerViolate(playerid, severity, violationCode, const violationName[])
{
	new acString[STRING_SIZE_LARGE], name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof name);
	switch(severity)
	{
		case SEVERITY_CASE_ONE:
		{
			if(s_playerWarnings[playerid] < MAX_WARNS_AC) s_playerWarnings[playerid]++;
			else 
			{
				format(acString, sizeof acString, "Player %s was kicked after 3 warnings, reason: Code violation #%d", name, violationCode);
				if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) Kick(playerid),
					SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, acString, MESSAGE_CASE_JANITOR);

			}
		}
		case SEVERITY_CASE_TWO:
		{
			format(acString, sizeof acString, "Player %s was kicked, reason: Code violation #%d", name, violationCode);
			if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) Kick(playerid),
				SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, acString, MESSAGE_CASE_JANITOR);
		}
		case SEVERITY_CASE_THREE:
		{
			format(acString, sizeof acString, "Player %s was banned, reason: Code violation #%d", name, violationCode);
			if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN)
			{
				SetCauseOfBan(playerid, violationName);
				BanByName(playerid);
				BanEx(playerid, violationName);
			} 
			SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, acString, MESSAGE_CASE_JANITOR);
		}
	}
	SendToAdminLogs(acString);
	return 1;
}

#if !defined DISABLE_FAKEKILL

	public OnPlayerFakeKill(playerid, spoofedid, spoofedreason, faketype)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_FAKEKILL, "Fake killing");
		return 1;
	}

#endif

#if !defined DISABLE_FAKECONNECT

	public OnPlayerFakeConnect(playerid)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_FAKECONNECT, "Fake connect");
		return 1;
	}

#endif

#if !defined DISABLE_JETPACK

	public OnPlayerJetpackCheat(playerid)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_THREE, VIOLATION_CODE_JETPACK, "Jetpack cheats");
		return 1;
	}

#endif

#if !defined DISABLE_GODMODE

	public OnPlayerGodmode(playerid, gmtype)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_GODMODE, "Godmode cheats");
		return 1;
	}

#endif

#if !defined DISABLE_CHATSPAM

	public OnPlayerSpamChat(playerid)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_ONE, VIOLATION_CODE_CHATSPAM, "Chat spamming");
		return 1;
	}

#endif

#if !defined DISABLE_GUNCHEATS

	public OnPlayerGunCheat(playerid, weaponid, ammo, hacktype)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_WEPHACKS, "Weapon cheats");
		return 1;
	}

#endif

#if !defined DISABLE_SPEEDCHEATS

	public OnPlayerSpeedCheat(playerid, speedtype)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_SPEEDING, "Speed cheats");
		return 1;
	}

#endif

#if !defined DISABLE_AIRBREAKTELEPORT

	public OnPlayerBreakAir(playerid, breaktype)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_AIRBRAKE, "Airbrake");
		return 1;
	}

#endif

#if !defined DISABLE_CARSPAM

	public OnPlayerSpamCars(playerid, number)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_THREE, VIOLATION_CODE_CARSPAM, "Car spam");
		return 1;
	}

#endif

#if !defined DISABLE_CARTROLL

	public OnPlayerCarTroll(playerid, vehicleid, trolledid, trolltype)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_CARTROLL, "Car troll");
		return 1;
	}

#endif

#if !defined DISABLE_MONEYCHEATS

	public OnPlayerCashCheat(playerid, oldcash, newcash, amount)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_MONEYHACK, "Cash cheats");
		return 1;
	}

#endif

#if !defined DISABLE_VEHICLEABUSE

	public OnPlayerCarSwing(playerid, vehicleid)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_CARSWING, "Car swing");
		return 1;
	}

	public OnPlayerParticleSpam(playerid, vehicleid)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_THREE, VIOLATION_CODE_PARTICLESPAM, "Particle spamming");
		return 1;
	}

#endif

#if !defined DISABLE_VEHICLEMODS

	public OnVehicleModEx(playerid, vehicleid, componentid, illegal)
	{
		if(illegal)
		{
			OnPlayerViolate(playerid, SEVERITY_CASE_THREE, VIOLATION_CODE_INVALIDMODS, "Invalid mods");
		}
		return 1;
	}

#endif

#if !defined DISABLE_SLIDEBUG

	public OnPlayerSlide(playerid, weaponid, speed)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_ONE, VIOLATION_CODE_SLIDEBUG, "Slide bugging");
		return 1;
	}

#endif

#if !defined DISABLE_LAGGERSDETECT

	public OnPlayerLagout(playerid, lagtype, ping)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_ONE, VIOLATION_CODE_LAGOUT, "Huge lag");
		return 1;
	}

#endif

#if !defined DISABLE_BUGCHEATS

	public OnPlayerBugAttempt(playerid, bugcode)
	{
		OnPlayerViolate(playerid, SEVERITY_CASE_TWO, VIOLATION_CODE_BUGATTEMPT, "Bug cheats");
		return 1;
	}

#endif

#if defined AC_OnPlayerDisconnect
	forward AC_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	s_playerWarnings[playerid] = 0;

	#if defined AC_OnPlayerDisconnect
		return AC_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}


#if defined _ALS_OnPlayerDisconnect
  #undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect AC_OnPlayerDisconnect
