//------------------------------------------------------------------------------
//
// File Name:	Sound.c
// Author(s):	Robb Cutrell (r.cutrell)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sound.h"
#include "fmod.h"
#include "Audio.h"
#include <stdio.h>		// printf()
#include <stdbool.h>	// FALSE

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

/*
//enum is found in header for global access
typedef enum SoundName
{
	soundEffect,
	soundTrack,
	SOUND_Beep,
	MAX_SOUNDS

}SoundName;
*/

char* SoundPaths[MAX_SOUNDS] =
{
	"Assets\\Audio\\sample_beep.wav",
	"Assets\\Audio\\sample_beep.wav",
	"Assets\\Audio\\TRACK_GameStateLevel1Song1.wav",
	"Assets\\Audio\\TRACK_GameStateLevel1Song2.wav",
};

typedef struct Sound
{

	FMOD_SOUND    *fmodSound;     // fmod struct managing fmod stuff
	FMOD_CHANNEL  *channel;  // another fmod struct managing fmod stuff
	FMOD_CHANNELGROUP *group;

}Sound;


Sound SoundArray[MAX_SOUNDS];

FMOD_RESULT result;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
FMOD_SYSTEM* soundSystem;
FMOD_CHANNELGROUP* channelGroups[MAX_CHANNELGROUPS];
float songDuration = 0.0f;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//function for opening/creating sound steam
bool SoundCreate(SoundName soundName, bool isLooping);

//function for creating new channel groups to be controlled
bool ChannelGroupCreate(FMOD_CHANNELGROUP* group);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


bool SoundPlay(SoundName soundName, channelGroup channelGroup, bool isLooping)
{
	//if sound is not already streaming, open the sound file
	if (SoundArray[soundName].fmodSound == NULL)
	{
		//checks to see if sound file was opened successfully
		bool success = SoundCreate(soundName, isLooping);
		if (!success)
		{
			return false;
		}

		//creates the sound group for sound if not already existing
		if (SoundArray[soundName].group == NULL)
		{
			success = ChannelGroupCreate(channelGroups[channelGroup]);
			if (!success)
			{
				return false;
			}
		}

		//assigns the sound's group for control purposes
		SoundArray[soundName].group = channelGroups[channelGroup];
	}

	//gets sound system
	soundSystem = GetSoundSystem();

	//Loads a sound channel with stream/sound in it and plays it in an open channel if pause is set to false
	result = FMOD_System_PlaySound(soundSystem, SoundArray[soundName].fmodSound, 0, true, &(SoundArray[soundName].channel));
	if (result != FMOD_OK)
	{
		return false;
	}

	//sets the channel into a group
	result = FMOD_Channel_SetChannelGroup(SoundArray[soundName].channel, SoundArray[soundName].group);
	if (result != FMOD_OK)
	{
		return false;
	}

	/*
	//sets the pause condition of the channel to false
	result = FMOD_Channel_SetPaused(SoundArray[soundName].channel, false);
	if (result != FMOD_OK)
	{
		return false;
	}
	*/

	return true;
}

bool SoundSetPause(SoundName soundName, bool pause)
{
	result = FMOD_Channel_SetPaused(SoundArray[soundName].channel, pause);
	if (result != FMOD_OK)
	{
		return false;
	}

	return true;
}

bool SoundSetPitch(SoundName soundName, float dt)
{
	result = FMOD_Channel_SetPitch(SoundArray[soundName].channel, dt);
	if (result != FMOD_OK)
	{
		return false;
	}

	return true;
}

bool SongOver(SoundName soundName, float dt)
{
	
	unsigned int length = 0;

	if (songDuration == 0.0f)
	{
		FMOD_Sound_GetLength(SoundArray[soundName].fmodSound, &length, FMOD_TIMEUNIT_MS);
		if (&length == NULL)
			return false;

		length /= 1000; //convert to seconds
		songDuration = (float)length;
	}

	songDuration -= dt;

	if (songDuration <= 0.0f)
	{
		songDuration = 0.0f;
		return true;
	}

	return false;

}

//sets volume with 1.0f being max volume.
bool SoundSetVolume(SoundName soundName, float volume)
{
	if (volume >= 0.75f)
	{
		volume = 0.75f; //restricts max volume
	}
	result = FMOD_Channel_SetVolume(SoundArray[soundName].channel, volume);
	if (result != FMOD_OK)
	{
		return false;
	}

	return true;
}





//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

bool SoundCreate(SoundName soundName, bool isLooping)
{
	soundSystem = GetSoundSystem();

	if (isLooping == true)
	{
		result = FMOD_System_CreateStream(soundSystem, SoundPaths[soundName], FMOD_LOOP_NORMAL | FMOD_2D, 0, &(SoundArray[soundName].fmodSound));
		return (result == FMOD_OK);
	}

	result = FMOD_System_CreateStream(soundSystem, SoundPaths[soundName], FMOD_LOOP_OFF | FMOD_2D, 0, &(SoundArray[soundName].fmodSound));
	return (result == FMOD_OK);

}

bool ChannelGroupCreate(FMOD_CHANNELGROUP* group)
{
	soundSystem = GetSoundSystem();

	bool success = FMOD_System_CreateChannelGroup(soundSystem, "test channel create", &group);
	return (success == FMOD_OK);

}