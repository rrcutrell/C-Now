//------------------------------------------------------------------------------
//
// File Name:	Sound.h
// Author(s):	Robb Cutrell (r.cutrell)
// Project:		MyGame
// Course:		CS230S18
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

	//------------------------------------------------------------------------------
	// Forward References:
	//------------------------------------------------------------------------------
	typedef struct Sound* soundPtr;
	typedef enum SoundType soundType;

	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------
	typedef enum SoundName
	{
		SOUND_Beep,
		TRACK_MainMenu,
		TRACK_GameStateLevel1Song1,
		TRACK_GameStateLevel1Song2,
		MAX_SOUNDS

	}SoundName;

	typedef enum channelGroup
	{
		CHANNEL_MainMenu,
		CHANNEL_GameLoop,
		MAX_CHANNELGROUPS

	}channelGroup;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	bool SoundPlay(SoundName soundName, channelGroup channelGroup, bool isLooping);

	bool SoundSetPause(SoundName soundname, bool pause);

	bool SoundSetPitch(SoundName soundName, float dt);

	bool SoundSetVolume(SoundName soundName, float volume);

	bool SongOver(SoundName soundName, float dt);



	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

