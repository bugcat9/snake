#include "audioplaythread.h"


AudioPlayThread::AudioPlayThread(QString path)
{

      player = new QMediaPlayer;
      player->setMedia(QUrl::fromLocalFile(path));
      player->setVolume(50);

}

void AudioPlayThread::run()
{

       player->play();

}

