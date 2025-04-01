/**
 * @file DriveBackAfterScore.h
 */

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/CommandSwerveDrivetrain.h"

#include <frc/controller/PIDController.h>

/**
 * @brief This class moves the robot back after scoring a coral.
 */
class DriveBackAfterScore
    : public frc2::CommandHelper<frc2::Command, DriveBackAfterScore> {
public:
    /**
     * @brief The default backward distance is 6 inches.
     */
    static constexpr units::inch_t kDefaultDistance = 6_in;

    explicit DriveBackAfterScore(
        subsystems::CommandSwerveDrivetrain* drivetrain,
        units::inch_t distance = kDefaultDistance
    );
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

    units::inch_t GetDistance(frc::Pose2d first, frc::Pose2d second);

private:
    subsystems::CommandSwerveDrivetrain* m_drivetrain;

    static constexpr double kP = 1.0;
    static constexpr double kI = 0.0;
    static constexpr double kD = 0.0;
    static constexpr units::meters_per_second_t kMaxVelocity = 1.0_mps;

    // Apply a slight shift to the left while driving back to pull out an algae
    static constexpr units::degrees_per_second_t kLeftRotate = 3_deg_per_s;

    swerve::requests::RobotCentric robotOriented = swerve::requests::RobotCentric{}
        .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage)
        .WithVelocityY(0_mps)
        .WithRotationalRate(kLeftRotate);

    frc::PIDController m_XAlignmentPID {kP, kI, kD};

    const units::inch_t kTolerance = 1_in;
    units::inch_t m_backwardDistance;
    frc::Pose2d m_initialPose;
};