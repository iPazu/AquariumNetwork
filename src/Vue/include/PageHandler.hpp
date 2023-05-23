#pragma once

#include "Page.hpp"
#include "GraphNode.hpp"

class PageHandler : public GraphNode
{
public:
    explicit PageHandler(int, int);

    ~PageHandler();

    struct Request 
    {
        Page::Type       pageType;
        std::vector<int> vuesID;
        sf::Vector2i     aquariumPosition;
    };

    void handleEvents(sf::Event, sf::Vector2i);
    void requestPage(const Request&);


private:
    void            switchToPendingPage();
    void            handleAquarium();

    virtual void    updateCurrent(sf::Time);
    virtual void    drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

    Page *          mCurrentPage;
    // Page::Type      mPendingType;
    Request         mPendingRequest;
    bool            mIsRequestHandled;

    sf::Vector2i    mDimensions;


};