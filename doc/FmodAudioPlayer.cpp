bool FmodAudioPlayer::isBackgroundMusicPlaying()
{
	bool bPlaying;
	if (pBGMChannel == NULL)
 	{
		return false;
	}
	
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->isPlaying(&bPlaying);        
	ERRCHECKWITHEXIT(result);
	
	bool bPaused = false;
	result = pBGMChannel->getPaused(&bPaused);
	ERRCHECKWITHEXIT(result);
		
	return bPlaying && !bPaused;
}
