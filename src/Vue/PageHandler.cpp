#include "include/PageHandler.hpp"
#include "include/WelcomePage.hpp"
#include "include/SelectionPage.hpp"
#include "include/TextureData.hpp"

PageHandler::PageHandler(int width, int height)
: mCurrentPage{ nullptr }
, mPendingRequest { .pageType = Page::Type::Welcome }
, mDimensions { width, height }
, mIsRequestHandled{ false }
{
    switchToPendingPage();
}

PageHandler::~PageHandler()
{
    delete mCurrentPage;
    mCurrentPage = nullptr;
}

void PageHandler::handleEvents(sf::Event event, sf::Vector2i mouse)
{
    if(mCurrentPage)
        mCurrentPage->handleEvents(event, mouse);
}

void PageHandler::requestPage(const Request& request)
{
    mPendingRequest = request;
    mIsRequestHandled = false;
}

void PageHandler::switchToPendingPage()
{
    if(!mCurrentPage || mCurrentPage->getPageType() != mPendingRequest.pageType)
    {
        delete mCurrentPage; // ensures whatever was in there gets removed

        switch (mPendingRequest.pageType)
        {
        case Page::Type::Welcome:
            mCurrentPage = new WelcomePage(SpriteProperties[SPROP::WELCOMEPAGE], mDimensions.x, mDimensions.y);
            break;
        case Page::Type::VueSelection:
            mCurrentPage = new SelectionPage(SpriteProperties[SPROP::SELECTIONPAGE], SpriteProperties[SPROP::BUTTON], mDimensions.x, mDimensions.y, mPendingRequest.vuesID);
        default:
            break;
        }
    }

    mIsRequestHandled = true;
}

void PageHandler::handleAquarium()
{
    
}

void PageHandler::updateCurrent(sf::Time dt)
{
    if(mCurrentPage)
    {
        if(!mIsRequestHandled)
        {
            if(mCurrentPage->getPageType() != mPendingRequest.pageType)
            {
                switchToPendingPage();
            }
            else
            {
                if(mPendingRequest.pageType == Page::Type::Aquarium)
                {
                    handleAquarium();
                }
            }
        }
        mCurrentPage->update(dt);
    }
}

void PageHandler::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // inshallah ça marche mdr
    target.draw(*mCurrentPage, states);
}

