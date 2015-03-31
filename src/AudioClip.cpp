#include "AudioClip.h"

/*
AudioClip::AudioClip(Envelope& _envelope) : envelope(_envelope){
	crossFade = 0.05;
}
*/
AudioClip::AudioClip(){
	crossFade = 0.05;
}

void AudioClip::setVolume(float _volume){

	//float clipPosition = getPosition();

	ofSoundPlayer::setVolume(_volume);


}
