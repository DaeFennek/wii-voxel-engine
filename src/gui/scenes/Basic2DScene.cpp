/*
 * Basic2DScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "Basic2DScene.h"

Basic2DScene::Basic2DScene() {
	m_Renderer = new Renderer2D();

}

Basic2DScene::~Basic2DScene() {
}

void Basic2DScene::draw() {
	std::vector<BasicTexture*>* textures = m_TextureHandler->getTextures();
	for (uint i = 0; i < textures->size(); i++)
	{
		if (((*textures)[i])->isVisible())
		{
			getRenderer()->drawTexture( ((*textures)[i]) );
		}
	}
}

void Basic2DScene::load() {
	BasicScene::load();
	GRRLIB_2dMode();
}

 Renderer2D* Basic2DScene::getRenderer() {
	return static_cast<Renderer2D*>(m_Renderer);
}

void Basic2DScene::unload() {
	BasicScene::unload();
	for (uint i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}
	m_elements.clear();
}

void Basic2DScene::update() {
	for (int i = 0; i < m_elements.size(); i++)
	{
		static_cast<UIElement*>(m_elements[i])->update();
	}
}