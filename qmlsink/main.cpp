#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
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

SetPlaying::SetPlaying (GstElement * pipeline)
{
  this->pipeline_ = pipeline ? static_cast<GstElement *> (gst_object_ref (pipeline)) : NULL;
}

SetPlaying::~SetPlaying ()
{
  if (this->pipeline_)
    gst_object_unref (this->pipeline_);
}

void
SetPlaying::run ()
{
  if (this->pipeline_)
    gst_element_set_state (this->pipeline_, GST_STATE_PLAYING);
}

int main(int argc, char *argv[])
{
  int ret;

  gst_init (&argc, &argv);

  {
    QGuiApplication app(argc, argv);

    GstElement *pipeline = gst_pipeline_new (NULL);
    GstElement *src = gst_element_factory_make ("videotestsrc", NULL);

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
    g_assert (src && scaler && glupload && sink);

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
//    if (!gst_element_link_filtered(src, scaler, video_caps)) {
//        return -1;
//    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickItem *videoItem;
    QQuickWindow *rootObject;

    /* find and set the videoItem on the sink */
    rootObject = static_cast<QQuickWindow *> (engine.rootObjects().first());
    videoItem = rootObject->findChild<QQuickItem *> ("videoItem");
    g_assert (videoItem);
    g_object_set(sink, "widget", videoItem, NULL);

    rootObject->scheduleRenderJob (new SetPlaying (pipeline),
        QQuickWindow::BeforeSynchronizingStage);

    ret = app.exec();

    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
  }

  gst_deinit ();

  return ret;
}
