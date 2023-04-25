#ifndef ADD_FISH_PANEL_HPP
#define ADD_FISH_PANEL_HPP

#include "GraphNode.hpp"
#include "Button.hpp"

class AddFishPanel : public GraphNode {
public:
    explicit AddFishPanel();
    ~AddFishPanel() override;

private:
    Button mAddFishButton;
    Label mAddFishLabel;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // ADD_FISH_PANEL_HPP