#include "state.hpp"

State::State(sf::RenderWindow *window, std::stack<State *> *states)
{

    this->window = window;
    this->states = states;

    this->quit = false;
    this->paused = false;

    this->Keytime = 0.f;
    this->KeytimeMax = 10.f;
}

void State::pauseState()
{
    this->paused = true;
}

const bool State::getKeytime()
{
    if (this->Keytime >= this->KeytimeMax)
    {
        this->Keytime = 0.f;
        return true;
    }

    return false;
}

void State::unpauseState()
{
    this->paused = false;
}

State::~State()
{
}

const bool &State::hasQuit() const
{
    return this->quit;
}

void State::exit()
{
    this->quit = true;
    this->view.setCenter(sf::Vector2f(WINDOW_SIZE.first / 2.f, WINDOW_SIZE.second / 2.f));
    this->window->setView(view);
}

void State::update(const float &dt)
{
}

void State::updateMousePos()
{
    this->mousePosScreen = sf::Mouse::getPosition();                           //sijainti n�yt�ll�
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);              //sijainti ikkunassa
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow); //muuttaa pikselin koordinaatiksi
}

void State::render(sf::RenderTarget *target)
{
}

void State::updatekeytime(const float &dt)
{
    if (this->Keytime < this->KeytimeMax)
        this->Keytime += 100.f * dt;
}