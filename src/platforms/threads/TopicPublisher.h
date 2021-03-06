
#ifndef   _PLATFORM_THREAD_TOPIC_PUBLISHER_H_
#define   _PLATFORM_THREAD_TOPIC_PUBLISHER_H_

#include <string>

#include "madara/threads/BaseThread.h"
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include "madara/knowledge/KnowledgeBase.h"
#include <madara/knowledge/containers/Double.h>
#include <madara/knowledge/containers/NativeDoubleVector.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <gams/variables/Agent.h>
#include <gams/variables/Self.h>
#include <move_base_msgs/MoveBaseActionGoal.h>


namespace platforms
{
  namespace threads
  {
    /**
    * A custom thread generated by gpc.pl
    **/
    class TopicPublisher : public madara::threads::BaseThread
    {
    public:
      /**
       * Default constructor
       **/
      TopicPublisher (ros::NodeHandle node_handle, gams::variables::Self* self);
      
      /**
       * Destructor
       **/
      virtual ~TopicPublisher ();
      
      /**
        * Initializes thread with MADARA context
        * @param   context   context for querying current program state
        **/
      virtual void init (madara::knowledge::KnowledgeBase & knowledge);

      /**
        * Executes the main thread logic
        **/
      virtual void run (void);

      void move(void);

      void cancel(void);

    private:
      /// data plane if we want to access the knowledge base
      madara::knowledge::KnowledgeBase data_;
      gams::variables::Self* self_;

      bool goalChanged_;
      bool cancelRequested_;

      ros::NodeHandle node_handle_;

      ros::Publisher pubGoal_;
      ros::Publisher pubCancel_;
      madara::knowledge::containers::Integer goalId_;
      std::string goal_frame_id_;
      madara::knowledge::containers::String frameType_;


    };
  } // end namespace threads
} // end namespace platforms

#endif // _PLATFORM_THREAD_TOPIC_PUBLISHER_H_
