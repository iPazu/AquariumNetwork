/**
 * @file GraphNode.hpp
 * @author Nicolas Gry(grybouilli@outlook.fr)
 * @brief GraphNode definition file.
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <vector>


/**
 * @brief Elementary graphical class.
 * 
 * All entites to be rendered in the app should inherit from it. Entities can be attached to others so that their position and other geometrical characteristics are bounded.
 */
class GraphNode : public sf::Drawable, public sf::Transformable
{
public:
    /**
     * @brief The pointer to GraphNode type.
     * 
     * Alias for std::unique_ptr<GraphNode>. 
     */
    using Ptr = std::unique_ptr<GraphNode>;

    GraphNode();
    virtual ~GraphNode();

    void    update(sf::Time);

    void    attachChild(Ptr);
    Ptr     detachChild(const GraphNode&);

private:
    virtual void    updateCurrent(sf::Time);
    void            updateChildren(sf::Time);

    virtual void    drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
    void            drawChildren(sf::RenderTarget&, sf::RenderStates) const;
    void            draw(sf::RenderTarget&, sf::RenderStates) const;

    std::vector<Ptr>    mChildren;
    GraphNode *         mParent;

};