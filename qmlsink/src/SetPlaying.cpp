
#include "SetPlaying.h"

SetPlaying::SetPlaying (GstElement * pipeline)
{
  this->pipeline_ = pipeline ? static_cast<GstElement *> (gst_object_ref(pipeline)) : NULL;
}

SetPlaying::~SetPlaying ()
{
  if (this->pipeline_)
    gst_object_unref (this->pipeline_);
}

void SetPlaying::run ()
{
  GstElement *elem_ptr = gst_bin_get_by_name(GST_BIN(this->pipeline_), "video_test_source");
  //g_object_set(elem_ptr, "pattern", 18, NULL);

  if (this->pipeline_)
    gst_element_set_state (this->pipeline_, GST_STATE_PLAYING);
}
