#include<gst/gst.h>

int main(int argc, char *argv[])
{
  GstElement *src, *pipeline, *sink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;

  gst_init(&argc, &argv);

  src = gst_element_factory_make("videotestsrc", "mySrc");
  sink = gst_element_factory_make("autovideosink", "mySink");
  
  pipeline = gst_pipeline_new("myPipeline");

  if( !pipeline || !src || !sink)
  {
    g_printerr("There is some problem while creating Elements!!!\n");
    return -1;
  }


  gst_bin_add_many(GST_BIN(pipeline), src, sink, NULL);
  if(gst_element_link(src, sink) != TRUE)
  {
    g_printerr("Error in linking elements\n");
    return -1;
  }

  g_object_set(src, "pattern", 0, NULL);

  ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
  return 0;
}
