
#if defined Spike_STRIP_Included_
   #endinput
#endif

#define Spike_STRIP_Included_

#define MAX_SPIKESTRIPS 200
#include <YSI_Coding\y_hooks>//Credits to Y_Less

enum sInfo
{
	sCreated,
    Float:sX,
    Float:sY,
    Float:sZ,
    sObject,
};

static SpikeInfo[MAX_SPIKESTRIPS][sInfo];

hook OnPlayerUpdate(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        for(new i = 0; i < sizeof(SpikeInfo); i++)
  	    {
  	        if(IsPlayerInRangeOfPoint(playerid, 3.0, SpikeInfo[i][sX], SpikeInfo[i][sY], SpikeInfo[i][sZ]))
            {
  	            if(SpikeInfo[i][sCreated] == 1)
  	            {
  	                new panels, doors, lights, tires;
  	                new carid = GetPlayerVehicleID(playerid);
		            GetVehicleDamageStatus(carid, panels, doors, lights, tires);
		            tires = encode_tires(1, 1, 1, 1);
			    	if(GetPlayerWantedLevel(playerid)>=1) UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
  	            }
  	        }
  	    }
  	}
	return 1;
}

stock CreateStrip(Float:x,Float:y,Float:z,Float:Angle)
{
    for(new i = 0; i < sizeof(SpikeInfo); i++)
  	{
  	    if(SpikeInfo[i][sCreated] == 0)
  	    {
            SpikeInfo[i][sCreated]=1;
            SpikeInfo[i][sX]=x;
            SpikeInfo[i][sY]=y;
            SpikeInfo[i][sZ]=z-0.7;
            SpikeInfo[i][sObject] = CreateObject(2899, x, y, z-0.9, 0, 0, Angle-90);
	        return 1;
  	    }
  	}
  	return 0;
}

stock DeleteAllStrip()
{
    for(new i = 0; i < sizeof(SpikeInfo); i++)
  	{
  	    if(SpikeInfo[i][sCreated] == 1)
  	    {
  	        SpikeInfo[i][sCreated]=0;
            SpikeInfo[i][sX]=0.0;
            SpikeInfo[i][sY]=0.0;
            SpikeInfo[i][sZ]=0.0;
            DestroyObject(SpikeInfo[i][sObject]);
            SpikeInfo[i][sObject]=-1;
  	    }
	}
    return 0;
}

stock DeleteClosestStrip(playerid)
{
    for(new i = 0; i < sizeof(SpikeInfo); i++)
  	{
  	    if(IsPlayerInRangeOfPoint(playerid, 2.0, SpikeInfo[i][sX], SpikeInfo[i][sY], SpikeInfo[i][sZ]))
        {
  	        if(SpikeInfo[i][sCreated] == 1)
            {
                SpikeInfo[i][sCreated]=0;
                SpikeInfo[i][sX]=0.0;
                SpikeInfo[i][sY]=0.0;
                SpikeInfo[i][sZ]=0.0;
                DestroyObject(SpikeInfo[i][sObject]);
                SpikeInfo[i][sObject]=-1;
                return 1;
  	        }
  	    }
  	}
    return 0;
}

static encode_tires(tires1, tires2, tires3, tires4) {

	return tires1 | (tires2 << 1) | (tires3 << 2) | (tires4 << 3);

}
