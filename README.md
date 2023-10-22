# SA-MP Android Include

An include to detect if the user is using the SA-MP Android mobile client.

## Example
```pawn
public OnPlayerConnect(playerid)
{
	if(IsPlayerSAMPMobile(playerid)) {
    	SendClientMessage(playerid, -1, "You are using the SA-MP Android client."); 
	}
	else {
    	SendClientMessage(playerid, -1, "You are not using the SA-MP Android client.");
	}	
	return 1;
}
```

### Credits
- Author by: **Jekmant**
- Continued by: **SAMP Android Brasil**
