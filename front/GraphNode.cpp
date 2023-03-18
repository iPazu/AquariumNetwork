/**
 * @file GraphNode.cpp
 * @author Nicolas Gry(grybouilli@outlook.fr)
 * @brief GraphNode implementation file
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "include/GraphNode.hpp"
#include <algorithm>
#include <stdexcept>
/**
 * @brief Construct a new GraphNode object.
 * 
 * Default constructor for the GraphNode class.
 */
GraphNode::GraphNode()
: mChildren {}
{

}

/**
 * @brief Destroy the GraphNode object.
 * 
 * Default destructor for the GraphNode class.
 */
GraphNode::~GraphNode()
{
}

/**
 * @brief Update function for graphical elements.
 * 
 * Calls updateCurrent and updateChildren. Should not be redefined in children classes.
 * 
 * @param dt Elapsed time since last call to update.
 */
void GraphNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

/**
 * @brief Attach an other grpahical element to the current object.
 * 
 * Adds the GraphNode pointed at by child to the children of the current object.
 * 
 * @param child The pointer to the child to attach.
 */
void GraphNode::attachChild(GraphNode::Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

/**
 * @brief Detach an element from the Graph Tree
 * 
 * Detach the given graphical element from the current graph tree. 
 * @param child The element to remove.
 * @return GraphNode::Ptr The pointer to the removed element.
 */
GraphNode::Ptr GraphNode::detachChild(const GraphNode& child)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) { return p.get() == &child; });
	
    if(found != mChildren.end())
    {
        throw std::runtime_error("Detaching a child that isn't in this graph.");
    }

	Ptr result = std::move(*found);
	result->mParent = nullptr;

	mChildren.erase(found);
	return result;
}

/**
 * @brief Update current object.
 * 
 * Update current object given elapsed time since last call to update. Does nothing by default.
 * 
 * @param dt Elapsed time since last call to update.
 */
void GraphNode::updateCurrent(sf::Time dt)
{
    // does nothing by default
}


/**
 * @brief Update current object's children.
 * 
 * Update current object's children given elapsed time since last call to update. 
 * 
 * @param dt Elapsed time since last call to update.
 */
void GraphNode::updateChildren(sf::Time dt)
{
    for(auto & c : mChildren)
        c->updateCurrent(dt);
}


/**
 * @brief Draw current object.
 * 
 * Draw current object on the given target. Does nothing by default.
 * 
 * @param target Target to draw on.
 * @param states Transform to apply on the object before drawing it.
 */
void GraphNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    // does nothing by default
}

/**
 * @brief Draw current object's children.
 * 
 * Draw current object's children on the given target.
 * 
 * @param target Target to draw on.
 * @param states Transform to apply on the objects before drawing it.
 */
void GraphNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto & c : mChildren)
		c->draw(target, states);
}


/**
 * @brief Draw current object and its children.
 * 
 * Draw current object and its children on the given target. 
 * 
 * @param target Target to draw on.
 * @param states Transform to apply on the object and its children before drawing it.
 */
void GraphNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

