/* 
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ROS_PUBLISHER_H_
#define _ROS_PUBLISHER_H_

#include "rosserial_msgs/TopicInfo.h"
#include "ros/node_handle.h"
#include "msg.h"


namespace ros {

  /* Generic Publisher */
  class Publisher
  {
    public:
      Publisher( const char * topic_name, Msg * msg, int endpoint=rosserial_msgs::TopicInfo::ID_PUBLISHER) :
        topic_(topic_name), 
        has_flash_topic_( false ),
        msg_(msg),
        endpoint_(endpoint) 
      {};
	
      Publisher( const __FlashStringHelper * topic_name, Msg * msg, int endpoint=rosserial_msgs::TopicInfo::ID_PUBLISHER) :
        topic_( reinterpret_cast<const char *>( topic_name ) ), 
        has_flash_topic_( true ),
        msg_(msg),
        endpoint_(endpoint)
      {};
      
      int publish( const Msg * msg ) { return nh_->publish(id_, msg); };
      int getEndpointType(){ return endpoint_; }

      const char * topic_;
      bool has_flash_topic_;
      Msg *msg_;
      // id_ and no_ are set by NodeHandle when we advertise 
      int id_;
      NodeHandleBase_* nh_;

    private:
      int endpoint_;
  };

}

#endif
