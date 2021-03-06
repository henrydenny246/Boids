#include "Game.hpp"

Game::Game(sf::Vector2u l_winSize, const std::string &l_title) : m_boidManager{}, m_renderer{l_winSize, l_title, &m_boidManager}, m_done{ false }, m_behaviours{ 0 }
{
    Reset();
}

Game::~Game()
{
    // Delete boids
}

void Game::Reset()
{
    // Delete boids
    // Reset to default settings
    m_boidManager.DeleteBoids();
    sf::Vector2u winSize = m_renderer.GetWindow()->getSize();
    for (int i = 0; i < 500; ++i)
    {
        m_boidManager.CreateBoid(winSize.x, winSize.y);
    }

    // Configurable behaviours (omit the behaviours you do not want)
    m_behaviours = (
        // (std::uint8_t)Behaviour::Alignment |
        (std::uint8_t)Behaviour::Cohesion |
        // (std::uint8_t)Behaviour::Separation |
        (std::uint8_t)Behaviour::Centralisation |
        (std::uint8_t)Behaviour::Orbit |
        (std::uint8_t)Behaviour::Resistance
    );
    m_renderer.UpdateBehaviourText(m_behaviours);
}

void Game::HandleInput()
{
    sf::Event ev;
    while (m_renderer.GetWindow()->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_done = true;
        }
        if (ev.type == sf::Event::KeyPressed)
        {
            switch (ev.key.code)
            {
                case (sf::Keyboard::Num1):
                    m_behaviours ^= (std::uint8_t)Behaviour::Alignment;
                    m_renderer.UpdateBehaviourText(m_behaviours);
                    break;
                case (sf::Keyboard::Num2):
                    m_behaviours ^= (std::uint8_t)Behaviour::Cohesion;
                    m_renderer.UpdateBehaviourText(m_behaviours);
                    break;
                case (sf::Keyboard::Num3):
                    m_behaviours ^= (std::uint8_t)Behaviour::Separation;
                    m_renderer.UpdateBehaviourText(m_behaviours);
                    break;
                case (sf::Keyboard::Num4):
                    m_behaviours ^= (std::uint8_t)Behaviour::Centralisation;
                    m_renderer.UpdateBehaviourText(m_behaviours);
                    break;
                case (sf::Keyboard::Num5):
                    m_behaviours ^= (std::uint8_t)Behaviour::Orbit;
                    m_renderer.UpdateBehaviourText(m_behaviours);
                    break;
                case (sf::Keyboard::Num6):
                    m_behaviours ^= (std::uint8_t)Behaviour::Resistance;
                    m_renderer.UpdateBehaviourText(m_behaviours);
                    break;

                case (sf::Keyboard::Space):
                {
                    m_boidManager.ToggleOrbitalDirection();
                    break;
                }
            
                default:
                    break;

            } 
        }
        if (ev.type == sf::Event::MouseButtonPressed)
        {
            m_boidManager.SetCentralisationNode(sf::Vector2f(sf::Mouse::getPosition(*m_renderer.GetWindow())));
        }
    }
}

void Game::Update()
{
    double deltaTime = m_elapsed.asSeconds();
    // Get delta time, update boid positions
    m_boidManager.Step(deltaTime, m_behaviours);
}

void Game::DrawScene()
{
    m_renderer.DrawScene(m_elapsed.asSeconds());
}

void Game::RestartClock()
{
    m_elapsed = m_clock.restart();
}

bool Game::IsDone()
{
    return m_done;
}