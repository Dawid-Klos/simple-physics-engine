//
// Created by dave on 22.06.23.
//
#include <gtest/gtest.h>
#include <engine/particle.h>
#include "../src/particle.cpp"

using namespace engine;

TEST(ParticleTest, Constructor) {
    Particle *particle = nullptr;

    particle = new Particle();
    ASSERT_NE(particle, nullptr);
}

TEST(ParticleTest, SetPosition) {
    Particle particle = Particle();
    particle.setPosition(real(10.0f), real(200.0f));

    Vector position = particle.getPosition();

    ASSERT_EQ(position.x, real(10.0f));
    ASSERT_EQ(position.y, real(200.0f));
}

TEST(ParticleTest, SetNegativePosition) {
    Particle particle = Particle();
    particle.setPosition(real(-10.0f), real(-200.0f));

    Vector position = particle.getPosition();

    ASSERT_EQ(position.x, real(-10.0f));
    ASSERT_EQ(position.y, real(-200.0f));
}

TEST(ParticleTest, GetPosition) {
    Particle particle = Particle();

    particle.setPosition(real(10.0f), real(200.0f));
    particle.setPosition(real(200.0f), real(10.0f));
    particle.setPosition(real(0.0f), real(0.0f));

    Vector position = particle.getPosition();

    ASSERT_EQ(position.x, real(0.0f));
    ASSERT_EQ(position.y, real(0.0f));
}

TEST(ParticleTest, SetVelocityWithReal) {
    Particle particle = Particle();
    particle.setVelocity(real(10.0f), real(200.0f));

    Vector velocity = particle.getVelocity();

    ASSERT_EQ(velocity.x, real(10.0f));
    ASSERT_EQ(velocity.y, real(200.0f));
}

TEST(ParticleTest, SetVelocityWithVector) {
    Particle particle = Particle();
    Vector velocity = Vector(real(10.0f), real(200.0f));

    particle.setVelocity(velocity);
    velocity = particle.getVelocity();

    ASSERT_EQ(velocity.x, real(10.0f));
    ASSERT_EQ(velocity.y, real(200.0f));
}

TEST(ParticleTest, SetNegativeVelocity) {
    Particle particle = Particle();
    particle.setVelocity(real(-10.0f), real(-200.0f));

    Vector velocity = particle.getVelocity();

    ASSERT_EQ(velocity.x, real(-10.0f));
    ASSERT_EQ(velocity.y, real(-200.0f));
}

TEST(ParticleTest, SetAccelerationWithReal) {
    Particle particle = Particle();
    particle.setAcceleration(real(100.0f), real(20.0f));

    Vector acceleration = particle.getAcceleration();

    ASSERT_EQ(acceleration.x, real(100.0f));
    ASSERT_EQ(acceleration.y, real(20.0f));
}

TEST(ParticleTest, SetAccelerationWithVector) {
    Particle particle = Particle();
    Vector acceleration = Vector(real(100.0f), real(20.0f));

    particle.setAcceleration(acceleration);
    acceleration = particle.getAcceleration();

    ASSERT_EQ(acceleration.x, real(100.0f));
    ASSERT_EQ(acceleration.y, real(20.0f));
}

TEST(ParticleTest, SetNegativeAcceleration) {
    Particle particle = Particle();
    particle.setAcceleration(real(-10.0f), real(-200.0f));

    Vector acceleration = particle.getAcceleration();

    ASSERT_EQ(acceleration.x, real(-10.0f));
    ASSERT_EQ(acceleration.y, real(-200.0f));
}

TEST(ParticleTest, SetMass) {
    Particle particle = Particle();
    particle.setMass(real(10.0f));

    real mass = particle.getMass();

    // we are storing inverted mass
    ASSERT_EQ(mass, real(10.0f));
}

// get inverted mass
TEST(ParticleTest, GetInvertedMass) {
    Particle particle = Particle();
    particle.setMass(real(10.0f));

    real mass = particle.getInvertedMass();

    // we are storing inverted mass
    ASSERT_EQ(mass, real(0.1f));
}

TEST(ParticleTest, IntegratorTestVelocity) {
    Particle particle = Particle();
    particle.setMass(real(10.0f));
    particle.setDamping(real(0.99f));
    particle.setPosition(real(10.0f), real(10.0f));

    particle.setAcceleration(real(10.0f), real(10.0f));
    particle.setVelocity(real(10.0f), real(10.0f));

    particle.integrate(real(0.12f));
    Vector velocity = particle.getVelocity();

    EXPECT_NEAR(velocity.x, real(11.186500494), 0.0001f);
    EXPECT_NEAR(velocity.y, real(11.186500494), 0.0001f);
}

TEST(ParticleTest, IntegratorTestPosition) {
    Particle particle = Particle();
    particle.setMass(10.0f);
    particle.setDamping(0.99f);
    particle.setPosition(10.0f, 10.0f);

    particle.setAcceleration(10.0f, 10.0f);
    particle.setVelocity(10.0f, 10.0f);

    particle.integrate(0.12f);
    Vector position = particle.getPosition();

    EXPECT_NEAR(position.x, 11.2f, 0.0001f);
    EXPECT_NEAR(position.y, 11.2f, 0.0001f);
}

// integrator acceleration
TEST(ParticleTest, IntegratorTestAcceleration) {
    Particle particle = Particle();
    particle.setMass(real(10.0f));
    particle.setDamping(real(0.99f));
    particle.setPosition(real(10.0f), real(10.0f));

    particle.setAcceleration(real(10.0f), real(10.0f));
    particle.setVelocity(real(10.0f), real(10.0f));

    particle.integrate(real(0.12f));
    Vector acceleration = particle.getAcceleration();

    ASSERT_EQ(acceleration.x, real(0.0f));
    ASSERT_EQ(acceleration.y, real(0.0f));
}