#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>
#include <gst/gst.h>

class MyTimer : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit MyTimer(GstElement *pipeline, QObject *parent = nullptr);

    Q_INVOKABLE void button(int val);

signals:
    void buttonPressed();

private slots:
  void onTimerExpired();
  void onButtonPressed();

private:
  GstElement * pipeline_;
  QTimer *timer_;
};


#endif // MYTIMER_H
