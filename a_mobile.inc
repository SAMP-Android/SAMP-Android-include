/*----------------------------------------------------------

 Include for SA:MP Mobile
 Author: Jekmant
 Continued by: @unk.cs

 Version: 1.0 a_mobile.inc, 2023/10/21 20:11:29

---------------------------------------------------------- */
#if defined _AMOBILE_included
  #endinput
#endif

#define _AMOBILE_included

#tryinclude <a_samp>

#if !defined PAWNRAKNET_INC_
    #error Please include <Pawn.RakNet> first.
#endif

#if !defined gpci
    native gpci(playerid, buffer[], size = sizeof(buffer));
#endif

#if !defined PACKET_CUSTOMRPC
    #define PACKET_CUSTOMRPC (251)
#endif

#define SAMP_LAUNCHER_GPCI "ED40ED0E8089CC44C08EE9580F4C8C44EE8EE990"
#define SAMP_VERSION "0.3.7"

enum {
    RPC_CHECK_CLIENT = 1
}

enum pSAMPMobileInfo {
    bool:isSAMPLauncher,
    bool:isSAMPLauncherBrazil
}

new PlayerSAMPMobileInfo[MAX_PLAYERS][pSAMPMobileInfo];

public OnPlayerConnect(playerid)
{
    // TODO: check cliente SAMP Launcher
    new versionStr[64], gpciStr[64];
    GetPlayerVersion(playerid, versionStr, sizeof(versionStr));
	gpci(playerid, gpciStr, sizeof(gpciStr));

    if(!strcmp(gpciStr, SAMP_LAUNCHER_GPCI) && !strcmp(versionStr, SAMP_VERSION))
        PlayerSAMPMobileInfo[playerid][isSAMPLauncher] = true;
	else
		PlayerSAMPMobileInfo[playerid][isSAMPLauncher] = false;
	

    #if defined SAMPmob_OnPlayerConnect
		return SAMPmob_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAMPmob_OnPlayerConnect
#if defined SAMPmob_OnPlayerConnect
	forward SAMPmob_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    PlayerSAMPMobileInfo[playerid][isSAMPLauncher] = false;
    PlayerSAMPMobileInfo[playerid][isSAMPLauncherBrazil] = false;

    #if defined SAMPmob_OnPlayerDisconnect
		return SAMPmob_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SAMPmob_OnPlayerDisconnect
#if defined SAMPmob_OnPlayerDisconnect
	forward SAMPmob_OnPlayerDisconnect(playerid, reason);
#endif

// TODO: Check SAMP Launcher Brazil - Client soon.
IPacket:251(playerid, BitStream:bitstream)
{
    new rpcID;
    BS_IgnoreBits(bitstream, 8);

    BS_ReadValue
    (
        bitstream,
        PR_UINT8, rpcID
    );
 
    switch(rpcID) {
        case RPC_CHECK_CLIENT: {
            PlayerSAMPMobileInfo[playerid][isSAMPLauncherBrazil] = true;
        }
    }
    return 1;
}

stock bool:IsPlayerSAMPMobile(playerid, bool:isBrasil = false) {
    if (isBrasil) {
        return PlayerSAMPMobileInfo[playerid][isSAMPLauncherBrazil];
    } else {
        return PlayerSAMPMobileInfo[playerid][isSAMPLauncher];
    }
}
