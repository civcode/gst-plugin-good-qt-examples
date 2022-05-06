#ifndef SETPLAYING_H
#define SETPLAYING_H

#include <QRunnable>
#include <gst/gst.h>

class SetPlaying : public QRunnable
{
public:
  SetPlaying(GstElement *);
  ~SetPlaying();

  void run ();

private:
  GstElement * pipeline_;
};

#endif // SETPLAYING_H
