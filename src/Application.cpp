#include "../include/Application.hpp"

Application::Application(const std::string_view &title, const sf::Vector2f& size, const unsigned int& frame_limit)
: size(size),
m_activeSection(0)
{
    const auto bpp = sf::VideoMode::getDesktopMode().bitsPerPixel;
    const auto vmode = sf::VideoMode(size.x, size.y, bpp);
    m_window.create(vmode, sf::String(title.data()));
    m_window.setFramerateLimit(frame_limit);
    ImGui::SFML::Init(m_window);
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
}

void Application::run()
{
    while(m_window.isOpen())
    {
        this->update();
        this->render();
    }
}

void Application::placeMenuSection()
{
    if(Section sec1("Menu", sf::Vector2f(0.f, 0.f), sf::Vector2f(this->size.x/4.f, this->size.y)); sec1)
    {
        auto [w, h] = ImGui::GetContentRegionMax();
        ImGui::Separator();
        ImGui::TextColored(sf::Color{255, 0, 0, 255}, "Rejestracja");
        if(ImGui::Button("Info", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Info; }
        if(ImGui::Button("InWszystko", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Input_All; }
        if(ImGui::Button("InPrzedmiot", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Input_Przedmiot; }
        if(ImGui::Button("InProwadzacy", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Input_Prowadzacy; }
        if(ImGui::Button("InStudent", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Input_Student; }
        ImGui::NewLine(); ImGui::Separator();
        ImGui::TextColored(sf::Color{255, 0, 0, 255}, "Odczyt");
        if(ImGui::Button("OutWszystko", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Output_All; }
        if(ImGui::Button("OutPrzedmiot", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Output_Przedmiot; }
        if(ImGui::Button("OutProwadzacy", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Output_Prowadzacy; }
        if(ImGui::Button("OutStudent", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Output_Student; }
        if(ImGui::Button("OutKierunek", sf::Vector2f(w, 20.f))) { m_activeSection = ActiveSection::Output_Kierunek; }
    }
}

void Application::placeFormSection()
{
    if(Section sec2("Formularz", sf::Vector2f(this->size.x/4.f, 0.f), sf::Vector2f(this->size.x*3.f/4.f, this->size.y)); sec2)
    {
        switch(m_activeSection)
        {
            case ActiveSection::Input_All: { formInputAll(); break; }
            case ActiveSection::Input_Przedmiot: { formInputPrzedmiot(); break; }
            case ActiveSection::Input_Prowadzacy: { formInputProwadzacy(); break; }
            case ActiveSection::Input_Student: { formInputStudent(); break; }
            case ActiveSection::Output_All: { formOutputAll(); break; }
            case ActiveSection::Output_Przedmiot: { formOutputPrzedmiot(); break; }
            case ActiveSection::Output_Prowadzacy: { formOutputProwadzacy(); break; }
            case ActiveSection::Output_Student: { formOutputStudent(); break; }
            case ActiveSection::Output_Kierunek: { formOutputKierunek(); break; }
            case ActiveSection::Info:
            default: { formInfo(); break; }
        }
    }
}

void Application::update()
{
    while(m_window.pollEvent(m_event))
    {
        ImGui::SFML::ProcessEvent(m_window, m_event);

        if(m_event.type == sf::Event::Resized)
        {
            this->size = sf::Vector2f{static_cast<float>(m_event.size.width), static_cast<float>(m_event.size.height)};
            if(this->size.x < 640.f || this->size.y < 480.f)
            {
                m_window.setSize(sf::Vector2u(640u, 480u));
            }
        }

        if(m_event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
    
    ImGui::SFML::Update(m_window, m_clock.restart());

    this->placeMenuSection();
    this->placeFormSection();
    
    this->render();
}

void Application::render()
{
    m_window.clear();
    ImGui::SFML::Render(m_window);
    m_window.display();
}