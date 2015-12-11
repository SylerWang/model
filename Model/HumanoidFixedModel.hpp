#ifndef LEPH_HUMANOIDFIXEDMODEL_HPP
#define LEPH_HUMANOIDFIXEDMODEL_HPP

#include "Model/HumanoidModel.hpp"

namespace Leph {

/**
 * HumanoidFixedModel
 *
 * Contains two HumanoidModel with
 * root located at each leg tip and
 * switching between the two according to
 * supporting leg.
 */
class HumanoidFixedModel
{
    public:
        
        /**
         * Enum for support foot
         */
        enum SupportFoot {
            LeftSupportFoot,
            RightSupportFoot,
        };

        /**
         * Initialization with given model type
         */
        HumanoidFixedModel(RobotType type);
        
        /**
         * Virtual destructor
         */
        virtual ~HumanoidFixedModel();
        
        /**
         * Return the current support foot
         */
        SupportFoot getSupportFoot() const;

        /**
         * Update the current support to given 
         * support foot and update odometry
         */
        void setSupportFoot(SupportFoot foot);

        /**
         * Compute using given support foot
         * orientation the robot base yaw 
         * or set manually the trunk yaw
         * (a correction is applied to compute
         * the base yaw)
         */
        void setYaw(SupportFoot foot);
        void setYaw(SupportFoot foot, double trunkYaw);

        /**
         * Return Leph::HumanoidModel fixed
         * on current supporting foot tip
         */
        const HumanoidModel& get() const;
        HumanoidModel& get();

        /**
         * Update current support foot
         * and compute floating base tranformation
         * to integrate model displacement
         */
        virtual void updateBase();

        /**
         * Udpate support foot floating base (pitch, roll)
         * orientation in order that trunk
         * orientation matches given euler angle (IMU)
         */
        void setOrientation(double trunkPitch, double trunkRoll);

        /**
         * Compute and return the Zero Moment Point
         * (ZMP) in given frame. Given degrees of freedom
         * velocity and acceleration are used (to compute
         * inverse dynamics)
         */
        Eigen::Vector3d zeroMomentPoint(
            const std::string& frame,
            const Eigen::VectorXd& velocity,
            const Eigen::VectorXd& acceleration);
        Eigen::Vector3d zeroMomentPoint(
            const std::string& frame,
            const VectorLabel& velocity,
            const VectorLabel& acceleration);

        /**
         * Set the model state by running 
         * Inverse Kinematics on both legs.
         * The state is given by the support foot,
         * the flying foot position, the position 
         * and orientation of the trunk with
         * respect to support foot.
         * Support foot is set flat on the ground.
         * Flying foot orientation is set the same as
         * support foot in world frame.
         * False is returned if the inverse 
         * kinematics fails.
         */
        bool trunkFootIK(
            SupportFoot support,
            const Eigen::Vector3d& trunkPos, 
            const Eigen::Matrix3d& trunkRotation,
            const Eigen::Vector3d& flyingFootPos);

        /**
         * Compute and return all degrees of
         * freedom velocities from given
         * trunk translation, orientation velocities
         * and flying foot translation velocity 
         * in support foot frame.
         * Translation velocity is the velocity vector.
         * Orientation velocity is the instantaneous 
         * angular velocity vector (in support foot frame)
         * !!! 
         * !!! Angular velocity vector is not the
         * !!! differentiation of axis angle representation
         * !!! (see AxisAngle::AxisDiffToAxisVel())
         * !!!
         */
        Eigen::VectorXd trunkFootIKVel(
            const Eigen::Vector3d& trunkPosVel, 
            const Eigen::Vector3d& trunkAxisAnglesVel,
            const Eigen::Vector3d& flyingFootPosVel);

        /**
         * Compute and return all degrees of freedom
         * accelerations from given trunk translation,
         * orientation and flying foot velocities and accelerations
         * in support foot frame. All degrees of freedom
         * velocities are also given.
         * Translation velocity/acceleration 
         * is the velocity/acceleration vector.
         * Orientation velocity/acceleration is the instantaneous 
         * angular velocity/acceleration vector (in support foot frame)
         * !!! 
         * !!! Angular velocity/acceleration vector is not the
         * !!! differentiation of axis angle representation
         * !!! (see AxisAngle::AxisDiffToAxisVel())
         * !!!
         */
        Eigen::VectorXd trunkFootIKAcc(
            const Eigen::VectorXd& dq,
            const Eigen::Vector3d& trunkPosVel, 
            const Eigen::Vector3d& trunkAxisAnglesVel,
            const Eigen::Vector3d& flyingFootPosVel,
            const Eigen::Vector3d& trunkPosAcc, 
            const Eigen::Vector3d& trunkAxisAnglesAcc,
            const Eigen::Vector3d& flyingFootPosAcc);

    private:
        
        /**
         * Current support foot
         */
        SupportFoot _supportFoot;

        /**
         * HumanoidModel for left and right 
         * support foot
         */
        HumanoidModel _modelLeft;
        HumanoidModel _modelRight;

        /**
         * Convert given base pitch/roll torque into
         * X/Y torque in world frame
         */
        void convertFootMoment(
            double torquePitch, double torqueRoll,
            double& Mx, double& My);

        /**
         * Compute ZMP position given X/Y/Z force
         * and X/Y moment in world frame
         */
        Eigen::Vector3d computeZMP(
            double Fx, double Fy, double Fz, 
            double Mx, double My);
};

}

#endif

