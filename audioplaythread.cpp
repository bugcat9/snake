#include "audioplaythread.h"


AudioPlayThread::AudioPlayThread(QString path)
{

      player = new QMediaPlayer;
      audioOutPut = new QAudioOutput;
      player->setAudioOutput(audioOutPut);
      player->setSource(QUrl::fromLocalFile(path));
      audioOutPut->setVolume(50);


}

void AudioPlayThread::run()
{

       player->play();

}

