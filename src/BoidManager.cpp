#include "BoidManager.hpp"

BoidManager::BoidManager() : m_anticlockwiseOrbit{true}, m_centralisationNode{(float)constants::k_windowSize[0], (float)constants::k_windowSize[1]}
{

}

BoidManager::~BoidManager()
{
    DeleteBoids();
}

void BoidManager::CreateBoid(sf::Vector2f l_pos)
{
    // Allocate memory and push boid onto vector
    Boid *boid = new Boid(l_pos);
    m_flock.push_back(boid);
}

void BoidManager::CreateBoid(unsigned int l_winWidth, unsigned int l_winHeight)
{
    Boid *boid = new Boid(l_winWidth, l_winHeight);
    m_flock.push_back(boid);
}

void BoidManager::DeleteBoids()
{
    // Deallocate memory
    for (auto &boid : m_flock)
    {
        delete boid;
        boid = nullptr;
    }
    m_flock.clear();
}

void BoidManager::Step(double dt, std::uint8_t behaviourOptions)
{
    for (auto &boid : m_flock)
    {
        boid->Flock(m_flock, m_centralisationNode, behaviourOptions, m_anticlockwiseOrbit);
    }
    for (auto &boid : m_flock)
    {
        boid->Update(dt);
    }
}

void BoidManager:: ToggleOrbitalDirection()
{
    m_anticlockwiseOrbit = !m_anticlockwiseOrbit;
}

void BoidManager::SetCentralisationNode(sf::Vector2f l_pos)
{
    m_centralisationNode = l_pos;
}

const std::vector<Boid*>& BoidManager::GetFlock()
{
    return m_flock;
}