#ifndef LEPH_FOOTSTEPDIFFERENTIATORCONCEPT_HPP
#define LEPH_FOOTSTEPDIFFERENTIATORCONCEPT_HPP

#include "TimeSeries/Concept.hpp"

namespace Leph {

/**
 * FootStepDifferentiatorConcept
 *
 * Compute delta pose with respect to robot
 * egocentric frame and with respect to 
 * support foot step.
 * Inputs:
 * 0: is_support_foot_left
 * 1: x
 * 2: y
 * 3: theta
 * Outputs:
 * 0: delta_x_on_left_foot
 * 1: delta_y_on_left_foot
 * 2: delta_theta_on_left_foot
 * 3: delta_x_on_right_foot
 * 4: delta_y_on_right_foot
 * 5: delta_theta_on_right_foot
 */
class FootStepDifferentiatorConcept : public Concept
{
    public:
        
        /**
         * Inherit Concept
         */
        virtual std::string name() const override;
        virtual size_t inputSize() const override;
        virtual size_t outputSize() const override;

        /**
         * Inherit Optimize
         */
        virtual size_t parameterSize() const override;
        virtual Leph::MetaParameter defaultParameter
            (size_t index) const override;

    protected:
        
        /**
         * Inherit Concept
         */
        virtual bool doCompute(double time) override;
};

}

#endif

