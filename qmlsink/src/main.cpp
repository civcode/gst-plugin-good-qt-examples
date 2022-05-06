#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickItem>

#include <QTimer>
//
#include <gst/gst.h>

#include "SetPlaying.h"
#include "MyTimer.h"


int main(int argc, char *argv[])
{
  int ret;

  gst_init (&argc, &argv);

  {
    QGuiApplication app(argc, argv);

    GstElement *pipeline = gst_pipeline_new (NULL);
    //GstElement *src = gst_element_factory_make ("videotestsrc", NULL);
    GstElement *src = gst_element_factory_make ("videotestsrc", "video_test_source");

    GstElement *scaler = gst_element_factory_make("videoscale", NULL);

    GstElement *glupload = gst_element_factory_make ("glupload", NULL);
    /* the plugin must be loaded before loading the qml file to register the
     * GstGLVideoItem qml item */
    GstElement *sink = gst_element_factory_make ("qmlglsink", NULL);

    GstElement *capsfilter = gst_element_factory_make("capsfilter", NULL);

    GstCaps *video_caps = gst_caps_new_simple("video/x-raw",
                                              //"format", G_TYPE_STRING, "I420",
                                              //"format", G_TYPE_STRING, "GRAY",
                                              "width", G_TYPE_INT, 800,
                                              "height", G_TYPE_INT, 480,
                                              NULL);

    //g_assert (src && glupload && sink);
    g_assert (src && scaler && capsfilter && glupload && sink);

    // set properties
    //g_object_set(src, "pattern", 18, NULL);
    //g_object_set(src, "");
    g_object_set(capsfilter, "caps", video_caps, NULL);


    //gst_bin_add_many (GST_BIN (pipeline), src, glupload, sink, NULL);
    //gst_element_link_many (src, glupload, sink, NULL);
    //gst_bin_add_many (GST_BIN (pipeline), src, scaler, glupload, sink, NULL);
    //gst_element_link_many (src, scaler, glupload, sink, NULL);
    gst_bin_add_many (GST_BIN (pipeline), src, scaler, capsfilter, glupload, sink, NULL);
    gst_element_link_many (src, scaler, capsfilter, glupload, sink, NULL);

    QQmlApplicationEngine engine;

    MyTimer myTimer(pipeline);
    engine.rootContext()->setContextProperty("MyTimer", &myTimer);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    QQuickItem *videoItem;
    QQuickWindow *rootObject;

    /* find and set the videoItem on the sink */
    rootObject = static_cast<QQuickWindow *> (engine.rootObjects().first());
    videoItem = rootObject->findChild<QQuickItem *> ("videoItem");
    g_assert (videoItem);
    g_object_set(sink, "widget", videoItem, NULL);

    rootObject->scheduleRenderJob (new SetPlaying (pipeline), QQuickWindow::BeforeSynchronizingStage);



    ret = app.exec();

    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
  }

  gst_deinit ();

  return ret;
}
