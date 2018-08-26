#
#   Copyright (C) 2011, 2012. PARP Research Group.
#   <http://perception.inf.um.es>
#   University of Murcia, Spain.
#
#   This file is part of the QVision library.
#
#   QVision is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as
#   published by the Free Software Foundation, version 3 of the License.
#
#   QVision is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with QVision. If not, see <http://www.gnu.org/licenses/>.
#

#############################
#
#   File qvros.pri
#

!qvros_available {
    CONFIG += qvros_available

    message(Included module: qvros)

    DEFINES += QVROS QVSSBA_AVAILABLE

    !exists($$ROS_PATH): \
            error(In module qvros: Specified path to ROS '$$ROS_PATH' does not exists.)

    INCLUDEPATH +=  $$ROS_PATH/ros/core/roscpp/include/                                            \
                    $$ROS_PATH/ros/core/rosconsole/include/                                        \
                    $$ROS_PATH/ros/core/roslib/include/                                            \
                    $$ROS_PATH/stacks/vslam/sba/include                                            \
                    $$ROS_PATH/stacks/vslam/csparse/include                                        \
                    $$ROS_PATH/ros/3rdparty/xmlrpcpp/src/                                          \
                    $$ROS_PATH/stacks/geometry/eigen/include/                                      \
                    $$ROS_PATH/stacks/visualization_common/visualization_msgs/msg_gen/cpp/include/ \
                    $$ROS_PATH/stacks/common_msgs/geometry_msgs/msg_gen/cpp/include/               \
                    $$ROS_PATH/ros/core/roslib/msg_gen/cpp/include/                                \
                    $$ROS_PATH/ros/std_msgs/msg_gen/cpp/include/									\
					$$ROS_PATH/stacks/ros_comm/clients/cpp/roscpp_serialization/include/			\
					$$ROS_PATH/stacks/ros_comm/clients/cpp/roscpp_traits/include/					\
					$$ROS_PATH/stacks/ros_comm/clients/cpp/roscpp/include/							\
					$$ROS_PATH/opt/ros/diamondback/stacks/ros_comm/tools/rosconsole/include/		\
					$$ROS_PATH/stacks/ros_comm/tools/rosconsole/include/							\
					$$ROS_PATH/stacks/ros_comm/utilities/rostime/include/							\
					$$ROS_PATH/stacks/ros_comm/utilities/cpp_common/include/						\
					$$ROS_PATH/stacks/ros_comm/utilities/xmlrpcpp/src/								\
					$$ROS_PATH/stacks/ros_comm/messages/std_msgs/msg_gen/cpp/include/				\
					$$ROS_PATH/stacks/ros_comm/messages/std_msgs/include/							\
					$$ROS_PATH/stacks/common_msgs/visualization_msgs/msg_gen/cpp/include/			\
					$$ROS_PATH/stacks/vslam/bpcg/include/

    LIBS += -Wl,-rpath=$$ROS_PATH/ros/core/roslib/lib       \
            -Wl,-rpath=$$ROS_PATH/ros/core/roscpp/lib       \
            -Wl,-rpath=$$ROS_PATH/stacks/vslam/sba/lib      \
            -Wl,-rpath=$$ROS_PATH/stacks/vslam/csparse/lib/ \
            -L$$ROS_PATH/ros/core/roslib/lib                \
            -L$$ROS_PATH/ros/core/roscpp/lib                \
            -L$$ROS_PATH/stacks/vslam/sba/lib               \
            -L$$ROS_PATH/stacks/vslam/csparse/lib/          \
            -lroslib -lcsparse -lsba

    HEADERS +=   $$PWD/qvros/qvros.h $$PWD/qvros/qvssba.h

    SOURCES +=   $$PWD/qvros/qvssba.cpp

    message(* Path to ROS: $$ROS_PATH)
}

