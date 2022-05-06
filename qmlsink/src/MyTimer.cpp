#include <QDebug>

#include "MyTimer.h"

MyTimer::MyTimer(GstElement *pipeline, QObject *parent) : pipeline_(pipeline), QObject(parent)
{
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(onTimerExpired()));
  //timer_->start(2000);
}

void MyTimer::button(int val)
{
    //static bool state;

    qDebug() << "button called. val = " << val;

//    GstElement *elem_ptr = gst_bin_get_by_name(GST_BIN(this->pipeline_), "video_test_source");
//    if (state) {
//        g_object_set(elem_ptr, "pattern", 0, NULL);
//    } else {
//        g_object_set(elem_ptr, "pattern", 18, NULL);
//    }
//    state = !state;

    GstElement *elem_ptr = gst_bin_get_by_name(GST_BIN(this->pipeline_), "video_test_source");
    switch (val) {
    case 0: g_object_set(elem_ptr, "pattern", 0, NULL); break;
    case 1: g_object_set(elem_ptr, "pattern", 18, NULL); break;

    }
}


void MyTimer::onTimerExpired() {
    static bool state;

    //qDebug() << "state = " << state;

    GstElement *elem_ptr = gst_bin_get_by_name(GST_BIN(this->pipeline_), "video_test_source");
    if (state) {
        g_object_set(elem_ptr, "pattern", 0, NULL);
    } else {
        g_object_set(elem_ptr, "pattern", 18, NULL);
    }
    state = !state;

}

void MyTimer::onButtonPressed()
{
    static bool state;

    qDebug() << "onButtonPressed";

    GstElement *elem_ptr = gst_bin_get_by_name(GST_BIN(this->pipeline_), "video_test_source");
    if (state) {
        g_object_set(elem_ptr, "pattern", 0, NULL);
    } else {
        g_object_set(elem_ptr, "pattern", 18, NULL);
    }
    state = !state;
}
