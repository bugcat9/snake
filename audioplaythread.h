#ifndef AUDIOPLAYTHREAD_H
#define AUDIOPLAYTHREAD_H

#include <QObject>
#include<QThread>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QMutex>
#include <QByteArray>
#include<QMediaPlayer>
class AudioPlayThread : public QThread
{
    Q_OBJECT
public:
    //
AudioPlayThread(QString path);

void run();
QMediaPlayer *player;
QAudioOutput *audioOutPut;

signals:

public slots:
};

#endif // AUDIOPLAYTHREAD_H
