//
// Copyright (c) 2017 CNRS
//
// This file is part of PinInvDyn
// PinInvDyn is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
// PinInvDyn is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Lesser Public License for more details. You should have
// received a copy of the GNU Lesser General Public License along with
// PinInvDyn If not, see
// <http://www.gnu.org/licenses/>.
//

#ifndef __invdyn_contact_base_hpp__
#define __invdyn_contact_base_hpp__

#include <pininvdyn/robot-wrapper.hpp>
#include <pininvdyn/math/utils.hpp>
#include <pininvdyn/tasks/task-motion.hpp>
#include <pininvdyn/math/constraint-base.hpp>
#include <pininvdyn/math/constraint-equality.hpp>
#include <pininvdyn/math/constraint-inequality.hpp>

namespace pininvdyn
{
  namespace contacts
  {
    
    ///
    /// \brief Base template of a Contact.
    ///
    class ContactBase
    {
    public:
      typedef pininvdyn::RobotWrapper RobotWrapper;
      typedef pininvdyn::math::ConstraintBase ConstraintBase;
      typedef pininvdyn::math::ConstraintInequality ConstraintInequality;
      typedef pininvdyn::math::ConstraintEquality ConstraintEquality;
      typedef pininvdyn::math::ConstRefVector ConstRefVector;
      typedef pininvdyn::math::Matrix Matrix;
      typedef pininvdyn::tasks::TaskMotion TaskMotion;
      typedef se3::Data Data;

      ContactBase(const std::string & name,
                  RobotWrapper & robot);

      const std::string & name() const;

      void name(const std::string & name);
      
      /// Return the number of motion constraints
      virtual unsigned int n_motion() const = 0;

      /// Return the number of force variables
      virtual unsigned int n_force() const = 0;

      virtual const ConstraintBase & computeMotionTask(const double t,
                                                       ConstRefVector q,
                                                       ConstRefVector v,
                                                       Data & data) = 0;

      virtual const ConstraintInequality & computeForceTask(const double t,
                                                            ConstRefVector q,
                                                            ConstRefVector v,
                                                            Data & data) = 0;

      virtual const Matrix & getForceGeneratorMatrix() = 0;

      virtual const ConstraintEquality & computeForceRegularizationTask(const double t,
                                                                    ConstRefVector q,
                                                                    ConstRefVector v,
                                                                    Data & data) = 0;

      virtual const TaskMotion & getMotionTask() const = 0;
      virtual const ConstraintBase & getMotionConstraint() const = 0;
      virtual const ConstraintInequality & getForceConstraint() const = 0;
      virtual const ConstraintEquality & getForceRegularizationTask() const = 0;
      virtual double getForceRegularizationWeight() const = 0;
      
    protected:
      std::string m_name;
      /// \brief Reference on the robot model.
      RobotWrapper & m_robot;
    };
    
  }
}

#endif // ifndef __invdyn_contact_base_hpp__