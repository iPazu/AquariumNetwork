#ifndef ADD_FISH_PANEL_HPP
#define ADD_FISH_PANEL_HPP

#include "GraphNode.hpp"
#include "Button.hpp"

class AddFishPanel : public GraphNode {
public:
    explicit AddFishPanel();
    ~AddFishPanel();

private:
    Button mAddFishButton;
    Label mAddFishLabel;
};

#endif // ADD_FISH_PANEL_HPP